from sctokenizer import Source
from scoss.metrics.token_based_metric import TokenBasedMetric
from scoss.metrics import CountOperator, SetOperator, HashOperator
from scoss import Scoss
from app.config import URL
import requests
import time
import scoss

# src1 = Source.from_file('./data/a.cpp')
# src2 = Source.from_file('./tests/data/b.cpp')
# for token in src2.tokenize():
#     print(token)

def test_scoss():
    start_time = time.time()
    sc = Scoss(lang='cpp')
    # sc.add_metric('count_operator')
    # sc.add_metric('set_operator')
    # sc.add_metric('hash_operator')
    sc.add_file_by_wildcard('./tests/olympic-submission/ALICEADD/*')
    print("preparation cost : ", time.time() - start_time)

    start_time = time.time()
    sc.run()
    print(len(sc.get_matches()))
    # sc.save_as_html('./tests/result/', and_thresholds=True)

    print("running time cost : ", time.time() - start_time)
    

def test_scoss_cmd():
    src_str_1 = open('./tests/data/a.cpp').read()
    src_str_2 = open('./tests/data/b.cpp').read()
    print(scoss.align_source('count_operator', src_str_1, src_str_2, 'cpp'))

def test_scoss_or():
    sc = Scoss(lang='cpp')
    sc.add_metric('count_operator', 1.0)
    sc.add_metric('set_operator')
    sc.add_file('./tests/data/a.cpp')
    sc.add_file('./tests/data/b.cpp')
    sc.add_file('./tests/data/c.cpp')
    sc.run()
    print(sc.get_matches(or_thresholds=True))

def test_scoss_and():
    sc = Scoss(lang='cpp')
    sc.add_metric('count_operator', 1.0)
    sc.add_metric('set_operator')
    sc.add_file('./tests/data/a.cpp')
    sc.add_file('./tests/data/b.cpp')
    sc.add_file('./tests/data/c.cpp')
    sc.run()
    print(sc.get_matches(and_thresholds=True))
    sc.save_as_html('./tests/result/', align=False)

def test_scoss_csv():
    sc = Scoss(lang='cpp')
    sc.add_metric('count_operator')
    sc.add_metric('set_operator')
    sc.add_file('./tests/data/a.cpp')
    sc.add_file('./tests/data/b.cpp')
    sc.add_file('./tests/data/c.cpp')
    sc.run()
    sc.save_matches_to_csv('tests/result/')

def test_scoss_save_html():
    sc = Scoss(lang='cpp')
    sc.add_metric('count_operator', 0.0)
    sc.add_metric('set_operator')
    # sc.add_file('./tests/data/a.cpp', mask='Thai')
    src1 = Source.from_file('./tests/data/a.cpp')
    src2 = Source.from_file('./tests/data/b_1.cpp')
    sc.add_source_str(src1.source_str, mask='a.cpp')
    print(src1.source_str)
    strs = """#include <stdio.h>\r\n#include <conio.h>\r\n\r\nvoid main()\r\n{\r\n    int i=0, s=0,n;\r\n    printf("Nhap vao so n:");\r\n    scanf("%d", &n);\r\n    while(i++<n)\r\n        s=s+i;\r\n    printf("Tong la: %d\\n", s);\r\n    getch();\r\n}\r\n"""
    sc.add_source_str(strs, mask='b_1.cpp')
    print(src2.source_str)
    # sc.add_file('./tests/data/c.cpp', mask='Ngoc')
    sc.run()
    print(sc.get_matches())
    # sc.save_as_html('./tests/result/', and_thresholds=True)

def cal_scoss(sources, metrics):
    sc = Scoss(lang='cpp')
    sc.add_metric('count_operator', 0.0)
    sc.add_metric('set_operator')
    for source in sources:
        
        print('--------------')
        if source['mask'] == '':
            print(source['pathfile'])
            src2 = Source.from_str(source['source_str'].decode('utf-8'))
            for token in src2.tokenize():
                print(token)
            # sc.add_source_str(source['source_str'], mask=source['pathfile'])
        else:
            pass
		# 	sc.add_source_str(source['source_str'], mask=source['mask'])
	# sc.add_file('./tests/data/c.cpp', mask='Ngoc')
    # sc.run()
    # print(sc.get_matches())

def test_run():
    strs = '#include <stdio.h>\r\n#include <conio.h>\r\n\r\nvoid main()\r\n{\r\n    int i=0, s=0,n;\r\n    printf("Nhap vao so n:");\r\n    scanf("%d", &n);\r\n    while(i++<n)\r\n        s=s+i;\r\n    printf("Tong la: %d\\n", s);\r\n    getch();\r\n}\r\n'
    src2 = Source.from_str(strs)
    for token in src2.tokenize():
        print(token)

if __name__ == '__main__':
    test_scoss()
    # test_run()
    # python3 tests/test_scoss.py 
    # test_scoss_or()
    # test_scoss_and()
    # test_scoss_csv()
    # url = URL + '/api/problems/' + str(1602940099000)
    # req = requests.get(url)
    # data_problem = req.json()
    # print(data_problem)
    # print(data_problem['sources'][-1])
    # src2 = Source.from_str(data_problem['sources'][-1]['source_str'])
    # for token in src2.tokenize():
    #     print(token)
    # cal_scoss(data_problem['sources'], data_problem['metrics'])

    # test_scoss_save_html()
