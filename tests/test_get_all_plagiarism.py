import scoss

def test():
    input_dir = 'tests/data/299721'
    output_dir = 'tests/data/result'
    scoss.get_all_plagiarism(input_dir, output_dir, threshold_combination_type='AND', moss_threshold=0,
    count_operator_threshold=0, set_operator_threshold=0, hash_operator_threshold=0)

if __name__ == '__main__':
    test()