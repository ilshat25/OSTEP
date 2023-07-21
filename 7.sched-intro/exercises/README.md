# Chapter 7 SCHEDULER INTRODUCTION

## Exercice 1

### Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

FIFO:

`$ python schedulter.py -p FIFO -l 200,200,200 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 200, Wait: 0
Job 1 -- Response: 200, Turnaround: 400, Wait: 200
Job 2 -- Response: 400, Turnaround: 600, Wait: 400

Avg Response:   (0 + 200 + 400) / 3 = 200
Avg Turnaround: (200 + 400 + 600) / 3 = 400
Avg Wait:       (0 + 200 + 400) / 3 = 200
```

SJF:

`$ python schedulter.py -p SJF -l 200,200,200 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 200, Wait: 0
Job 1 -- Response: 200, Turnaround: 400, Wait: 200
Job 2 -- Response: 400, Turnaround: 600, Wait: 400

Avg Response:   (0 + 200 + 400) / 3 = 200
Avg Turnaround: (200 + 400 + 600) / 3 = 400
Avg Wait:       (0 + 200 + 400) / 3 = 200
```

Metrics the same for both polices because jobs are starting the same time and the length of the jobs are the same.

## Exercise 2

### Now do the same but with jobs of different lengths: 100, 200, and 300.

FIFO

`$ python schedulter.py -p FIFO -l 100,200,300 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 100, Wait: 0
Job 1 -- Response: 100, Turnaround: 300, Wait: 100
Job 2 -- Response: 300, Turnaround: 600, Wait: 300

Avg Response:   (0 + 100 + 300) / 3 = 133.33
Avg Turnaround: (100 + 300 + 600) / 3 = 333.33
Avg Wait:       (0 + 100 + 300) / 3 = 133.33
```

SJF:

`$ python schedulter.py -p SJF -l 100,200,300 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 100, Wait: 0
Job 1 -- Response: 100, Turnaround: 300, Wait: 100
Job 2 -- Response: 300, Turnaround: 600, Wait: 300

Avg Response:   (0 + 100 + 300) / 3 = 133.33
Avg Turnaround: (100 + 300 + 600) / 3 = 333.33
Avg Wait:       (0 + 100 + 300) / 3 = 133.33
```

Results are the same because jobs are going to scheduler in ascending order, with different order results would be vary
