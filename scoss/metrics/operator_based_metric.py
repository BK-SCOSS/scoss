# -*- coding: utf-8 -*-
"""
    code-similarity.operator_based_metric
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    DESCRIPTION
    The algorithms on this file are strongly inspired by Similarity System of Virtual Programming Lab (Moodle)

    :copyright: (c) 2020 by Ngoc Bui.
    :license: MIT LICENSE, see LICENSE for more details.
"""

from __future__ import absolute_import

from scoss.metrics.metric import Metric
from scoss.metrics.token_based_metric import TokenBasedMetric
from sctokenizer.token import TokenType

from abc import ABC, abstractmethod
import hashlib


class OperatorBasedMetric(ABC, TokenBasedMetric):

    def line_diff(self, line1, line2):
        score = super(OperatorBasedMetric, self).line_diff(line1, line2)
        if score == 1.0:
            return score
        else:
            line1 = self.normalize_tokens(line1)
            line2 = self.normalize_tokens(line2)
            return 0.5 * self.is_equal_tokens(line1, line2)

    @abstractmethod
    def evaluate(self, source1, source2):
        pass


class CountOperator(OperatorBasedMetric):
    """CountOperator.
    """

    name = 'count_operator'

    def evaluate(self, source1, source2):
        if source1.lang != source2.lang:
            raise ValueError(
                'source1 and source2 is written on different language')
        vecfrec1 = source1.get_vecfrec()
        vecfrec2 = source2.get_vecfrec()
        diff1 = 0
        taken = 0
        for key1 in vecfrec1.keys():
            if key1 in vecfrec2:
                if vecfrec1[key1] != vecfrec2[key1]:
                    diff1 += 1
                taken += 1
            else:
                diff1 += 1
        diff2 = len(vecfrec2) - taken
        if len(vecfrec1) + len(vecfrec2) == 0:
            return 0
        return (1 - ((diff1 + diff2) / (len(vecfrec1) + len(vecfrec2))))



class SetOperator(OperatorBasedMetric):
    """SetOperator.
    """

    name = 'set_operator'

    def evaluate(self, source1, source2):
        if source1.lang != source2.lang:
            raise ValueError(
                'source1 and source2 is written on different language')
        vecfrec1 = source1.get_vecfrec()
        vecfrec2 = source2.get_vecfrec()
        size1 = source1.get_size()
        size2 = source2.get_size()
        diff = 0
        taken = 0
        for key1 in vecfrec1.keys():
            if key1 in vecfrec2:
                diff += abs(vecfrec2[key1] - vecfrec1[key1])
                taken += vecfrec2[key1]
            else:
                diff += vecfrec1[key1]
        diff += size2 - taken
        if size1 + size2 == 0:
            return 0
        return (1 - (diff/(size1+size2)))

class HashOperator(OperatorBasedMetric):
    """HashOperator.

    """
    name = 'hash_operator'

    def evaluate(self, source1, source2):
        if source1.lang != source2.lang:
            raise ValueError(
                'source1 and source2 is written on different language')
        hashes1 = source1.get_hash()
        hashes2 = source2.get_hash()
        size1 = source1.get_size()
        size2 = source2.get_size()
        diff = 0
        taken = 0
        for key1 in hashes1.keys():
            if key1 in hashes2:
                diff += abs(hashes2[key1] - hashes1[key1])
                taken += hashes2[key1]
            else:
                diff += hashes1[key1]
        diff += size2 - taken
        if size1 + size2 == 0:
            return 0
        return (1-(diff / (size1 + size2)))

