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

## Exercise 3

### Now do the same, but also with the RR scheduler and a time-slice of 1

RR:

`$ python schedulter.py -p RR -q 1 -l 100,200,300 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 298, Wait: 198
Job 1 -- Response: 1,   Turnaround: 499, Wait: 299
Job 2 -- Response: 2,   Turnaround: 600, Wait: 300

Avg Response:   (0 + 1 + 2) / 3 = 1
Avg Turnaround: (298 + 499 + 600) / 3 = 465.67
Avg Wait:       (198 + 299 + 300) / 3 = 265.67
```

We can the difference, Response became much better, but in cost of performance metrics...

## Exercise 4

### For what types of workloads does SJF deliver the same turnaround times as FIFO?

For the workloads where jobs goes in ascending order, in this case (if jobs comes in the same time, ofc) SJF has the same turnaround as FIFO

## Exercise 5

### For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

The length of first n - 1 jobs should be equal to quanum

```
RT = Ts - Ta, where Ts - the time of first job scheduling, Ta - the time of job arrival.
Let's say that the arrival time would be the same for each job.

Then
RR:  RT(n) = n * t, where n - the number of the job, t - length of the quantum
SJF: RT(n) = T(0) + T(1) + ... + T(n - 1), for n > 0 and 0 if n = 0, T(i) - cpu time needed for the job

n * t = T(0) + T(1) + ... + T(n - 1)
t = (T(0) + T(1) + ... + T(n - 1)) / n => T(i) = t => for the first n - 1 jobs the time of needed cpu has to be the same as the length of the quantum, in this case RR and SJF has the same response time
```

RR:

`$ python schedulter.py -p RR -q 100 -l 100,100,100 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 100, Wait: 0
Job 1 -- Response: 100, Turnaround: 200, Wait: 100
Job 2 -- Response: 200, Turnaround: 300, Wait: 200

Avg Response:   (0 + 100 + 200) / 3 = 100
Avg Turnaround: (100 + 200 + 300) / 3 = 200
Avg Wait:       (0 + 100 + 200) / 3 = 100
```

SJF:

`$ python schedulter.py -p SJF -l 100,100,200 -s 100`

```
Job 0 -- Response: 0,   Turnaround: 100, Wait: 0
Job 1 -- Response: 100, Turnaround: 200, Wait: 100
Job 2 -- Response: 200, Turnaround: 400, Wait: 200

Avg Response:   (0 + 100 + 200) / 3 = 100
Avg Turnaround: (100 + 200 + 400) / 3 = 233.33
Avg Wait:       (0 + 100 + 200) / 3 = 100
```

## Exercise 6

### What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

With the same increase the length of the jobs, the response time would increase linear

```
T'(i) = T(i) + m, m - the increase const
RT'(n) = T'(0) + T'(1) + ... + T'(n - 1) = RT(n) + n*m
in average: RTavg' = (RT'(0) + RT'(1) + ... + RT'(n)) / (n + 1) = RTavg + (0 + m + ... + n*m) / (n + 1) = RTavg + m * n / 2, N = n + 1 - the count of jobs 
```

`$ python schedulter.py -p SJF -l 100,200,300,500,600 -s 100`
`Avg Response: 420`

`$ python schedulter.py -p SJF -l 200,300,400,600,700 -s 100`
`Avg Response: 620`

`$ python schedulter.py -p SJF -l 300,400,500,700,800 -s 100`
`Avg Response: 820`

## Exercise 7

### What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case re- sponse time, given N jobs?

The trend is linear with increasing quantum length for RR if quantum length < avg(job length)

The worst case is t >= max(T(i)), in this case RT(n) = sum(T(i)), 0 <= i < n
