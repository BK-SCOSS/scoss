from __future__ import absolute_import

from scoss.metrics.metric_list import MetricList
from scoss.my_source import MySource
from scoss.scoss import Scoss
from scoss import smoss
from jinja2 import Environment
import os
import sys
import csv
from tqdm import tqdm

def check_similarity(metric_name, src_str_1, src_str_2, lang):
    metric = MetricList([metric_name])
    src1 = MySource.from_str(src_str_1, lang) 
    src2 = MySource.from_str(src_str_2, lang)
    
    scores = metric.evaluate(src1, src2)
    return scores[metric_name]

def align_source(metric_name, src_str_1, src_str_2, lang):
    metric = MetricList([metric_name])
    src1 = MySource.from_str(src_str_1, lang) 
    src2 = MySource.from_str(src_str_2, lang)
    
    alignments = metric.align_source(src1, src2)
    return alignments[metric_name]

def get_all_files(contest_path):
    subdirs = [x[0] for x in os.walk(contest_path)]
    all_files = {}
    for i in range(1, len(subdirs)):
        listOfFiles = []
        subdir = subdirs[i]
        subdir_name = os.path.basename(os.path.normpath(subdir))
        for (dirpath, _, filenames) in os.walk(subdir):
            listOfFiles += [os.path.join(dirpath, file) for file in filenames]
        for f in listOfFiles:
            if os.stat(f).st_size == 0:
                continue
            ext = f.split('.')[-1]
            if (subdir_name, ext) in all_files:
                all_files[subdir_name, ext].append(f)
            else:
                all_files[subdir_name, ext] = [f]
    return all_files

def create_dir(filepath):
    wdir = filepath
    if os.path.isfile(os.path.abspath(filepath)):
        wdir = os.path.dirname(filepath)
    if not os.path.exists(wdir):
        try:
            os.makedirs(wdir)
        except OSError: # Guard against race condition
            pass

def get_all_plagiarism(input_dir, output_dir, threshold_combination_type='AND', moss_threshold=None,
    count_operator_threshold=None, set_operator_threshold=None, hash_operator_threshold=None):
    if moss_threshold == None and count_operator_threshold == None and \
        set_operator_threshold == None and hash_operator_threshold == None:
        print('Please choose at least 1 metric from [moss, count_operator, set_operator, hash_operator]', file=sys.stderr)
        sys.exit(-1)
    if not threshold_combination_type:
        threshold_combination_type = 'AND'
    all_files = get_all_files(input_dir)
    output_dir = os.path.join(output_dir, 'plagiarism_report_{}/'.format(os.path.basename(os.path.normpath(input_dir))))
    result_dir = os.path.join(output_dir, 'source_code_comparisons/')
    create_dir(result_dir)

    with open('./scoss/assets/summary.html', mode='r') as f:
        HTML1 = f.read()
    with open('./scoss/assets/comparison.html', mode='r') as f:
        HTML2 = f.read()
    heads = None
    all_links = []
    for (dir_name, ext), file_list in all_files.items(): 
        cur_dir_name = '{}_{}'.format(dir_name, ext)
        cur_dir_path = os.path.join(result_dir, cur_dir_name)
        # print(cur_dir_path)
        create_dir(cur_dir_path)
        scoss_matches_dict = {}
        if count_operator_threshold != None or \
            set_operator_threshold != None or \
            hash_operator_threshold != None:
            print('Getting scoss plagiarism for {} language in problem {}...'.format(ext, dir_name))
            try:
                sc = Scoss(lang=ext)
            except ValueError as er:
                print(er)
                continue
            if count_operator_threshold != None:
                sc.add_metric('count_operator', threshold=count_operator_threshold)
            if set_operator_threshold != None:
                sc.add_metric('set_operator', threshold=set_operator_threshold)
            if hash_operator_threshold != None:
                sc.add_metric('hash_operator', threshold=hash_operator_threshold)
            for f in file_list:
                user_filename = os.path.basename(f)
                problem_dir = os.path.basename(os.path.dirname(f))
                sc.add_file(f, '{}_{}'.format(problem_dir, user_filename))
            sc.run()
            if threshold_combination_type.upper() == 'AND':
                scoss_matches = sc.get_matches(or_thresholds=False, and_thresholds=True)
            else: # Be careful
                scoss_matches = sc.get_matches(or_thresholds=True, and_thresholds=False)
            for match in scoss_matches:
                if match['source1'] < match['source2']:
                    scoss_matches_dict[match['source1'], match['source2']] = match['scores']
                else:
                    scoss_matches_dict[match['source2'], match['source1']] = match['scores']
            print('Successfully getting scoss plagiarism for {} language in problem {}!'.format(ext, dir_name))

        smoss_matches_dict = {}
        if moss_threshold != None:
            print('Getting scoss plagiarism for {} language in problem {}...'.format(ext, dir_name))
            try:
                sm = smoss.SMoss(lang=ext)
            except:
                print('Unsupported languge: ', ext)
                continue
            sm.set_threshold(moss_threshold)
            for f in file_list:
                user_filename = os.path.basename(f)
                problem_dir = os.path.basename(os.path.dirname(f))
                sm.add_file(f, '{}_{}'.format(problem_dir, user_filename))
            sm.run()
            smoss_matches = sm.get_matches()
            for match in smoss_matches:
                if match['source1'] < match['source2']:
                    smoss_matches_dict[match['source1'], match['source2']] = match['scores']
                else:
                    smoss_matches_dict[match['source2'], match['source1']] = match['scores']
            print('Successfully getting smoss plagiarism for {} language in problem {}!'.format(ext, dir_name))
        ###################################################################################
        all_matches_dict = {}    
        # print('scoss_matches_dict = ', scoss_matches_dict)   
        # print('smoss_matches_dict = ', smoss_matches_dict)   
        if not scoss_matches_dict and not smoss_matches_dict:
            continue
        elif not scoss_matches_dict or not smoss_matches_dict:
            scoss_matches_dict.update(smoss_matches_dict)
            all_matches_dict = scoss_matches_dict
        else:
            for k, v in scoss_matches_dict.items():
                if k in smoss_matches_dict:
                    all_matches_dict[k] = v
                    all_matches_dict[k].update(smoss_matches_dict[k])
                elif threshold_combination_type == 'AND':
                    continue
                else: # OR_threshold
                    all_matches_dict[k] = v
                    all_matches_dict[k].update({'moss_score':0})
        for k, v in all_matches_dict.items():
            scores = list(all_matches_dict[k].values())
            all_matches_dict[k]['average_score'] = sum(scores) / len(scores)

        # Sort all_matches_dict by average_score
        all_matches_dict = {k: v for k, v in sorted(all_matches_dict.items(), key=lambda item: -item[1]['average_score'])}
        # all_matches_dict = sorted(all_matches_dict, key = lambda i: float(i['scores']['average_score']), reverse=True)
        values_view = all_matches_dict.values()
        value_iterator = iter(values_view)
        first_score = next(value_iterator)
        heads = ['source1', 'source2'] + list(first_score.keys())
        links = []
        print('Creating results')
        for (src1, src2), scores in tqdm(all_matches_dict.items()):
            dic = {}
            dic['source1'] = src1
            dic['source2'] = src2
            dic['scores'] = {}
            dic['alignments'] = {}
            # print('scores =', scores)
            for metric in scores.keys():
                C = int(scores[metric]*255)
                R = C
                G = 0
                B = 0
                span = '<span style="color: rgb({}, {}, {})">'.format(R,G,B) + str(format(scores[metric]*100, '.2f')) +'%</span>'
                if metric == 'average_score':
                    dic['scores'][metric] = span
                    links.append(dic)
                    continue
                elif metric == 'moss_score':
                    try:
                        compe = sm.get_matches_file()[src1][src2]
                    except KeyError:
                        compe = ''
                else:
                    source_str1 = sc.get_sources()[src1].source_str
                    source_str2 = sc.get_sources()[src2].source_str
                    data1 = [i.replace('<', '&lt').replace('>', '&gt') for i in source_str1.split('\n')]
                    data2 = [i.replace('<', '&lt').replace('>', '&gt') for i in source_str2.split('\n')]
                    html1 = ''
                    html2 = ''
                    alignment = align_source(metric, source_str1, source_str2, ext)
                    for line in alignment:
                        if line[0] == -1 :
                            html1 += '<pre >  </pre>'
                            temp2 = '<pre >'+  str(line[1])+ '	'+  data2[line[1]-1] + '</pre>'
                            html2 += temp2
                        elif line[1] == -1 :
                            html2 += '<pre >  </pre>'
                            temp1 = '<pre >'+  str(line[0])+ '	'+  data1[line[0]-1] + '</pre>'
                            html1 += temp1
                        elif line[0] != -1 and line[0] != -1:
                            if line[2] >=0.25 and line[2] <0.75:
                                temp1 = '<pre style="color: #ffb600">'+  str(line[0])+ '	'+  data1[line[0]-1] + '</pre>'
                                html1 += temp1
                                temp2 = '<pre style="color: #ffb600">'+  str(line[1])+ '	'+  data2[line[1]-1] + '</pre>'
                                html2 += temp2
                            elif line[2] >= 0.75:
                                temp1 = '<pre style="color: red">'+  str(line[0])+ '	'+  data1[line[0]-1] + '</pre>'
                                html1 += temp1
                                temp2 = '<pre style="color: red">'+  str(line[1])+ '	'+  data2[line[1]-1] + '</pre>'
                                html2 += temp2
                            else:
                                temp1 = '<pre style="color: black">'+  str(line[0])+ '	'+  data1[line[0]-1] + '</pre>'
                                html1 += temp1
                                temp2 = '<pre style="color: black">'+  str(line[1])+ '	'+  data2[line[1]-1] + '</pre>'
                                html2 += temp2
                    compe = Environment().from_string(HTML2).render(file1=match['source1'], file2=match['source2'], \
                                    metric=metric, score=span, \
                                    data1=html1, data2=html2)
                name_file = '{}_{}_{}.html'.format(src1, src2, metric)
                # create_dir(name_file)
                with open(os.path.join(cur_dir_path, name_file), 'w', encoding='utf-8') as file:
                    file.write(compe)
                dic['scores'][metric] = span
                dic['alignments'][metric] = 'source_code_comparisons/{}/{}'.format(cur_dir_name, name_file)
                links.append(dic)
        all_links += links

        page = Environment().from_string(HTML1).render(heads=heads, links=links)
        with open(os.path.join(output_dir, 'summary_{}.html'.format(cur_dir_name)), 'w') as file:
            file.write(page)

    if not heads:
        print("There is no plagiarism activities!")
        sys.exit(0)
    all_links = sorted(all_links, key = lambda i: i['scores']['average_score'].split('">')[-1].split('%')[0], reverse=True)
    page = Environment().from_string(HTML1).render(heads=heads, links=all_links)
    with open(os.path.join(output_dir, 'all_summary.html'), 'w') as file:
        file.write(page)

    with open(os.path.join(output_dir,'all_summary.csv'), mode='w', newline='') as f:
        writer = csv.writer(f) 
        writer.writerow(heads)
        for link in all_links:
            row = [link['source1'], link['source2']]
            for k, v in link['scores'].items():
                row.append(v.split('">')[-1].split('%')[0]+'%')
            writer.writerow(row)
        
        


    

    
