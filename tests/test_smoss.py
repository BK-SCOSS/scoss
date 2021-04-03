from sctokenizer import Source
from scoss import smoss

def test_smoss():
    sm = smoss.SMoss(lang='cpp')
    # print(sm.get_userid())
    # sm.add_file('./tests/data/a.cpp', "Thai")
    # sm.add_file('./tests/data/a.cpp', "Thai2")
    # sm.add_file('./tests/data/b.cpp', "Ngoc")
    # sm.add_file('./tests/data/b.cpp', "Ngoc2")
    # sm.add_file('./tests/data/c.cpp', "Vien")
    # sm.add_file('./tests/data/c.cpp', "Vien2")
    sm.add_file_by_wildcard("./tests/TTUD20201/GROUPUP/*.cpp")
    # sm.set_threshold(0.5)
    # sm.run()
    sm.run()
    # print(sm.get_lang())
    print(sm.get_matches())
    print(sm.get_matches_file())
    # print(sm.get_similarity_matrix())
    # sm.save_as_html('./tests/smoss_result/')
    # sm.save_matches_to_csv('./tests/smoss_result/')
    # print(sm.get_matches_file()['Ngoc']['Vien'])
    


if __name__ == '__main__':
    # python3 tests/test_scoss.py 
    # 1. url variable will be empty if userid is invalid
    # userid should be 5-digit long, e.g. 13579

    # 2. maybe moss server takes forever to return
    test_smoss()

