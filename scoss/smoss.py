# -*- coding: utf-8 -*-
"""
    code-similarity.smoss
    ~~~~~~~~~~~~~~~~~~~~~

    the implement base on mosspy: https://github.com/soachishti/moss.py
"""

import os
import glob
import enum
import time
import pandas as pd
import socket
from collections import OrderedDict
from bs4 import BeautifulSoup
from jinja2 import Environment
from sctokenizer import Source
import requests

from scoss.utils import check_language

try:
    from urllib.request import urlopen
except ImportError:
    from urllib2 import urlopen

class SMossState(enum.Enum):
    INIT = 0 
    RUNNING = 1 
    CLOSE = 3

class SMoss():
    __id = 0
    server = 'moss.stanford.edu'
    port = 7690
    languages = (
            "c",
            "cc",
            "java",
            "ml",
            "pascal",
            "ada",
            "lisp",
            "scheme",
            "haskell",
            "fortran",
            "ascii",
            "vhdl",
            "verilog",
            "perl",
            "matlab",
            "python",
            "mips",
            "prolog",
            "spice",
            "vb",
            "csharp",
            "modula2",
            "a8086",
            "javascript",
            "plsql")

    def __init__(self, lang, userid=32193):
        
        SMoss.__id += 1
        self.id = SMoss.__id

        self.__userid = userid

        self.__lang = check_language(lang)
        self.__state = SMossState.INIT
        self.__threshold = 0
        self.__sources = OrderedDict()

        self.__matches = []
        self.__similarity_matrix = dict()
        self.__matches_file = dict()

        self.__options = {
                    "l": "c",
                    "m": 10,
                    "d": 0,
                    "x": 0,
                    "c": "",
                    "n": 250
                }

        if self.__lang in self.languages:
            self.__options["l"] = self.__lang

        self.__base_files = OrderedDict()

    def get_language(self):
        return self.__lang

    def get_options(self):
        return self.__options

    def set_ignore_limit(self, limit):
        self.__options['m'] = limit

    def set_comment_string(self, comment):
        self.__options['c'] = comment

    def set_number_of_matching_files(self, n):
        if n > 1:
            self.__options['n'] = n

    def set_directory_mode(self, mode):
        self.__options['d'] = mode

    def set_experimental_server(self, opt):
        self.__options['x'] = opt

    def set_threshold(self, threshold: float):
        self.__threshold = threshold

    def add_base_file(self, file, mask=None):
        if self.__state != SMossState.INIT:
            raise ValueError('Cannot add file after running')
        if mask is None:
            mask = file
        if os.path.isfile(file) and os.path.getsize(file) > 0:
            src = Source.from_file(file, lang=self.__lang, name=mask)
            self.__base_files[mask] = src
        else:
            raise Exception("addBaseFile({}) => File not found or is empty.".format(file))
    
    def add_base_source_str(self, source_str, mask):
        if self.__state != SMossState.INIT:
            raise ValueError('Cannot add file after running')
        if mask in self.__sources.keys():
            raise ValueError(f'mask:{mask} is already exist')
        src = Source.from_str(source_str, lang=self.__lang)
        self.__sources[mask] = src

    def add_file(self, file, mask=None):
        if self.__state != SMossState.INIT:
            raise ValueError('Cannot add file after running')
        if mask is None:
            mask = file
        if mask in self.__sources.keys():
            raise ValueError(f'mask:{mask} is already exist')
        src = Source.from_file(file, lang=self.__lang, name=mask)
        self.__sources[mask] = src

    def update_file(self, file, mask=None):
        if self.__state != SMossState.INIT:
            raise ValueError('Cannot add file after running')
        if mask is None:
            mask = file
        src = Source.from_file(file, lang=self.__lang, name=mask)
        self.__sources[mask] = src

    def add_source_str(self, source_str, mask):
        if self.__state != SMossState.INIT:
            raise ValueError('Cannot add file after running')
        if mask in self.__sources.keys():
            raise ValueError(f'mask:{mask} is already exist')
        src = Source.from_str(source_str, lang=self.__lang)
        self.__sources[mask] = src

    def update_source_str(self, source_str, mask):
        if self.__state != SMossState.INIT:
            raise ValueError('Cannot add file after running')
        src = Source.from_str(source_str, lang=self.__lang)
        self.__sources[mask] = src

    def add_file_by_wildcard(self, dirpath, recursive=True):
        if self.__state == SMossState.INIT:
            print(dirpath)
            for file in glob.glob(dirpath, recursive=recursive):
                self.add_file(file)
        else:
            raise ValueError('Cannot add file after running')
        print(len(self.__sources))

    def get_matches(self):
        if self.__state == SMossState.INIT:
            self.run()
        matches = []
        for match in self.__matches:
            copied_match = match.copy()
            if 'link' in copied_match:
                del copied_match['link']
            matches.append(copied_match)
        return matches

    def get_similarity_matrix(self):
        if self.__state == SMossState.INIT:
            self.run()
        return self.__similarity_matrix

    def get_matches_file(self):
        if self.__state == SMossState.INIT:
            self.run()
        return self.__matches_file
    
    def save_matches_to_csv(self, filepath):
        if self.__state == SMossState.INIT:
            self.run()
        new_matches = []
        for match in self.__matches:
            dic = {}
            dic['source1'] = match['source1']
            dic['source2'] = match['source2']
            for metric, score in match['scores'].items():
                dic[metric] = score
            new_matches.append(dic)
        df_data = pd.DataFrame.from_dict(new_matches)
        name_file = 'result_' +str(int(time.time())) +'.csv'
        df_data.to_csv(os.path.join(filepath, name_file))

    def parse_html_table(self, url):
        html = urlopen(url).read().decode()
        soup = BeautifulSoup(html, features="lxml")
        tds = soup.find_all('td')
        i = 0
        self.__matches = []
        with open('./scoss/assets/smoss_comparison.html', mode='r') as f:
            big_html_string = f.read()
        bases = big_html_string.split('<<<>>>')
        while i < len(tds):
            score_str = tds[i].contents[0].contents[0][-4:-2]
            score_str = ''.join(c for c in score_str if c.isdigit())
            score = int(score_str)/100
            if score < self.__threshold:
                i += 3
                continue
            a_score = {'moss_score': score}
            src1 = tds[i].contents[0].contents[0].split()[0]
            src2 = tds[i+1].contents[0].contents[0].split()[0]

            # Construct matches
            a_match = {}
            a_match['source1'] = src1
            a_match['source2'] = src2
            a_match['scores'] = a_score
            a_match['link'] = tds[i].contents[0].attrs['href']
            self.__matches.append(a_match)

            # Construct similarity_matrix
            if src1 in self.__similarity_matrix:
                self.__similarity_matrix[src1][src2] = a_score
            else:
                self.__similarity_matrix[src1] = {src2:a_score}

            if src2 in self.__similarity_matrix:
                self.__similarity_matrix[src2][src1] = a_score
            else:
                self.__similarity_matrix[src2] = {src1:a_score}

            # # Construct matches_file
            base_url = os.path.dirname(a_match['link'])
            match_name = os.path.splitext(os.path.basename(a_match['link']))[0]
            html_strs = []
            more_urls = ['-top.html', '-0.html', '-1.html']
            for more_url in more_urls:
                html_str = self.url_content_to_str(base_url + '/' + match_name + more_url)
                html_strs.append(html_str)
            match_comparison = bases[0] + html_strs[0] + bases[1] + \
                            html_strs[1] + bases[2] + html_strs[2] + bases[3] 
            if src1 in self.__matches_file:
                self.__matches_file[src1][src2] = match_comparison
            else:
                self.__matches_file[src1] = {src2:match_comparison}

            if src2 in self.__matches_file:
                self.__matches_file[src2][src1] = match_comparison
            else:
                self.__matches_file[src2] = {src1:match_comparison}
            # with open(os.path.join('./tests/smoss_result/', 'big_all_html.html'), 'w') as file:
            #     file.write(big_html_string)
            i += 3

    def upload_file(self, s, src, mask, file_id, on_send):
        bin_str = src.source_str.encode() 
        size = len(bin_str)
        message = "file {0} {1} {2} {3}\n".format(
            file_id,
            self.__options['l'],
            size,
            mask
        )
        s.send(message.encode())
        s.send(bin_str)
        on_send(src)

    def send(self, on_send=lambda src: None):
        s = socket.socket()
        s.connect((self.server, self.port))

        s.send("moss {}\n".format(self.__userid).encode())
        s.send("directory {}\n".format(self.__options['d']).encode())
        s.send("X {}\n".format(self.__options['x']).encode())
        s.send("maxmatches {}\n".format(self.__options['m']).encode())
        s.send("show {}\n".format(self.__options['n']).encode())
        s.send("language {}\n".format(self.__options['l']).encode())

        recv = s.recv(1024)

        if recv == "no":
            s.send(b"end\n")
            s.close()
            raise Exception("send() => Language not accepted by server")

        for mask, src in self.__base_files.items():
            self.upload_file(s, src, mask, 0, on_send)

        index = 1
        for mask, src in self.__sources.items():
            self.upload_file(s, src, mask, index, on_send)
            index += 1

        s.send("query 0 {}\n".format(self.__options['c']).encode())

        response = s.recv(1024)

        s.send(b"end\n")
        s.close()
        return response.decode().replace("\n","")

    def run(self):
        if self.__state != SMossState.CLOSE:
            start_time = time.time()
            url = self.send()
            start_time = time.time()
            if url == '':
                raise ValueError("MOSS Server returned empty url. Please check userid.")
            self.parse_html_table(url)
            self.__state = SMossState.CLOSE
        else:
            raise ValueError("Can only execute run function once.")

    def url_content_to_str(self, url):
        # html_str = urlopen(url).read().decode()
        res = requests.get(url)
        return res.text

    def process_url(self, url, file_name, path):
        def save_html(url, file_name):
            html_str = self.url_content_to_str(url)
            with open(os.path.join(path, file_name), 'w') as file:
                file.write(html_str)

        save_html(url, file_name)
        html = self.url_content_to_str(url)
        soup = BeautifulSoup(html, 'lxml')
        base_url = os.path.dirname(url)
        for more_url in soup.find_all('frame'):
            file_name = more_url.get('src')   
            save_html(base_url + '/' + file_name, file_name)
            
    def save_as_html(self, output_dir=None):
        if self.__state == SMossState.INIT:
            self.run()
        HTML1 = ""
        with open('./scoss/assets/summary.html', mode='r') as f:
            HTML1 = f.read()

        if len(self.__matches) != 0:
            heads = [x for x in self.__matches[0].keys() if x != 'link']
            links = []
            index_file = 0
            for match in self.__matches:
                dic = {}
                dic['source1'] = match['source1']
                dic['source2'] = match['source2']
                dic['scores'] = {}
                name_file = 'comparison_' + str(index_file) +'.html'
                index_file += 1
                metric = 'moss_score'
                C = int(match['scores'][metric]*255)
                R = C
                G = 0
                B = 0;
                span = '<span style="color: rgb({}, {}, {})">'.format(R,G,B) + str(format(match['scores'][metric]*100, '.2f')) +'%</span>'
                dic['scores'][metric] = [name_file, span]
                links.append(dic)
                self.process_url(match['link'], name_file, output_dir)
            page = Environment().from_string(HTML1).render(heads=heads, links=links)
            with open(os.path.join(output_dir, 'summary.html'), 'w') as file:
                file.write(page)
    
    def set_metric_threshold(self, metric_name, threshold: float):
        raise ValueError("smoss doesn't support this function. Use set_threshold() instead.")

    def add_metric(self, metric, threshold: float=0.0, exist_ok=False):
        raise ValueError("smoss doesn't support this function.")

