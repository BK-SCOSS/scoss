from app.controllers.task_queue import TaskQueue

import time

def check_problem(problem_id):
    print(problem_id)
    time.sleep(1)
    

def test_task_queue():
    tq = TaskQueue(do_work=check_problem, num_workers=4, queue_size=100000)
    for i in range(100):
        tq.enqueue_nowait(i) # Return True if add sucessfully, otherwise return False
        print("Enqueue", i)

    print("Waiting")
    tq.join()

if __name__ == '__main__':
    test_task_queue()

