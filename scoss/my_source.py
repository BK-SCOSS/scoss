from __future__ import absolute_import

from sctokenizer import Source, TokenType

import hashlib
import os

LANG_MAP = {
    'cc': 'cpp',
    'py': 'python',
}

class MySource(Source):
    def __init__(self, source_str, lang=None, name=None):
        super(MySource, self).__init__(source_str, lang, name)
        self.normalized_tokens = None
        self.vecfrec = None
        self.hashes = None
        self.size = None
        self.lines = None

    @classmethod
    def from_file(cls, filepath, lang=None, name=None):
        """
            return the Source object
            :rtype: Source
        """
        with open(filepath) as f:
            source_str = f.read()
        if lang is None:
            ext = os.path.splitext(filepath)[1][1:]
            lang = LANG_MAP[ext]
        if name is None:
            name = filepath
        return MySource(source_str, lang, name)

    @classmethod
    def from_str(cls, source_str, lang=None, name=None):
        """
            return the Source object
            :rtype: Source
        """
        if lang is None:
            lang = cls.detect_language(source_str)
        return MySource(source_str, lang, name)


    def get_lines(self):
        if self.lines is not None:
            return self.lines

        tokens = self.tokenize()
        if len(tokens) == 0:
            return []

        lines = [[] for _ in range(tokens[-1].line)]
        for token in tokens:
            lines[token.line-1].append(token)

        self.lines = lines
        return lines

    def get_normalized_tokens(self):
        """get_tokens_normalize.
            only keep tokens are operator or special symbol

        Args:
            tokens:
        """
        if self.normalized_tokens is not None:
            return self.normalized_tokens

        tokens = self.tokenize()
        openning_bracket = "([{"
        new_tokens = []
        for token in tokens:
            if token.token_value in openning_bracket:
                continue
            if token.token_type == TokenType.OPERATOR or \
                    token.token_type == TokenType.SPECIAL_SYMBOL:
                new_tokens.append(token)
        self.normalized_tokens = new_tokens
        return new_tokens

    def get_size(self):
        """
        get number of tokens
        """
        tokens = self.get_normalized_tokens() 
        return len(tokens)

    def get_vecfrec(self):
        if self.vecfrec is not None:
            return self.vecfrec

        tokens = self.get_normalized_tokens()
        self.vecfrec = {}
        for token in tokens:
            if token.token_value in self.vecfrec:
                self.vecfrec[token.token_value] += 1
            else:
                self.vecfrec[token.token_value] = 1
        return self.vecfrec


    def get_hash(self):
        if self.hashes is not None:
            return self.hashes

        hashes = {}
        last = ['', '', '', '']
        tokens = self.get_normalized_tokens()
        for token in tokens:
            for i in range(len(last)-1):
                last[i] = last[i+1]
            last[-1] = token.token_value
            item = ''
            for i in range(len(last)):
                item += last[i]
            has = int(hashlib.sha256(item.encode(
                'utf-8')).hexdigest(), 16) % 10**3
            if has in hashes:
                hashes[has] += 1
            else:
                hashes[has] = 1
        self.hashes = hashes
        return hashes
