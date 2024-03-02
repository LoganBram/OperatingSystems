import threading
import time

class SharedBuffer:
    def __init__(self, size, num_consumers):
        # Internal shared buffer
        self.buffer = []
        # Mutex to protect the buffer
        self.mutex = threading.Lock()
        # Semaphores to signal when the buffer is not empty
        self.notEmpty = threading.Semaphore(0)
         # Semaphores to signal when the buffer is not full
        self.notFull = threading.Semaphore(size)
        # Flag to signal that production is done
        self.doneProducing = False
        self.num_consumers = num_consumers

    '''
    Add a message to the buffer. If the buffer is full, the producer will wait.
    '''

    def add_message(self, message):
         # TODO: wait if buffer is full
        self.notFull.acquire()
        with self.mutex:
            self.buffer.append(message)
            # TODO: signal that buffer is not empty
        self.notEmpty.release()

    '''
    Read a message from the buffer. If the buffer is empty, the consumer will wait.
    '''

    def read_message(self):
        # TODO: wait if buffer is empty
        self.notEmpty.acquire()
        with self.mutex:
             # TODO: if production is done and buffer is empty, return None (check the buffer length)
            if self.doneProducing and len(self.buffer) == 0:
                # TODO: release the requried semaphore to avoid deadlock
                self.notEmpty.release()
                return None
            message = self.buffer.pop(0)
        # TODO: signal that buffer is not full
        self.notFull.release()
        return message
    
    '''
    Mark that production is done. This will be used by the producers to signal that they are done producing.
    '''

    def mark_done_producing(self):
        with self.mutex:
            # TODO: set the flag to signal that production is done
            self.doneProducing = True
             # TODO: release the semaphore for each consumer (you may need to release it multiple times)
        for i in range(self.num_consumers):  # djust based on the expected number of consumers waiting
            self.notEmpty.release()

'''
Producer and consumer functions. Each producer produces multiple messages and each consumer consumes messages until production is done.
'''

def producer(thread_id, buffer, write_time,num_producers):
    for message_number in range(5):  # Assuming each producer produces 5 messages
        message = f"Message {message_number} from Producer {thread_id}"
        buffer.add_message(message)
        print(f"Producer {thread_id} produced: {message}")
        time.sleep(write_time)  # Simulate write time
    if thread_id == num_producers - 1:  # if last producer, signal completion
        buffer.mark_done_producing()

'''
Consumer function. Each consumer consumes messages until production is done and the buffer is empty.
'''

def consumer(thread_id, buffer, read_time):
     # TODO: consume a message from the buffer
    while True:
        message = buffer.read_message()
         # TODO: break the loop if production is done and buffer is empty
        #is checking if production is done neccessary-----?
        if message is None:
            break
        print(f"Consumer {thread_id} consumed: {message}")
        time.sleep(read_time)  # Simulate read time

def main(buffer_size, num_producers, num_consumers, read_time, write_time):
    buffer = SharedBuffer(buffer_size, num_consumers)
    
    producers = [threading.Thread(target=producer, args=(i, buffer, write_time, num_producers)) for i in range(num_producers)]
    consumers = [threading.Thread(target=consumer, args=(i, buffer, read_time)) for i in range(num_consumers)]

    for p in producers:
        p.start()
    for c in consumers:
        c.start()

    for p in producers:
        p.join()
    for c in consumers:
        c.join()

    print("All producers and consumers have finished.")

if __name__ == '__main__':
    # params for testing
    buffer_size = 3 
    num_producers = 2  
    num_consumers = 5  
    read_time = 0.5  
    write_time = 2  
    
    main(buffer_size, num_producers, num_consumers, read_time, write_time)
