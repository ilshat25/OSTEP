# Chapter 19. PAGING: TLBs

## Exercise 1

### For timing, you’ll need to use a timer (e.g., gettimeofday()). How precise is such a timer? How long does an operation have to take in order for you to time it precisely? (this will help determine how many times, in a loop, you’ll have to repeat a page access in order to time it successfully)

[m_getitmeofday.c](https://github.com/ilshat25/OSTEP/tree/main/19.paging-tlbs/exercises/m_gettimeofday.c)

Timer is precise is up to 1 microsecond. 

## Exercise 2

### Write the program, called `tlb.c`, that can roughly measure the cost of accessing each page. Inputs to the program should be: the number of pages to touch and the number of trials.

good article: https://people.kth.se/~johanmon/ose/assignments/tlb.pdf

[tlb.c](https://github.com/ilshat25/OSTEP/tree/main/19.paging-tlbs/exercises/tlb.c)

### Now write a script in your favorite scripting language (bash?) to run this program, while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration. Run the script on different machines and gather some data. How many trials are needed to get reliable measurements?

[bench.c](https://github.com/ilshat25/OSTEP/tree/main/19.paging-tlbs/exercises/bench.sh)

About 10000 trials is need on my mac 2018.

There's some result:

macbook pro 2018:
```

```
