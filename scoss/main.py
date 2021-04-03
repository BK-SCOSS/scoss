from __future__ import absolute_import

from scoss.metrics.metric_list import MetricList
from scoss.my_source import MySource

import os

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

    
