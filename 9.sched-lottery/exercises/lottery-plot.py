#! /usr/bin/env python3

import random

import matplotlib.pyplot as plt
from schedulers import LotteryScheduler, StrideScheduler
import numpy as np
import sys


uList = [0] * 1000
JOBS_COUNT = 2

args = sys.argv

if len(args) < 2:
    print('Enter scheduler type (lottery or stride)')
    exit(0)

sched_type = args[1]
if sched_type == 'lottery':
    sched = LotteryScheduler()
else:
    sched = StrideScheduler()

for i in range(30):
    random.seed(i)

    for job_length in range(1, 1001):
        finish_times = sched.run(JOBS_COUNT, job_length)
        u = round(finish_times[0] / finish_times[1], 2)
        uList[job_length - 1] += u

fig = plt.figure()
x = np.linspace(1, 1000, 1000)
plt.plot(x, [u / 30 for u in uList], color='orange')
plt.ylim(0, 1)
plt.margins(0)
plt.xlabel('Job Length')
plt.ylabel('Unfairness (Average)')
plt.title(f'{sched_type.capitalize()} Scheduling')
plt.savefig(f'{sched_type}.png', dpi=227)
