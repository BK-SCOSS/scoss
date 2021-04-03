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

Comming soon...

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