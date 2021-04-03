import requests

def count_words_at_url(url):
    """Just an example function that's called async."""
    resp = requests.get(url)
    print(len(resp.text.split()))
    return len(resp.text.split())


def for_n(n):
    res = 0
    for i in range(n):
        res += i
    print(res)
    return res
