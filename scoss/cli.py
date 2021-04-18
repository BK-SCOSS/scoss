import scoss

import click

@click.command()
@click.option(
    '--input-dir', '-i', required=True,
    help='Input directory.'
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
def scoss_command(input_dir, output_dir, threshold_combination,\
    moss, count_operator, set_operator, hash_operator):
    if not output_dir:
        output_dir = './'

    scoss.get_all_plagiarism(input_dir, output_dir, threshold_combination, 
        moss, count_operator, set_operator, hash_operator)

if __name__ == '__main__':
    scoss_command()