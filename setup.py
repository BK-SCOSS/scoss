from setuptools import setup, find_packages

with open("README.md", mode='r', encoding='utf-8') as fh:
    long_description = fh.read()

PROJECT_URLS = {
    'Bug Tracker': 'https://github.com/ngocjr7/geneticpython/issues',
    'Documentation': 'https://github.com/ngocjr7/geneticpython/blob/master/README.md',
    'Source Code': 'https://github.com/ngocjr7/geneticpython'
}

with open('requirements.txt') as f:
    install_requires = f.read().strip().split('\n')


setup(name='scoss',
      description='A Source Code Similarity System',
      author='Ngoc Bui',
      long_description=long_description,
      long_description_content_type="text/markdown",
      author_email='ngocjr7@gmail.com',
      project_urls=PROJECT_URLS,
      version='0.0.2', 
      packages=find_packages(),
      install_requires=install_requires,
      python_requires='>=3.6')
