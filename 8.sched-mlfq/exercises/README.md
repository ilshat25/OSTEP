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
