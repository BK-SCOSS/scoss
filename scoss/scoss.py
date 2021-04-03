from __future__ import absolute_import

from scoss.metrics import MetricList, Metric, all_metrics
from scoss.metrics.token_based_metric import *
from scoss.utils import check_language
from scoss.my_source import MySource
from jinja2 import Environment
from collections import OrderedDict, defaultdict

import pandas as pd
import os
import glob
import enum
import time
import copy


class ScossState(enum.Enum):
    INIT = 0
    RUNNING = 1
    CLOSE = 3


class Scoss():
    __id = 0

    def __init__(self, lang, used_metrics=None):
        """__init__.

        Args:
            lang:
            used_metrics:
        """
        Scoss.__id += 1
        self.id = Scoss.__id

        self.__lang = check_language(lang)
        self.__state = ScossState.INIT
        self.__thresholds = defaultdict(float)

        self.__metric_list = MetricList(used_metrics)
        for metric_name in self.__metric_list.get_metric_names():
            self.__thresholds[metric_name] = 0.0

        self.__sources = OrderedDict()
        self.__pending_pool = OrderedDict()

        self.__similarity_matrix = dict()
        self.__alignment_matrix = dict()
    
    def get_language(self):
        return self.__lang

    def get_number_of_sources(self):
        return len(self.__sources) + len(self.__pending_pool)

    def set_metric_threshold(self, metric_name, threshold: float):
        if metric_name not in self.__thresholds:
            raise ValueError(
                f'metric_name:{metric_name} is not in metric_list')
        self.__thresholds[metric_name] = threshold

    def add_metric(self, metric, threshold: float = 0.0, exist_ok=False):
        if self.__state != ScossState.INIT:
            raise ValueError('Cannot add metric after running')

        self.__metric_list.add_metric(metric, exist_ok=exist_ok)
        if isinstance(metric, Metric):
            metric_name = metric.get_name()
        else:
            metric_name = metric
        self.__thresholds[metric_name] = threshold

    def add_source_str(self, source_str, mask):
        if mask in self.__sources.keys() or mask in self.__pending_pool.keys():
            raise ValueError(f'mask:{mask} is already exist')
        src = MySource.from_str(source_str, lang=self.__lang)
        src.name = mask
        self.__pending_pool[mask] = src
        if self.__state == ScossState.RUNNING:
            self.run()

    def update_source_str(self, source_str, mask):
        src = MySource.from_str(source_str, lang=self.__lang)
        src.name = mask
        self.__pending_pool[mask] = src

        if self.__state == ScossState.RUNNING:
            self.run()

    def add_file(self, file, mask=None):
        if mask is None:
            mask = file
        if mask in self.__sources or mask in self.__pending_pool:
            raise ValueError(f'mask:{mask} is already exist')
        src = MySource.from_file(file, lang=self.__lang)
        src.name = mask
        self.__pending_pool[mask] = src

        if self.__state == ScossState.RUNNING:
            self.run()

    def update_file(self, file, mask=None):
        if mask is None:
            mask = file
        src = MySource.from_file(file, lang=self.__lang)
        src.name = mask
        self.__pending_pool[mask] = src

        if self.__state == ScossState.RUNNING:
            self.run()

    def add_file_by_wildcard(self, dirpath, recursive=True):
        for file in glob.glob(dirpath, recursive=recursive):
            self.add_file(file)

    def check_similarity(self, src):
        """check_similarity.
            Check similarity between src and current sources 

        Args:
            src:
        """
        ret = dict()
        for other_mask, other in self.__sources.items():
            scores = self.__metric_list.evaluate(src, other)
            ret[other_mask] = scores

        return ret

    def run(self):
        """run.
            compute similarity source from pending_pool vs solved sources

        """
        self.__state = ScossState.RUNNING

        if self.__metric_list.get_number_of_metrics() == 0:
            self.__metric_list = MetricList(all_metrics)

        pending_pool_items = list(self.__pending_pool.items())
        for name, src in pending_pool_items:
            scores = self.check_similarity(src)

            self.__similarity_matrix[name] = scores
            for other_name, score in scores.items():
                self.__similarity_matrix[other_name][name] = score

            self.__sources[name] = src
            self.__pending_pool.pop(name)


    def get_similarity_matrix(self):
        self.run()
        return self.__similarity_matrix

    def sort_matches(self, matches, by=None):
        """sort_matches.

        Args:
            matches:
            by: 'sum': sort by sum of all metrics
                List[metric_name]: sort by order in this list
        """
        matches = list(matches)

        if by == 'sum' or by == None:
            matches.sort(reverse=True, key=lambda match:  sum(
                match['scores'].values()))
            return matches
        else:
            matches.sort(reverse=True, key=lambda match:  match['scores'][by])
            return matches

    def get_matches(self, or_thresholds=False, and_thresholds=False):
        """get_similarity_scores.

        Args:
            or_thresholds: a match is detected if similarity score in any metrics is greater than threshold
            and_thresholds: a match is detected if similarity score in all metrics is greater than threshold
        """
        if or_thresholds and and_thresholds:
            raise ValueError(
                'Cannot trim result by both OR and AND thresholds')
        self.run()
        match_dict = {}
        for name, score_dict in self.__similarity_matrix.items():
            for other_name, scores in score_dict.items():
                key = hash(name) ^ hash(other_name)
                match = {}
                match['source1'] = name
                match['source2'] = other_name
                match['scores'] = scores
                match_dict[key] = match

        matches = list(match_dict.values())

        no_trimmed = 0
        if not or_thresholds and not and_thresholds:
            no_trimmed = len(matches)
        elif or_thresholds:
            for i in range(len(matches)):
                for metric, score in matches[i]['scores'].items():
                    if score > self.__thresholds[metric]:
                        matches[no_trimmed] = matches[i]
                        no_trimmed += 1
                        break
        elif and_thresholds:
            for i in range(len(matches)):
                check = True
                for metric, score in matches[i]['scores'].items():
                    if score < self.__thresholds[metric]:
                        check = False
                if check:
                    matches[no_trimmed] = matches[i]
                    no_trimmed += 1


        return self.sort_matches(matches[:no_trimmed], by='sum')

    def save_matches_to_csv(self, filepath, or_thresholds=False, and_thresholds=False):
        """save_matches_to_csv.
        Args:
            filepath: save to filepath
            or_thresholds: see get_matches, use get_matches 
            and_thresholds:
        """
        matches = self.get_matches(or_thresholds, and_thresholds)
        new_matches = []
        for match in matches:
            dic = {}
            dic['source1'] = match['source1']
            dic['source2'] = match['source2']
            for metric, score in match['scores'].items():
                dic[metric] = score
            new_matches.append(dic)
        df_data = pd.DataFrame.from_dict(new_matches)
        name_file = 'result_' + str(int(time.time())) + '.csv'
        df_data.to_csv(os.path.join(filepath, name_file))

    def save_as_html(self, output_dir='./', or_thresholds=False, and_thresholds=True, align=True):
        """save_as_html.
            use self.__alignment_matrix to align 2 source, 

        Args:
            trimmed:
            output_dir: save all html files in output_dir, if output_dir=None -> donot save
        Return:
            ret: A dictionary of html files. example: {'summary.html': HTML1, 'match1.html': HTML2, ....}
        """

        def score_color(score):
            C = int(score*255)
            R = C
            G = 0
            B = 0
            span = '<span style="color: rgb({}, {}, {})">'.format(
                R, G, B) + str(format(score*100, '.2f')) + '%</span>'
            return span

        HTML1 = ""
        HTML2 = ""
        with open('./scoss/assets/summary.html', mode='r') as f:
            HTML1 = f.read()
        with open('./scoss/assets/comparison.html', mode='r') as f:
            HTML2 = f.read()

        print("Running...")
        matches = self.get_matches(or_thresholds, and_thresholds)

        if len(matches) == 0:
            heads = []
            links = []
        else:
            heads = ['source1', 'source2']
            heads.extend(matches[0]['scores'].keys())
            links = []
            for match in matches:
                link = copy.deepcopy(match)
                for metric, score in match['scores'].items():
                    link['scores'][metric] = score_color(score) 
                links.append(links)
            links = matches 

        print("Saving summary...")
        page = Environment().from_string(HTML1).render(heads=heads, links=links)
        with open(os.path.join(output_dir, 'summary.html'), 'w') as file:
            file.write(page)

        if align:
            print("Aligning...")
            for i in range(len(matches)):
                src1 = self.__sources[matches[i]['source1']]
                src2 = self.__sources[matches[i]['source2']]
                matches[i]['alignments'] = self.__metric_list.align_source(src1, src2) 

            print("Saving alignments...")


            heads = ['source1', 'source2']
            heads.extend(matches[0]['scores'].keys())
            links = []
            index_file = 0
            for match in matches:
                dic = {}
                dic['source1'] = match['source1']
                dic['source2'] = match['source2']
                dic['scores'] = {}
                dic['alignments'] = {}
                for metric, alignment in match['alignments'].items():
                    data1 = self.__sources[dic['source1']].source_str
                    data2 = self.__sources[dic['source2']].source_str

                    data1 = [i.replace('<', '&lt').replace(
                        '>', '&gt') for i in data1.split('\n')]
                    data2 = [i.replace('<', '&lt').replace(
                        '>', '&gt') for i in data2.split('\n')]

                    html1 = ''
                    html2 = ''
                    for line in alignment:

                        if line[0] == -1:

                            html1 += '<pre >  </pre>'
                            temp2 = '<pre >' + \
                                str(line[1]) + '	' + \
                                data2[line[1]-1] + '</pre>'
                            html2 += temp2
                        elif line[1] == -1:
                            html2 += '<pre >  </pre>'
                            temp1 = '<pre >' + \
                                str(line[0]) + '	' + \
                                data1[line[0]-1] + '</pre>'
                            html1 += temp1
                        elif line[0] != -1 and line[0] != -1:
                            index1 = line[0]
                            index2 = line[1]
                            if line[2] >= 0.25 and line[2] < 0.75:
                                temp1 = '<pre style="color: #ffb600">' + \
                                    str(line[0]) + '	' + \
                                    data1[line[0]-1] + '</pre>'
                                html1 += temp1
                                temp2 = '<pre style="color: #ffb600">' + \
                                    str(line[1]) + '	' + \
                                    data2[line[1]-1] + '</pre>'
                                html2 += temp2
                            elif line[2] >= 0.75:
                                temp1 = '<pre style="color: red">' + \
                                    str(line[0]) + '	' + \
                                    data1[line[0]-1] + '</pre>'
                                html1 += temp1
                                temp2 = '<pre style="color: red">' + \
                                    str(line[1]) + '	' + \
                                    data2[line[1]-1] + '</pre>'
                                html2 += temp2
                            else:
                                temp1 = '<pre style="color: black">' + \
                                    str(line[0]) + '	' + \
                                    data1[line[0]-1] + '</pre>'
                                html1 += temp1
                                temp2 = '<pre style="color: black">' + \
                                    str(line[1]) + '	' + \
                                    data2[line[1]-1] + '</pre>'
                                html2 += temp2
                    name_file = 'comparison_' + \
                        str(index_file) + '.html'
                    index_file += 1
                    span = score_color(match['scores'][metric])
                    dic['scores'][metric] = span
                    dic['alignments'][metric] = name_file
                    compe = Environment().from_string(HTML2).render(file1=match['source1'], file2=match['source2'],
                                                                    metric=metric, score=span,
                                                                    data1=html1, data2=html2)
                    with open(os.path.join(output_dir, name_file), 'w') as file:
                        file.write(compe)
                links.append(dic)

            page = Environment().from_string(HTML1).render(heads=heads, links=links)
            with open(os.path.join(output_dir, 'summary.html'), 'w') as file:
                file.write(page)
        print("Done!")
