from redis import Redis
from rq import Queue
from my_module import count_words_at_url, for_n
import time
import multiprocessing
from rq import Connection, Worker

r = Redis()
queue = Queue(connection=r)
# job = queue.enqueue(count_words_at_url, 'http://nvie.com')
job = queue.enqueue(for_n, int(1e5))
print(job)
print(job.result)
