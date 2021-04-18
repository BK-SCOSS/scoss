# scoss
A Source Code Similarity System - SCOSS

There are four supported metrics:

* `count_operator`: A metric that counts operators in source-code to calculate similarity score.
* `set_operator`: A metric that checks the presence of operators in source-code to calculate similarity score.
* `hash_operator`: A metric that uses the combination of adjacent operators to calculate similarity score.
* `SMoss`: A wrapper of [MOSS](http://theory.stanford.edu/~aiken/moss/) (the same as `mosspy`).

## Installations
This package requires `python 3.6` or later.
```sh
pip install scoss
```

## Usages
You can use SCOSS as a Command Line Interface, or a library in your project, or web-app interface

### Command Line Interface (CLI)
See document by passing ```--help``` argument.
```
scoss --help
Usage: scoss [OPTIONS]

Options:
  -i, --input-dir TEXT      Input directory.  [required]
  -o, --output-dir TEXT           Output directory.
  -tc, --threshold-combination [AND|OR]
                                  AND: All metrics are greater than threshold.
                                  OR: At least 1 metric is greater than
                                  threshold.

  -mo, --moss FLOAT RANGE         Use moss metric and set up moss threshold.
  -co, --count-operator FLOAT RANGE
                                  Use count operator metric and set up count
                                  operator threshold.

  -so, --set-operator FLOAT RANGE
                                  Use set operator metric and set up set
                                  operator threshold.

  -ho, --hash-operator FLOAT RANGE
                                  Use hash operator metric and set up hash
                                  operator threshold.

  --help                          Show this message and exit.
```
To get plagiarism report of a directory containing source code files, add ```-i/ --input-dir``` option. Add at least 1 similarity metric in [```-mo/--moss```, ```-co/--count-operator```, ```-so/--set-operator```, ```-ho/--hash-operator```] and its threshold (in range [0,1]). If using 2 or more metrics, you need to define how they should be combined using ```-tc/--threshold-combination``` (```AND``` will be used by default).

Basic command: ```scoss -i path/to/source_code_dir/ -tc OR -co 0.1 -ho 0.1 -mo 0.1 -o another_path/to/plagiarism_report/```
### Using as a library

1. Define a `Scoss` object and register some metrics:
```python
from scoss import Scoss
sc = Scoss(lang='cpp')
# only show pairs that have similarity score > threshold
sc.add_metric('count_operator', threshold=0.7) 
sc.add_metric('set_operator', threshold=0.5)
```

2. Register source-codes to defined `scoss` object:
```python
sc.add_file('./tests/data/a.cpp')
sc.add_file('./tests/data/b.cpp')
sc.add_file('./tests/data/c.cpp')
# or add by wide-card
sc.add_file_by_wildcard('./tests/data/problem_A_*.cpp')
```

3. Run `Scoss` and get results:
```python
sc.run()
# filter results by combine thresholds from different metrics (and_threshold)
print(sc.get_matches(and_thresholds=True))
```

The same behaviours is defined in `SMoss`. You can create `SMoss` object to use MOSS system.

### Web-app interface
Please check our web-app interface [here](https://github.com/ngocjr7/scoss_webapp).


## Issues
This project is in development, if you find any issues, please create an issue [here](https://github.com/ngocjr7/scoss/issues).

## Contributors
[Ngoc Bui](https://github.com/ngocjr7), [Thai Do](https://github.com/Dec1mo), [Tran Vien](https://github.com/tranvien98).

## Acknowledgements
This project is sponsored and led by Prof. Do Phan Thuan, Hanoi University of Science and Technology.

A part of this code adapts this source code https://github.com/soachishti/moss.py as baseline for `SMoss`.
