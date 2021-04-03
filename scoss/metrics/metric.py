
from sctokenizer import Source

class Metric():
    name = None

    def __init__(self):
        pass

    def get_name(self):
        return self.name

    def evaluate(self, source1, source2):
        pass

    def evaluate_str(self, source_str1, source_str2, lang):
        src1 = Source.from_str(source_str1, lang=lang)
        src2 = Source.from_str(source_str2, lang=lang)
        return self.evaluate(src1, src2)

    def align_source(self, source1, source2):
        pass
        
