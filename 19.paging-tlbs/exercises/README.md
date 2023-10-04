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

macbook pro 2018, 2,3 GHz Quad-Core Intel Core i5, 16 GB 2133 MHz LPDDR3:
```
ilssshat$ ./bench.sh 
With 2    pages and 4000  trials, average access time = 2.095250 ns
With 4    pages and 4000  trials, average access time = 1.946250 ns
With 8    pages and 4000  trials, average access time = 1.874969 ns
With 16   pages and 4000  trials, average access time = 8.965531 ns
With 32   pages and 4000  trials, average access time = 9.328101 ns
With 64   pages and 4000  trials, average access time = 9.130352 ns
With 128  pages and 4000  trials, average access time = 9.835205 ns
With 256  pages and 4000  trials, average access time = 9.819797 ns
With 512  pages and 4000  trials, average access time = 9.608551 ns
With 1024 pages and 4000  trials, average access time = 9.792068 ns
With 2048 pages and 4000  trials, average access time = 12.406692 ns
With 4096 pages and 4000  trials, average access time = 13.002484 ns
```
