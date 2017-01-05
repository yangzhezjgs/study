import time
from functools import wraps

def timing(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
         start = time.clock()
         result = f(*args, **kwargs)
         end = time.clock()
         print("%s: %fs" % (f.__name__, end - start))
         return result
    return wrapper




