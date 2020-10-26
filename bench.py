import numpy
import timeit
import matplotlib.pyplot as plt
import sys
import os

"""
Based on code at:
https://raw.githubusercontent.com/charanpald/tyre-hug/master/tyrehug/exp/linalg.py
https://github.com/charanpald/tyre-hug/blob/18da02faf2cba579566390cac12c8d796a423184/tyrehug/exp/linalg.py
Visited on: 26.10.2020
Originally found at:
https://simplyml.com/linear-algebra-shootout-numpy-vs-theano-vs-tensorflow-2/
Author: Charanpal Dhanjal
"""

def get_dir(dir_name):
    if os.path.exists(dir_name):
        return dir_name
    else:
        return ""
DATA_DIR = "/home/gania/Documents/tensorMultBenchmarks/data/"


numpy.random.seed(21)
num_repeats = 20
min_size = 500
max_size = 5001
step = 500

data_dir = get_dir(DATA_DIR)

def benchmark_numpy():
    times = []
    print("Benchmarking Numpy " + str(numpy.__version__))

    for i in range(min_size, max_size, step):
        print(i)
        global A, B
        A = numpy.random.rand(i, i).astype(numpy.float32)
        B = numpy.random.rand(i, i).astype(numpy.float32)

        current_times = [i]

        timer = timeit.Timer("numpy.dot(A, B)", "import numpy; from __main__ import A, B")
        current_times.append(numpy.min(timer.repeat(num_repeats, 1)))

        timer = timeit.Timer("numpy.exp(A)", "import numpy; from __main__ import A")
        current_times.append(numpy.min(timer.repeat(num_repeats, 1)))

        timer = timeit.Timer("numpy.sum(A)", "import numpy; from __main__ import A")
        current_times.append(numpy.min(timer.repeat(num_repeats, 1)))

        timer = timeit.Timer("A + B", "import numpy; from __main__ import A, B")
        current_times.append(numpy.min(timer.repeat(num_repeats, 1)))

        timer = timeit.Timer("numpy.mean(A)", "import numpy; from __main__ import A")
        current_times.append(numpy.min(timer.repeat(num_repeats, 1)))

        timer = timeit.Timer("numpy.min(A)", "import numpy; from __main__ import A")
        current_times.append(numpy.min(timer.repeat(num_repeats, 1)))

        times.append(current_times)

    times = numpy.array(times)
    filename = data_dir + "numpy_times"
    numpy.save(filename, times)
    print("Saved results as {}.npy".format(filename))

    print("\nResults check")
    print("-"*14)

    # Print results to compare them
    print("||dot(A, B)||={}".format(numpy.linalg.norm(numpy.dot(A, B))))
    print("||exp(A)||={}".format(numpy.linalg.norm(numpy.exp(A))))
    print("sum(A)={}".format(numpy.sum(A)))
    print("||A+B||={}".format(numpy.linalg.norm(A + B)))
    print("mean(A)={}".format(numpy.mean(A)))
    print("min(A)={}".format(numpy.min(A)))

def plot_times():
    numpy_times = numpy.load(data_dir + "numpy_times.npy")

    titles = ["dot", "exp", "sum", "add", "mean", "min"]

    for i, title in enumerate(titles):
        plt.figure(i)
        plt.title(title)
        plt.plot(numpy_times[:, 0], numpy_times[:, i + 1], label="numpy")
        plt.legend(loc="upper left")
        plt.xlabel("size")
        plt.ylabel("time (s)")
        plt.plot()

        # print(title)
        print(numpy.c_[numpy_times[:, i + 1]])
        plt.savefig(title + ".png")

    plt.show()

if len(sys.argv) == 2 and sys.argv[1] == '1':
    benchmark_numpy()
else:
    plot_times()
