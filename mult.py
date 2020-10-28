import numpy
import timeit
import matplotlib.pyplot as plt
import sys
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import tensorflow as tf


"""
https://sanjayasubedi.com.np/python/efficient-matrix-multiplication-in-python/
"""
global A, B

global n

def allocate(n):
    global A
    global B
    A = numpy.random.rand(n, n).astype(numpy.float32)
    B = numpy.random.rand(n, n).astype(numpy.float32)

def matmul1(a, b):
    n = a.shape[0]
    res = numpy.empty(a.shape)
    for i in range(n):
        for j in range(n):
            res[i,j] = numpy.dot(a[i,:], b[:,j])
    return res

def matmul2(a,b):
    res = numpy.empty(a.shape)
    n = a.shape[0]
    for i in range(n):
        res[i] = numpy.dot(a[i], b)

def matmul3(a,b):
    return tf.matmul(a,b)

for i in range(100):
    n = 100+i*10
    timer = timeit.Timer("allocate(n)", "import numpy; from __main__ import allocate, n")
    t = 1000.0*timer.repeat(1,1)[0]
    #timer = timeit.Timer("matmul2(A, B)", "import numpy; from __main__ import A,B,matmul2")
    #timer = timeit.Timer("matmul3(A, B)", "import tensorflow as tf; from __main__ import A,B,matmul3")
    timer = timeit.Timer("np.dot(A, B)", "import numpy as np; from __main__ import A,B")
    print("{:.3f} ".format(1000.0*numpy.sum(timer.repeat(10, 1))), end='')
