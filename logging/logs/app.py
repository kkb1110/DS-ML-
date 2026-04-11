from logger import logging

def add(a,b):
    logging.debug("Addition going on")
    return a+b

logging.debug("Addition function called")
add(10,20)