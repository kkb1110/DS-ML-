import threading
import time

def print_numbers():
    for i in range(5):
        time.sleep(2)
        print("Number: ",i)

def print_chars():
    for i in "abcde":
        time.sleep(2)
        print("Character: ",i)

t=time.time()
t1=threading.Thread(target=print_numbers)
t2=threading.Thread(target=print_chars)

t1.start()
t2.start()
t1.join()
t2.join()
print(time.time()-t)


