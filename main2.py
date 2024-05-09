# This is a sample Python script.
from typing import Optional

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


# numpy to torch with .from_numpy(x)
import numpy as np



import torch

# !/bin/python3

import math
import os
import random
import re
import sys


#
# Complete the 'largestRectangle' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts INTEGER_ARRAY h as parameter.
import tracemalloc


# code or function for which memory
# has to be monitored

# importing libraries
import os
import psutil

import pandas as pd
import os
import matplotlib.pyplot as plt

import pandas as pd
import os



import numpy as np
import matplotlib.pyplot as plt


import numpy as np
import matplotlib.pyplot as plt

# Parameters

import pandas as pd
import matplotlib.pyplot as plt

import numpy as np
import matplotlib.pyplot as plt

# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

def solution(A) :
    A_len = len(A)    # The length of array A
    # Get the sum of maximum subarray, which ends this position
    # Method: http://en.wikipedia.org/wiki/Maximum_subarray_problem
    max_ending_here = [0] * A_len
    max_ending_here_temp = 0
    for index in range(1, A_len - 2) : # X can land in index, for example A_len-3
        max_ending_here_temp = max(0, A[index] + max_ending_here_temp)
        max_ending_here[index] = max_ending_here_temp
        # Get the sum of maximum subarray, which begins this position
        # The same method.But we travel from the tail to the head
        max_beginning_here = [0] * A_len
        max_beginning_here_temp = 0
    for index in range(A_len - 2, 1, -1) : # Z can lnad in index, for example 2
        max_beginning_here_temp = max(0, A[index] + max_beginning_here_temp)
        max_beginning_here[index] = max_beginning_here_temp
        # Connect two subarray for a double_slice.If the first subarray
        # ends at position i, the second subarray starts at position i + 2.
        # Then we compare each double slice to get the one with the
        # greatest sum.
    max_double_slice = 0
    for index in range(0, A_len - 2) :
        max_double_slice = max(max_double_slice,
            max_ending_here[index] + max_beginning_here[index + 2])
    return max_double_slice

# Test the function
print(solution([3, 2, 6, -1, 4, 5, -1, 2]))  # Output should be 17



