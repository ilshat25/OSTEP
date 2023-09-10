# Chapter 17. FREE SPACE MANAGEMENT

## Exercise 1

### First run with the flags `-n 10 -H 0 -p BEST -s 0` to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?

```
ilssshat$ python malloc.py -n 10 -H 0 -p BEST -s 0
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList 
compute False

ptr[0] = Alloc(3) returned (addr: 1000, sz: 3) [searched 1 element]
List (addr: 1003, sz: 97)

Free(ptr[0])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 97)

ptr[1] = Alloc(5) returned (addr: 1003, sz: 5) [searched 2 elements]
List (addr: 1000, sz: 3), (addr: 1008, sz: 92)

Free(ptr[1])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 92)

ptr[2] = Alloc(8) returned (addr: 1008, sz: 8) [searched 3 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 10016, sz: 84)

Free(ptr[2])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[3] = Alloc(8) returned (addr: 1008, sz: 8) [searched 4 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 10016, sz: 84)

Free(ptr[3])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[4] = Alloc(2) returned (addr: 1000, sz: 2) [searched 4 elements]
List (addr: 1002, sz: 1), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[5] = Alloc(7) returned (addr: 1008, sz: 7) [searched 4 elements]
List (addr: 1002, sz: 1), (addr: 1003, sz: 5), (addr: 10015, sz: 1), (addr: 10016, sz: 84)
```

## Exercise 2

### How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes?

Worst fit leads to excessive frgmintation wiht search overhead

```
ilssshat$ python malloc.py -n 10 -H 0 -p WORST -s 0
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy WORST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList 
compute False

ptr[0] = Alloc(3) returned (addr: 1000, sz: 3) [searched 1 element]
List (addr: 1003, sz: 97)

Free(ptr[0])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 97)

ptr[1] = Alloc(5) returned (addr: 1003, sz: 5) [searched 2 elements]
List (addr: 1000, sz: 3), (addr: 1008, sz: 92)

Free(ptr[1])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 92)

ptr[2] = Alloc(8) returned (addr: 1008, sz: 8) [searched 3 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 10016, sz: 84)

Free(ptr[2])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[3] = Alloc(8) returned (addr: 10016, sz: 8) [searched 4 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10024, sz: 76)

Free(ptr[3])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 8), (addr: 10024, sz: 76)

ptr[4] = Alloc(2) returned (addr: 10024, sz: 2) [searched 5 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 8), (addr: 10026, sz: 74)

ptr[5] = Alloc(7) returned (addr: 10026, sz: 7) [searched 5 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 8), (addr: 10033, sz: 67)
```

## Exercise 3

### What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit?

Because the listis in order the fragmentation is the same as for BEST FIT approach, but the number of searches a bit better, because you don't need to scan all list, but take only first fitted element

```
ilssshat$ python malloc.py -n 10 -H 0 -p BEST -s 0
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList 
compute False

ptr[0] = Alloc(3) returned (addr: 1000, sz: 3) [searched 1 element]
List (addr: 1003, sz: 97)

Free(ptr[0])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 97)

ptr[1] = Alloc(5) returned (addr: 1003, sz: 5) [searched 2 elements]
List (addr: 1000, sz: 3), (addr: 1008, sz: 92)

Free(ptr[1])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 92)

ptr[2] = Alloc(8) returned (addr: 1008, sz: 8) [searched 3 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 10016, sz: 84)

Free(ptr[2])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[3] = Alloc(8) returned (addr: 1008, sz: 8) [searched 3 elements]
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 10016, sz: 84)

Free(ptr[3])
returned 0
List (addr: 1000, sz: 3), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[4] = Alloc(2) returned (addr: 1000, sz: 2) [searched 1 elements]
List (addr: 1002, sz: 1), (addr: 1003, sz: 5), (addr: 1008, sz: 8), (addr: 10016, sz: 84)

ptr[5] = Alloc(7) returned (addr: 1008, sz: 7) [searched 3 elements]
List (addr: 1002, sz: 1), (addr: 1003, sz: 5), (addr: 10015, sz: 1), (addr: 10016, sz: 84)
```

## Exercise 4

### For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings (-l ADDRSORT, -l SIZESORT+, -l SIZESORT-) to see how the policies and the list orderings interact.

Ordering affects only FIRST FIT strategy because BEAST and WORST FITS do full scan anyway. With SIZESORT- makes only one search, but memory becames more fragmented, with SIZESORT+ there's more searches, but fragmetation is the best.

## Exercise 5

### Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?

Without coalescing external fragmentation became big problem over time, some requests can't be satisfyied. With coalescing free list is much less and therefore more requests can be satifisfied + less time to search.

## Exercise 6

### What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?

If th epercent allocated fraction is more than 50, then the program will try to allocate more memory, than free it. It leads to lack of memory over time. percent near 0 is the same as percent near 50, to be freed memory has to be allocated.

## Exercise 7

### What kind of specific requests can you make to generate a highly-fragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organi- zation of the free list.

```
ilssshat$ python malloc.py -H 0 -S 5 -s 0 -A +1,+1,+1,+1,+1,-0,-1,-2,-3,-4 -c
seed 0
size 5
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList +1,+1,+1,+1,+1,-0,-1,-2,-3,-4
compute True

ptr[0] = Alloc(1) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1001 sz:4 ]

ptr[1] = Alloc(1) returned 1001 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1002 sz:3 ]

ptr[2] = Alloc(1) returned 1002 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1003 sz:2 ]

ptr[3] = Alloc(1) returned 1003 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1004 sz:1 ]

ptr[4] = Alloc(1) returned 1004 (searched 1 elements)
Free List [ Size 0 ]: 

Free(ptr[0])
returned 0
Free List [ Size 1 ]: [ addr:1000 sz:1 ]

Free(ptr[1])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:1 ][ addr:1001 sz:1 ]

Free(ptr[2])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:1 ][ addr:1001 sz:1 ][ addr:1002 sz:1 ]

Free(ptr[3])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:1 ][ addr:1001 sz:1 ][ addr:1002 sz:1 ][ addr:1003 sz:1 ]

Free(ptr[4])
returned 0
Free List [ Size 5 ]: [ addr:1000 sz:1 ][ addr:1001 sz:1 ][ addr:1002 sz:1 ][ addr:1003 sz:1 ][ addr:1004 sz:1 ]
```