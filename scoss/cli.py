import scoss

import click

@click.command()
@click.option(
    '--submission-dir', '-sd', required=True,
    help='Submission directory.'
)
@click.option(
    '--output-dir', '-o', 
    help='Output directory.'
)
@click.option(
    '--threshold-combination', '-tc', 
    type=click.Choice(['AND','OR'], case_sensitive=False),
    help='AND: All metrics are greater than threshold.\nOR: At least 1 metric is greater than threshold.'
)
@click.option(
    '--moss', '-mo', type=click.FloatRange(0,1),
    help='Use moss metric and set up moss threshold.'
)
@click.option(
    '--count-operator', '-co', type=click.FloatRange(0,1),
    help='Use count operator metric and set up count operator threshold.'
)
@click.option(
    '--set-operator', '-so', type=click.FloatRange(0,1),
    help='Use set operator metric and set up set operator threshold.'
)
@click.option(
    '--hash-operator', '-ho', type=click.FloatRange(0,1),
    help='Use hash operator metric and set up hash operator threshold.'
)
def scoss_command(submission_dir, output_dir, threshold_combination,\
    moss, count_operator, set_operator, hash_operator):
    if not output_dir:
        output_dir = './'

    scoss.get_all_plagiarism(submission_dir, output_dir, threshold_combination, 
        moss, count_operator, set_operator, hash_operator)

if __name__ == '__main__':
    # python scoss_cli.py -sd tests/data/299721 -tc OR -co 0.1 -ho 0.1 -mo 0.1 -o tests/data
    # python scoss_cli.py -sd tests/data/299721 -tc OR -co 0.9 -ho 0.7 -o tests/data
    scoss_command()