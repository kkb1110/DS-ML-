from concurrent.futures import ThreadPoolExecutor
from time import sleep
import time

def printNumber(number):
    sleep(1)
    return f"Number : {number}"

numbers=[1,2,3,4,5,6,7]
print(printNumber(5))

with ThreadPoolExecutor(max_workers=3) as executor:
    results=executor.map(printNumber,numbers)

for result in results:
    print(result)