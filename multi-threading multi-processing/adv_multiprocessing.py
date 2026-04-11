from concurrent.futures import ProcessPoolExecutor
from time import sleep
import multiprocessing.connection

def printNumber(number):
    sleep(1)
    return f"Square : {number**2}"

numbers=[1,2,3,4,5,6,7]
print(printNumber(5))

if __name__ == "__main__" :
    with ProcessPoolExecutor(max_workers=3) as executor:
        results=executor.map(printNumber,numbers)

    for result in results:
        print(result)