
from sctokenizer import Source
from scoss.metrics.token_based_metric import TokenBasedMetric
from scoss.metrics import CountOperator, SetOperator, HashOperator
from scoss import Scoss

def test_scoss():
    sc = Scoss(lang='java')
    sc.add_metric('count_operator')
    sc.add_metric('set_operator')
    sc.add_file('./tests/data/43141512HieuLV_100.java')
    sc.add_file('./tests/data/45166531NgocVT_80.java')
    sc.run()
    print(sc.get_aligment_matrix())

if __name__ == '__main__':
    test_scoss()
