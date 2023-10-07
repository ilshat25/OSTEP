# Chapter 21. Paging: Beyond Physical memory

## Exercise 1

First, open two separate terminal connections to the same machine, so that you can easily run something in one window and the other.
Now, in one window, run vmstat 1, which shows statistics about machine usage every second. Read the man page, the associated README, and any other information you need so that you can understand its output. Leave this window running vmstat for the rest of the exercises below.
Now, we will run the program mem.c but with very little memory usage. This can be accomplished by typing ./mem 1 (which uses only 1 MB of memory). How do the CPU usage statistics change when running mem? Do the numbers in the user time column make sense? How does this change when running more than one instance of mem at once?
- - -

After running the program cpu usage of user code arise
```
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
...
 0  0      0 15603120  21972 495064    0    0     0     0  154  166  0  0 100  0  0
 0  0      0 15602932  21972 495068    0    0     0     0  319  487  0  0 100  0  0
 1  0      0 15602664  21972 495068    0    0     0     0  441  407  6  0 94  0  0
 1  0      0 15601616  21980 495068    0    0     0   176  594  379 13  0 87  0  0
 1  0      0 15602012  21980 495068    0    0     0     0  529  345 13  0 87  0  0
 1  0      0 15602020  21980 495068    0    0     0     0  426  260 13  0 87  0  0
...
```

With more than one instance free memory and time spent running non-kernel mode increased proprtionaly
```
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 ...
 2  0      0 15936480  17744 203976    0    0     0     0 2706 3084 27  1 72  0  0
 2  0      0 15936968  17760 203976    0    0    16     0 1181  647 25  0 74  0  0
 3  0      0 15933060  17760 203996    0    0     0     0 2396 2610 32  1 67  0  0
 3  0      0 15934568  17768 203996    0    0     0    40 1528  678 37  1 61  0  0
 3  0      0 15934828  17768 203964    0    0     0     0 2404 2527 38  0 62  0  0
```


## Exercise 2

Let’s now start looking at some of the memory statistics while running mem. We’ll focus on two columns: swpd (the amount of virtual memory used) and free (the amount of idle memory). Run ./mem 1024 (which allocates 1024 MB) and watch how these val- ues change. Then kill the running program (by typing control-c) and watch again how the values change. What do you notice about the values? In particular, how does the free column change when the program exits? Does the amount of free memory increase by the expected amount when mem exits?
- - - 


As it can be seen, after running the program free memory decreased by ~1Md, after killing it free memory increased by ~1Mb. No swapped memory was used.
```
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
...
// on launch
 0  0      0 15921176  18252 204732    0    0     0    28 1176 1928  0  0 99  0  0
 0  0      0 15921184  18252 204732    0    0     0     0  272  452  0  0 100  0  0
 1  0      0 15336420  18252 204732    0    0     0     0 2151 2469  6  7 87  0  0
 2  0      0 14870220  18252 204732    0    0     0     0  582  336  6  7 87  0  0
 1  0      0 14870324  18252 204716    0    0     0     0 1474 2045 13  1 87  0  0
...
// on killing
 1  0      0 14865668  18372 204596    0    0     0     0 1526 2286 13  0 87  0  0
 1  0      0 14864992  18380 204596    0    0     0    12  729  830 13  0 87  0  0
 0  0      0 15915184  18380 204596    0    0     0     0 1914 2731  7  1 92  0  0
 0  0      0 15915724  18380 204596    0    0     0     0  310  365  0  0 100  0  0
 0  0      0 15916216  18380 204596    0    0     0     0 1160 1958  0  0 100  0  0
...
```


## Exercise 3

We’ll next look at the swap columns (si and so), which indicate how much swapping is taking place to and from the disk. Of course, to activate these, you’ll need to run mem with large amounts of memory. First, examine how much free memory is on your Linux system (for example, by typing cat /proc/meminfo; type man proc for details on the /proc file system and the types of informa- tion you can find there). One of the first entries in /proc/meminfo is the total amount of memory in your system. Let’s assume it’s something like 8 GB of memory; if so, start by running mem 4000 (about 4 GB) and watching the swap in/out columns. Do they ever give nonzero values? Then, try with 5000, 6000, etc. What happens to these values as the program enters the second loop (and beyond), as compared to the first loop? How much data (total) are swapped in and out during the second, third, and subsequent loops? (do the numbers make sense?)
- - - 

On my virtual machine there's 16Gb of RAM. To force swapping i laucnhed `./mem 16000`
It can be seen, that memory allocating not at once, but linear on time and when it came to critical point (250mb) swapping enabled, constat swap in/out there. There's always some blocks to write in to swap and sometimes zeroes when reading from it.

```
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0      0 15905640  48080 209844    0    0     0     0   82  118  0  0 100  0  0
 0  0      0 15905324  48088 209844    0    0     0    12  290  506  0  0 100  0  0
 1  0      0 15678016  48088 209844    0    0     0     0  309  326  3  1 96  0  0
 1  0      0 14947520  48088 209844    0    0     0     0  490  267  7  6 87  0  0
...
 1  0      0 3196084  48112 209844    0    0     0     0  347  144  7  6 88  0  0
 1  0      0 2459804  48112 209844    0    0     0    12  337  119  7  5 87  0  0
 1  0      0 1713324  48120 209836    0    0     0    12  342  139  7  5 87  0  0
 1  0      0 973292  48120 209844    0    0     0     0  365  152  7  6 87  0  0
 1  0      0 234252  48120 209844    0    0     0     0  348  135  7  5 87  0  0
 1  6 228620 273140    496  23976 1036 228524  8940 228524 1444 1602  2  4 58 36  0
 1  6 451084 145092    496  21084  956 223752 18988 223764 26522 2493  1  2 48 48  0
 1  5 499712 181656    792  29748 21216 58668 29924 58668 2151 3371  0  1 44 55  0
 0  1 484864 173976    928  35764 32780 8020 40332  8020 2222 3887  0  0 67 33  0
 0  1 503296 177156   2744  40216 17784 33460 24492 33460 1807 2029  0  0 78 21  0
 0  2 495360 168724   2744  40224 8168    0  8176     0  765  902  0  0 85 14  0
...
```


## Exercise 4

Do the same experiments as above, but now watch the other statistics (such as CPU utilization, and block I/O statistics). How do they change when mem is running?
- - -

CPU utilization was closed to zero, too much time was spent waiting to disk i/o


## Exercise 5

Now let’s examine performance. Pick an input for mem that com-fortably fits in memory (say 4000 if the amount of memory on the system is 8 GB). How long does loop 0 take (and subsequent loops 1, 2, etc.)? Now pick a size comfortably beyond the size of memory (say 12000 again assuming 8 GB of memory). How long do the loops take here? How do the bandwidth numbers compare? How different is performance when constantly swapping versus fitting everything comfortably in memory? Can you make a graph, with the size of memory used by mem on the x-axis, and the bandwidth of accessing said memory on the y-axis? Finally, how does the performance of the first loop compare to that of subsequent loops, for both the case where everything fits in memory and where it doesn’t?
- - -

I have two launches:
with 10Gb and no swapping
```
ilssshat-vm$ ./mem 10000
allocating 10485760000 bytes (10000.00 MB)
  number of integers in array: 2621440000
loop 0 in 14012.09 ms (bandwidth: 713.67 MB/s)
loop 1 in 5630.04 ms (bandwidth: 1776.18 MB/s)
loop 2 in 5672.21 ms (bandwidth: 1762.98 MB/s)
loop 3 in 5637.59 ms (bandwidth: 1773.81 MB/s)
loop 4 in 5627.82 ms (bandwidth: 1776.89 MB/s)
loop 5 in 5615.88 ms (bandwidth: 1780.66 MB/s)
loop 6 in 5816.94 ms (bandwidth: 1719.12 MB/s)
loop 7 in 5751.84 ms (bandwidth: 1738.57 MB/s)
loop 8 in 5787.45 ms (bandwidth: 1727.88 MB/s)
```

and with 16Gb and swapping:
```
ilssshat-vm$ ./mem 16000
allocating 16777216000 bytes (16000.00 MB)
  number of integers in array: 4194304000
loop 0 in 25382.74 ms (bandwidth: 630.35 MB/s)
loop 1 in 894990.58 ms (bandwidth: 17.88 MB/s)
```

The difference between first and second loop is looks like difference between "cold" and "hot" cache or maybe "lazy" pages allocations (actually this one I swa on vmstat, when free memory decrease constanly on time), with RAM only second loop is three times faster than first one. With swapped model second run is slower than first, it's because first run tried to be RAM only while it fits, and on the end implied swap memory. Swap memory 1000 times slower than RAM.


## Exercise 6

Swap space isn’t infinite. You can use the tool swapon with the -s flag to see how much swap space is available. What happens if you try to run mem with increasingly large values, beyond what seems to be available in swap? At what point does the memory allocation fail?
- - -

```
ilssshat-vm$ swapon -s
Filename                                Type            Size    Used    Priority
/swapfile                               file            8388604 138140  -2
```

With more than RAM + swap memory allocation fails:
```
ilssshat-vm$ ./mem 24000
allocating 25165824000 bytes (24000.00 MB)
memory allocation failed
```


## Exercise 7

Finally, if you’re advanced, you can configure your system to use different swap devices using swapon and swapoff. Read the man pages for details. If you have access to different hardware, see how the performance of swapping changes when swapping to a classic hard drive, a flash-based SSD, and even a RAID array. How much can swapping performance be improved via newer devices? How close can you get to in-memory performance?
- - -

Actually on my vm tehere weren't swapped memory. I add it myself throug guide: https://www.digitalocean.com/community/tutorials/how-to-add-swap-space-on-ubuntu-20-04

The faster hardware is the fater swapping memory you will have
