# Chapter 8 MULTI LEVEL FEEDBACK QUEUE

## Exercise 1

### Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

`$ python mlfq.py -s 100 -m 10 -j 2 -n 2 -M 0 -q 4`

```
Here is the list of inputs:
  OPTIONS jobs 2
  OPTIONS queues 2
  OPTIONS allotments for queue  1 is   1
  OPTIONS quantum length for queue  1 is   4
  OPTIONS allotments for queue  0 is   1
  OPTIONS quantum length for queue  0 is   4
  OPTIONS boost 0
  OPTIONS ioTime 5
  OPTIONS stayAfterIO False
  OPTIONS iobump False

Job List:
  Job  0 -- startTime: 0  runTime: 8    ioFreq: 0
  Job  1 -- startTime: 0  runTime: 15   ioFreq: 0

----+---+------------------------
 Q1 |j0 |0000
    |j1 |    1111
----+---+------------------------
 Q2 |j0 |        0000
    |j1 |            11111111111
----+---+------------------------
        0    5    10   15   20 

Final statistics:
  Job 0 -- Response: 0, Turnaround: 12
  Job 1 -- Response: 4, Turnaround: 23

  Avg Response:     (0 + 4) / 2 = 2
  Avg Turnaround:   (12 + 23) / 2 = 17.5
```

## Exercise 2

### How would you run the scheduler to reproduce each of the examples in the chapter?

```
Figure 8.2: Long-running job over time
$ python mlfq.py --jlist 0,200,0 -q 10 -n 3 -c

Figure 8.3: Along came an interactive job
$ python mlfq.py --jlist 0,180,0:100,20,0 -q 10 -n 3 -c

Figure 8.4: A mixed i/o-intensive and CPU-intensive workload
$ python mlfq.py --jlist 0,175,0:50,25,1 -q 10 -n 3 -S -c

Figure 8.5: Without priority boost
$ python mlfq.py --jlist 0,130,0:100,50,1:100,50,1 -q 10 -n 3 -i 1 -S -c

Figure 8.5: With priority boost
$ python mlfq.py --jlist 0,130,0:100,50,1:100,50,1 -q 10 -n 3 -i 1 -S -B 50 -c

Figure 8.6: Without gaming tolerance
$ python mlfq.py --jlist 0,170,0:70,90,9 -q 10 -n 3 -i 1 -S -I -c

Figure 8.6: With gaming tolerance
$ python mlfq.py --jlist 0,170,0:70,90,9 -q 10 -n 3 -i 1 -I -c

Figure 8.7: Lower priority, longer quanta
$ python mlfq.py --jlist 0,140,0:0,140,0 -Q 10,20,40 -a 2 -n 3 -c
```

## Exercise 3

### How would you configure the scheduler parameters to behave just like a round-robin scheduler?

Make only one queue

`$ python mlfq.py -j 3 -n 1 -M 0 -c`

## Exercise 4

### Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

`$ python mlfq.py --jlist 0,20,0:10,10,4 -n 3 -i 1 -q 5 -S -c`

```
Here is the list of inputs:
  OPTIONS jobs 2
  OPTIONS queues 3
  OPTIONS allotments for queue  2 is   1
  OPTIONS quantum length for queue  2 is   5
  OPTIONS allotments for queue  1 is   1
  OPTIONS quantum length for queue  1 is   5
  OPTIONS allotments for queue  0 is   1
  OPTIONS quantum length for queue  0 is   5
  OPTIONS boost 0
  OPTIONS ioTime 1
  OPTIONS stayAfterIO True
  OPTIONS iobump False

Job List:
  Job  0 -- startTime: 0  runTime: 20   ioFreq: 0
  Job  1 -- startTime: 0  runTime: 10   ioFreq: 4

----+---+-------------------------------
 Q1 |j0 |00000
    |j1 |          1111 1111 11
----+---+-------------------------------
 Q2 |j0 |     00000
    |j1 |              
----+---+-------------------------------
 Q3 |j0 |              0    0  00000000  
    |j1 |            
----+---+-------------------------------
        0    5    10   15   20        30 

Final statistics:
  Job 0 -- Response: 0, Turnaround: 30
  Job 1 -- Response: 0, Turnaround: 12

  Avg Response:     (0 + 0) / 2 = 0
  Avg Turnaround:   (12 + 30) / 2 = 21
```

## Exercise 5

### Given a system with a quantum length of 10ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long- running (and potentially-starving) job gets at least 5% of the CPU?

Lets assume that there's always short interactive tasks wanting to cpu-time, in this case to have at least 5% of cpu-time wiht 10ms quntum length in the highest queue boos time has to be as least 10ms / 0.05 = *200ms*.

## Exercise 6

### One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.

IO boost can be a good tactic in case if there're some short jobs that perform i/o intensively and some cpu-demand jobs

`$ python mlfq.py --jlist 0,50,0:0,25,5 -n 3 -q 5 -c`

```
Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  75
  Job  1: startTime   0 - response   5 - turnaround  65

  Avg  1: startTime n/a - response 2.50 - turnaround 70.00
```

`$ python mlfq.py --jlist 0,50,0:0,25,5 -n 3 -q 5 -I -c`

```
Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  75
  Job  1: startTime   0 - response   5 - turnaround  50

  Avg  1: startTime n/a - response 2.50 - turnaround 62.50
```

but if there're too many interactive jobs they will lead the system to starving of cpu-demand jobs even in the highest queue
