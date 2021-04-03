from __future__ import absolute_import

import os
from scoss.utils.parameters import *

def get_filename(filepath):
    return os.path.basename(filepath)

def get_basename(filepath):
    filename = get_filename(filepath)
    return os.path.splitext(filename)[0]
    
def check_language(lang):
    if lang in SUPPORTED_LANGUGES:
        return lang
    if lang in LANG_MAP:
        return LANG_MAP[lang]
    raise ValueError("Unsupported languge")

