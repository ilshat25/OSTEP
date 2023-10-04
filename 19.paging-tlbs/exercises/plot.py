#! /usr/bin/env python3

import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

x = []
y = []
for line in open('tlb.data'):
    data = line.split()
    x.append(int(data[0]))
    y.append(float(data[1]))

fig, ax = plt.subplots()

plt.plot(x, y, '-bo')
plt.xscale('log', base=2)
plt.autoscale(False, axis='x')
ax.xaxis.set_major_formatter(ScalarFormatter())
plt.xlabel('Number Of Pages')
plt.ylabel('Time Per Access (ns)')
plt.title('TBL Size')
plt.savefig(f'tlb.png', dpi=227)
