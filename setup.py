from setuptools import setup, find_packages

with open("README.md", mode='r', encoding='utf-8') as fh:
    long_description = fh.read()

PROJECT_URLS = {
    'Bug Tracker': 'https://github.com/ngocjr7/scoss/issues',
    'Documentation': 'https://github.com/ngocjr7/scoss/blob/master/README.md',
    'Source Code': 'https://github.com/ngocjr7/scoss'
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
      version='0.0.5', 
      entry_points='''
        [console_scripts]
        scoss=scoss.cli:scoss_command
      ''',
      packages=find_packages(),
      install_requires=install_requires,
      python_requires='>=3.6')
