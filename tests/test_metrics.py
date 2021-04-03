from sctokenizer import Source
from scoss.metrics.token_based_metric import TokenBasedMetric
from scoss.metrics import CountOperator, SetOperator, HashOperator

src1 = Source.from_file('./tests/data/a.cpp')
src2 = Source.from_file('./tests/data/b.cpp')

def test_token_based_metric():
    metric = TokenBasedMetric()
    a = metric.evaluate(src1, src2)
    print(a)

    diff = metric.align_source(src1, src2)
    print(diff)

def test_count_operator():
    metric = CountOperator()

    a = metric.evaluate(src1, src2)
    print(a)

    diff = metric.align_source(src1, src2)
    print(diff)

def test_set_operator():
    metric = SetOperator()

    a = metric.evaluate(src1, src2)
    print(a)

    diff = metric.align_source(src1, src2)
    print(diff)


def test_hash_operator():
    metric = HashOperator()

    a = metric.evaluate(src1, src2)
    print(a)

    diff = metric.align_source(src1, src2)
    print(diff)

if __name__ == '__main__':
    # test_token_based_metric()
    # test_count_operator()
    # test_set_operator()
    test_hash_operator()

