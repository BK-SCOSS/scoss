
from sctokenizer import Source
from scoss.metrics.token_based_metric import TokenBasedMetric
from scoss.metrics import CountOperator, SetOperator, HashOperator
from scoss import Scoss
import scoss

def test_scoss():
    sc = Scoss(lang='java')
    sc.add_metric('count_operator')
    sc.add_metric('set_operator')
    # sc.add_file('./tests/data/43141512HieuLV_100.java')
    # sc.add_file('./tests/data/45166531NgocVT_80.java')
    sc.add_file('tests/data/b_1.cpp')
    sc.add_file('tests/data/b_2.cpp')
    sc.run()
    src_str_1 = open('./tests/data/a.cpp').read()
    print('src_str_1 = ', src_str_1)
    src_str_2 = open('./tests/data/b.cpp').read()
    print(scoss.align_source('count_operator', src_str_1, src_str_2, 'cpp'))

if __name__ == '__main__':
    test_scoss()
