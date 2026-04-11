import multiprocessing
import time

def print_numbers():
    for i in range(5):
        time.sleep(1)
        print("Number: ",i)

def print_chars():
    for i in "abcde":
        time.sleep(1.5)
        print("Character: ",i)



if __name__=="__main__":
    ###create 2 processes
    p1=multiprocessing.Process(target=print_numbers)
    p2=multiprocessing.Process(target=print_chars)

    ### start the processes
    p1.start()
    p2.start()

    ## wait for the process to complete
    p1.join()
    p2.join()


