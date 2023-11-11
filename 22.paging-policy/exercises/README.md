# Chapter 22: Paging Policies

## Exercise 1

Generate random addresses with the following arguments: -s 0 -n 10, -s 1 -n 10, and -s 2 -n 10. Change the policy from FIFO, to LRU, to OPT. Compute whether each access in said address traces are hits or misses.
- - -

```
ilssshat$ python paging-policy.py -s 0 -n 10 --policy FIFO
ARG addresses -1
ARG addressfile 
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Assuming a replacement policy of FIFO, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 8   Miss    8
Access: 7   Miss    8 7
Access: 4   Miss    8 7 4  
Access: 2   Miss    7 4 2  
Access: 5   Miss    4 2 5
Access: 4   Hit     4 2 5
Access: 7   Miss    2 5 7  
Access: 3   Miss    5 7 3
Access: 4   Miss    7 3 4
Access: 5   Miss    3 4 5

1 / 10
```

```
ilssshat$ python paging-policy.py -s 0 -n 10 --policy LRU
ARG addresses -1
ARG addressfile 
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Assuming a replacement policy of LRU, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 8   Miss    8
Access: 7   Miss    8 7
Access: 4   Miss    8 7 4
Access: 2   Miss    7 4 2
Access: 5   Miss    4 2 5
Access: 4   Hit     2 5 4
Access: 7   Miss    5 4 7
Access: 3   Miss    4 7 3
Access: 4   Hit     7 3 4
Access: 5   Miss    3 4 5

2 / 10
```

```
ilssshat$ python paging-policy.py -s 0 -n 10 --policy OPT
ARG addresses -1
ARG addressfile 
ARG numaddrs 10
ARG policy OPT
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Assuming a replacement policy of OPT, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 8   Miss    8 
Access: 7   Miss    8 7
Access: 4   Miss    8 7 4     
Access: 2   Miss    7 4 2     
Access: 5   Miss    7 4 5     
Access: 4   Hit     7 4 5     
Access: 7   Hit     7 4 5     
Access: 3   Miss    4 5 3     
Access: 4   Hit     4 5 3     
Access: 5   Hit     4 5 3

4 / 10
```

## Exercise 2

For a cache of size 5, generate worst-case address reference streams for each of the following policies: FIFO, LRU, and MRU (worst-case reference streams cause the most misses possible). For the worst case reference streams, how much bigger of a cache is needed to improve performance dramatically and approach OPT?
- - -

```
FIFO
1   Miss    [1]
2   Miss    [1 2]
3   Miss    [1 2 3]
4   Miss    [1 2 3 4]
5   Miss    [1 2 3 4 5]
6   Miss    [2 3 4 5 6]
1   Miss    [3 4 5 6 1]
2   Miss    [4 5 6 1 2]
3   Miss    [5 6 1 2 3]
4   Miss    [6 1 2 3 4]
5   Miss    [1 2 3 4 5]
6   Miss    [2 3 4 5 6]
...
```

LRU the same situation as for FIFO, for sequential accesses in a loop the cache size has to be the same as the loop size

```
MRU
1   Miss    [1]
2   Miss    [1 2]
3   Miss    [1 2 3]
4   Miss    [1 2 3 4]
5   Miss    [1 2 3 4 5]
6   Miss    [1 2 3 4 6]
5   Miss    [1 2 3 4 5]
6   Miss    [1 2 3 4 6]
5   Miss    [1 2 3 4 5]
6   Miss    [1 2 3 4 6]
5   Miss    [1 2 3 4 5]
...
```


## Exercise 3

Generate a random trace (use python or perl). How would you expect the different policies to perform on such a trace?
- - -

1 4 2 3 5 1 6 2 8 1 7 6 2 4 4 3

according to my expectations LRU should perform as well as FIFO and RANDOM

```
ilssshat$ python paging-policy.py --policy OPT --addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3 -c
ARG addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3
ARG addressfile 
ARG numaddrs 10
ARG policy OPT
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS Left  ->          [1] <- Right Replaced:- [Hits:0 Misses:1]
Access: 4  MISS Left  ->       [1, 4] <- Right Replaced:- [Hits:0 Misses:2]
Access: 2  MISS Left  ->    [1, 4, 2] <- Right Replaced:- [Hits:0 Misses:3]
Access: 3  MISS Left  ->    [1, 2, 3] <- Right Replaced:4 [Hits:0 Misses:4]
Access: 5  MISS Left  ->    [1, 2, 5] <- Right Replaced:3 [Hits:0 Misses:5]
Access: 1  HIT  Left  ->    [1, 2, 5] <- Right Replaced:- [Hits:1 Misses:5]
Access: 6  MISS Left  ->    [1, 2, 6] <- Right Replaced:5 [Hits:1 Misses:6]
Access: 2  HIT  Left  ->    [1, 2, 6] <- Right Replaced:- [Hits:2 Misses:6]
Access: 8  MISS Left  ->    [1, 6, 8] <- Right Replaced:2 [Hits:2 Misses:7]
Access: 1  HIT  Left  ->    [1, 6, 8] <- Right Replaced:- [Hits:3 Misses:7]
Access: 7  MISS Left  ->    [1, 6, 7] <- Right Replaced:8 [Hits:3 Misses:8]
Access: 6  HIT  Left  ->    [1, 6, 7] <- Right Replaced:- [Hits:4 Misses:8]
Access: 2  MISS Left  ->    [1, 6, 2] <- Right Replaced:7 [Hits:4 Misses:9]
Access: 4  MISS Left  ->    [1, 6, 4] <- Right Replaced:2 [Hits:4 Misses:10]
Access: 4  HIT  Left  ->    [1, 6, 4] <- Right Replaced:- [Hits:5 Misses:10]
Access: 3  MISS Left  ->    [1, 6, 3] <- Right Replaced:4 [Hits:5 Misses:11]

FINALSTATS hits 5   misses 11   hitrate 31.25

ilssshat$ python paging-policy.py --policy LRU --addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3 -c
ARG addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3
ARG addressfile 
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS LRU ->          [1] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 4  MISS LRU ->       [1, 4] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 2  MISS LRU ->    [1, 4, 2] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 3  MISS LRU ->    [4, 2, 3] <- MRU Replaced:1 [Hits:0 Misses:4]
Access: 5  MISS LRU ->    [2, 3, 5] <- MRU Replaced:4 [Hits:0 Misses:5]
Access: 1  MISS LRU ->    [3, 5, 1] <- MRU Replaced:2 [Hits:0 Misses:6]
Access: 6  MISS LRU ->    [5, 1, 6] <- MRU Replaced:3 [Hits:0 Misses:7]
Access: 2  MISS LRU ->    [1, 6, 2] <- MRU Replaced:5 [Hits:0 Misses:8]
Access: 8  MISS LRU ->    [6, 2, 8] <- MRU Replaced:1 [Hits:0 Misses:9]
Access: 1  MISS LRU ->    [2, 8, 1] <- MRU Replaced:6 [Hits:0 Misses:10]
Access: 7  MISS LRU ->    [8, 1, 7] <- MRU Replaced:2 [Hits:0 Misses:11]
Access: 6  MISS LRU ->    [1, 7, 6] <- MRU Replaced:8 [Hits:0 Misses:12]
Access: 2  MISS LRU ->    [7, 6, 2] <- MRU Replaced:1 [Hits:0 Misses:13]
Access: 4  MISS LRU ->    [6, 2, 4] <- MRU Replaced:7 [Hits:0 Misses:14]
Access: 4  HIT  LRU ->    [6, 2, 4] <- MRU Replaced:- [Hits:1 Misses:14]
Access: 3  MISS LRU ->    [2, 4, 3] <- MRU Replaced:6 [Hits:1 Misses:15]

FINALSTATS hits 1   misses 15   hitrate 6.25

ilssshat$ python paging-policy.py --policy RAND --addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3 -c
ARG addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3
ARG addressfile 
ARG numaddrs 10
ARG policy RAND
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS Left  ->          [1] <- Right Replaced:- [Hits:0 Misses:1]
Access: 4  MISS Left  ->       [1, 4] <- Right Replaced:- [Hits:0 Misses:2]
Access: 2  MISS Left  ->    [1, 4, 2] <- Right Replaced:- [Hits:0 Misses:3]
Access: 3  MISS Left  ->    [1, 4, 3] <- Right Replaced:2 [Hits:0 Misses:4]
Access: 5  MISS Left  ->    [1, 4, 5] <- Right Replaced:3 [Hits:0 Misses:5]
Access: 1  HIT  Left  ->    [1, 4, 5] <- Right Replaced:- [Hits:1 Misses:5]
Access: 6  MISS Left  ->    [1, 5, 6] <- Right Replaced:4 [Hits:1 Misses:6]
Access: 2  MISS Left  ->    [5, 6, 2] <- Right Replaced:1 [Hits:1 Misses:7]
Access: 8  MISS Left  ->    [5, 2, 8] <- Right Replaced:6 [Hits:1 Misses:8]
Access: 1  MISS Left  ->    [5, 8, 1] <- Right Replaced:2 [Hits:1 Misses:9]
Access: 7  MISS Left  ->    [5, 8, 7] <- Right Replaced:1 [Hits:1 Misses:10]
Access: 6  MISS Left  ->    [8, 7, 6] <- Right Replaced:5 [Hits:1 Misses:11]
Access: 2  MISS Left  ->    [8, 6, 2] <- Right Replaced:7 [Hits:1 Misses:12]
Access: 4  MISS Left  ->    [8, 2, 4] <- Right Replaced:6 [Hits:1 Misses:13]
Access: 4  HIT  Left  ->    [8, 2, 4] <- Right Replaced:- [Hits:2 Misses:13]
Access: 3  MISS Left  ->    [8, 2, 3] <- Right Replaced:4 [Hits:2 Misses:14]

FINALSTATS hits 2   misses 14   hitrate 12.50

ilssshat$ python paging-policy.py --policy FIFO --addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3 -c
ARG addresses 1,4,2,3,5,1,6,2,8,1,7,6,2,4,4,3
ARG addressfile 
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS FirstIn ->          [1] <- Lastin  Replaced:- [Hits:0 Misses:1]
Access: 4  MISS FirstIn ->       [1, 4] <- Lastin  Replaced:- [Hits:0 Misses:2]
Access: 2  MISS FirstIn ->    [1, 4, 2] <- Lastin  Replaced:- [Hits:0 Misses:3]
Access: 3  MISS FirstIn ->    [4, 2, 3] <- Lastin  Replaced:1 [Hits:0 Misses:4]
Access: 5  MISS FirstIn ->    [2, 3, 5] <- Lastin  Replaced:4 [Hits:0 Misses:5]
Access: 1  MISS FirstIn ->    [3, 5, 1] <- Lastin  Replaced:2 [Hits:0 Misses:6]
Access: 6  MISS FirstIn ->    [5, 1, 6] <- Lastin  Replaced:3 [Hits:0 Misses:7]
Access: 2  MISS FirstIn ->    [1, 6, 2] <- Lastin  Replaced:5 [Hits:0 Misses:8]
Access: 8  MISS FirstIn ->    [6, 2, 8] <- Lastin  Replaced:1 [Hits:0 Misses:9]
Access: 1  MISS FirstIn ->    [2, 8, 1] <- Lastin  Replaced:6 [Hits:0 Misses:10]
Access: 7  MISS FirstIn ->    [8, 1, 7] <- Lastin  Replaced:2 [Hits:0 Misses:11]
Access: 6  MISS FirstIn ->    [1, 7, 6] <- Lastin  Replaced:8 [Hits:0 Misses:12]
Access: 2  MISS FirstIn ->    [7, 6, 2] <- Lastin  Replaced:1 [Hits:0 Misses:13]
Access: 4  MISS FirstIn ->    [6, 2, 4] <- Lastin  Replaced:7 [Hits:0 Misses:14]
Access: 4  HIT  FirstIn ->    [6, 2, 4] <- Lastin  Replaced:- [Hits:1 Misses:14]
Access: 3  MISS FirstIn ->    [2, 4, 3] <- Lastin  Replaced:6 [Hits:1 Misses:15]

FINALSTATS hits 1   misses 15   hitrate 6.25
```