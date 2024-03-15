import threading
import time
import random

# Define the number of philosophers / forks
PHILOSOPHERS_COUNT = 5
thinking_time = 1
eating_time = 5
# Initialize locks for each fork
# TODO: create a list of forks using a semaphore for each fork
forks = [threading.Semaphore(1), threading.Semaphore(1), threading.Semaphore(1), threading.Semaphore(1), threading.Semaphore(1)]

mutex = threading.Semaphore(1)


def philosopher(id):

    while True:
        # Think
        print(f"Philosopher {id} is thinking.")
        # Simulate thinking time
        time.sleep(random.randint(1, thinking_time))

        # TODO: You should protect the critical section before executing the code below
        
        with mutex: # Added with instead of acquiring and releasing after the next TODO
            left_fork, right_fork = prevent(id)
            
            # Pick up forks
            print(f"Philosopher {id} is hungry.")
            # TODO: pick up the left fork
            forks[left_fork].acquire()

            print(f"Philosopher {id} picked up left fork.")
            # TODO: pick up the right fork
            forks[right_fork].acquire()

            print(f"Philosopher {id} picked up right fork.")

        # TODO: You should release the lock for the critical section after executing the code above
        
        # Eat
        # Simulate eating time
        print(f"Philosopher {id} is eating.")
        time.sleep(random.randint(1, eating_time))

        # Put down forks
        # TODO: put down the left fork
        forks[left_fork].release()

        # TODO: put down the right fork
        forks[right_fork].release()
        print(f"Philosopher {id} finished eating and put down forks.")

def prevent(id):
    '''
    Philosophers must pick up smallest fork first.
    This fixes deadlock because philosophers 1 and 5 can't
    both carry a chopstick because they both try to take the first one
    and only one of them can grab it at a time

    Returns: fork1 - smaller number
             fork2 - bigger number
    '''
    fork1 = id
    fork2 = (id + 1) % PHILOSOPHERS_COUNT

    # Always set fork1 to the smaller fork
    if fork1 < fork2:
        return fork1, fork2
    
    return fork2, fork1
        
if __name__ == "__main__":
    # Create and start philosopher threads
    philosophers = [threading.Thread(
        target=philosopher, args=(i,)) for i in range(PHILOSOPHERS_COUNT)]
    for p in philosophers:
        p.start()

    # Wait for all threads to finish
    for p in philosophers:
        p.join()
