# Chapter 13 ADDRESS SPACE

## Exercise 1

### The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!

*free* is a GNU/LINUX cli for memory display

## Exercise 2

### Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

```
ilssshat$ free -m
      total       used        free        wire        inac/ac     spec        comp        purge
Mem:  16384       7881        2238        3047        8885        766         1443        868
Swap: 3072        1696        1375
```

## Exercise 3

### Next, create a little program that uses a certain amount of memory, called memory-user.c. This program should take one command- line argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefi- nitely, or, perhaps, for a certain amount of time also specified at the command line.

[memory-user.c](https://github.com/ilshat25/OSTEP/tree/main/13.mem-intro/exercises/memory-user.c)

## Exercise 4

### Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?

```
ilssshat$ free --mega // before call ./memory-user 100
      total       used        free        wire        inac/ac     spec        comp        purge       
Mem:  17179       7265        3742        2925        8672        5           1831        790         
Swap: 2147        1195        952         
ilssshat$ free --mega // after call ./memory-user 100
      total       used        free        wire        inac/ac     spec        comp        purge       
Mem:  17179       7328        3629        2936        8774        5           1831        782         
Swap: 2147        1195        952         
ilssshat$ kill -9 39698 // kill memory-user process
ilssshat$ free --mega // after kill ./memory-user 100
      total       used        free        wire        inac/ac     spec        comp        purge       
Mem:  17179       7285        3722        2946        8671        6           1831        790         
Swap: 2147        1195        952   
```

As you can see the amount of used/free memory is changed according to the amount of memory that was queried by memory-user process.

The process can allocate more meory than is physicaly has (it's true for my mac) because of virtual memory (I have read about it here: https://www.chriswrites.com/what-is-virtual-memory-on-the-mac/)

## Exercise 5

### Let’s try one more tool, known as pmap. Spend some time, and read the pmap manual page in detail.

pmap prints information about the address space of a process.

## Exercise 6

### To use pmap, you have to know the process ID of the process you’re interested in. Thus, first run ps auxw to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).

Instead of pmap I will use vmmap on macos

## Exercise 7

### Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?

```
ilssshat$ ./memory-user 100
pid = 40755
104857600 bytes (or 100 megabytes) are going to be allocated
```

```
ilssshat$ /usr/bin/vmmap --summary 40755
Process:         memory-user [40755]
Path:            /Users/USER/*/memory-user
Load Address:    0x104fc0000
Identifier:      memory-user
Version:         ???
Code Type:       X86-64
Platform:        macOS
Parent Process:  bash [74075]

Date/Time:       2023-08-19 13:55:00.382 +0300
Launch Time:     2023-08-19 13:53:56.013 +0300
OS Version:      macOS 13.2.1 (22D68)
Report Version:  7
Analysis Tool:   /usr/bin/vmmap

Physical footprint:         100.3M
Physical footprint (peak):  100.3M
Idle exit: untracked
----

ReadOnly portion of Libraries: Total=186.9M resident=19.9M(11%) swapped_out_or_unallocated=167.0M(89%)
Writable regions: Total=117.1M written=100.1M(85%) resident=100.1M(86%) swapped_out=0K(0%) unallocated=17.0M(14%)

                                VIRTUAL RESIDENT    DIRTY  SWAPPED VOLATILE   NONVOL    EMPTY   REGION 
REGION TYPE                        SIZE     SIZE     SIZE     SIZE     SIZE     SIZE     SIZE    COUNT (non-coalesced) 
===========                     ======= ========    =====  ======= ========   ======    =====  ======= 
Kernel Alloc Once                    8K       4K       4K       0K       0K       0K       0K        1 
MALLOC guard page                   16K       0K       0K       0K       0K       0K       0K        4 
MALLOC metadata                     72K      60K      60K       0K       0K       0K       0K        5 
MALLOC_LARGE                     100.0M   100.0M   100.0M       0K       0K       0K       0K        1         see MALLOC ZONE table below
MALLOC_LARGE metadata                4K       4K       4K       0K       0K       0K       0K        1         see MALLOC ZONE table below
MALLOC_SMALL                      8192K       8K       8K       0K       0K       0K       0K        1         see MALLOC ZONE table below
MALLOC_TINY                       1024K      16K      16K       0K       0K       0K       0K        1         see MALLOC ZONE table below
STACK GUARD                       56.0M       0K       0K       0K       0K       0K       0K        1 
Stack                             8192K      20K      20K       0K       0K       0K       0K        1 
VM_ALLOCATE                          4K       4K       4K       0K       0K       0K       0K        1 
__DATA                             199K     116K      49K       0K       0K       0K       0K       36 
__DATA_CONST                       247K     184K       4K       0K       0K       0K       0K       34 
__DATA_DIRTY                        63K      63K      63K       0K       0K       0K       0K       23 
__LINKEDIT                       181.8M    15.7M       0K       0K       0K       0K       0K        3 
__OBJC_RO                         65.5M    28.4M       0K       0K       0K       0K       0K        1 
__OBJC_RW                         1989K    1341K     1520       0K       0K       0K       0K        2 
__TEXT                            5236K    4356K       0K       0K       0K       0K       0K       42 
dyld private memory                256K      28K      28K       0K       0K       0K       0K        1 
shared memory                       16K      16K      16K       0K       0K       0K       0K        2 
unused but dirty shlib __DATA       15K      15K      15K       0K       0K       0K       0K       17 
===========                     ======= ========    =====  ======= ========   ======    =====  ======= 
TOTAL                            428.2M   150.2M   100.3M       0K       0K       0K       0K      178 

                                 VIRTUAL   RESIDENT      DIRTY    SWAPPED ALLOCATION      BYTES DIRTY+SWAP          REGION
MALLOC ZONE                         SIZE       SIZE       SIZE       SIZE      COUNT  ALLOCATED  FRAG SIZE  % FRAG   COUNT
===========                      =======  =========  =========  =========  =========  =========  =========  ======  ======
DefaultMallocZone_0x105051000     109.0M     100.0M     100.0M         0K        176     100.0M        16K      1%       4

```

## Exercise 8

### Finally, let’s run pmap on your memory-user program, with dif- ferent amounts of used memory. What do you see here? Does the output from pmap match your expectations?

```
ilssshat$ ./memory-user 32000
pid = 40920
33554432000 bytes (or 32000 megabytes) are going to be allocated
memory was allocated
```

```
ilssshat$ /usr/bin/vmmap --summary 40920
Process:         memory-user [40920]
Path:            /Users/USER/*/memory-user
Load Address:    0x10c3c3000
Identifier:      memory-user
Version:         ???
Code Type:       X86-64
Platform:        macOS
Parent Process:  bash [74075]

Date/Time:       2023-08-19 14:02:18.253 +0300
Launch Time:     2023-08-19 14:01:59.312 +0300
OS Version:      macOS 13.2.1 (22D68)
Report Version:  7
Analysis Tool:   /usr/bin/vmmap

Physical footprint:         2.0G
Physical footprint (peak):  2.0G
Idle exit: untracked
----

ReadOnly portion of Libraries: Total=186.9M resident=20.0M(11%) swapped_out_or_unallocated=166.9M(89%)
Writable regions: Total=31.3G written=2.0G(6%) resident=2.0G(6%) swapped_out=0K(0%) unallocated=29.3G(94%)

                                VIRTUAL RESIDENT    DIRTY  SWAPPED VOLATILE   NONVOL    EMPTY   REGION 
REGION TYPE                        SIZE     SIZE     SIZE     SIZE     SIZE     SIZE     SIZE    COUNT (non-coalesced) 
===========                     ======= ========    =====  ======= ========   ======    =====  ======= 
Kernel Alloc Once                    8K       4K       4K       0K       0K       0K       0K        1 
MALLOC guard page                   16K       0K       0K       0K       0K       0K       0K        4 
MALLOC metadata                     72K      60K      60K       0K       0K       0K       0K        5 
MALLOC_LARGE                       2.1G     2.0G     2.0G       0K       0K       0K       0K       17         see MALLOC ZONE table below
MALLOC_LARGE (reserved)           29.1G       0K       0K       0K       0K       0K       0K        1         see MALLOC ZONE table below
MALLOC_LARGE metadata                4K       4K       4K       0K       0K       0K       0K        1         see MALLOC ZONE table below
MALLOC_SMALL                      8192K       8K       8K       0K       0K       0K       0K        1         see MALLOC ZONE table below
MALLOC_TINY                       1024K      16K      16K       0K       0K       0K       0K        1         see MALLOC ZONE table below
STACK GUARD                       56.0M       0K       0K       0K       0K       0K       0K        1 
Stack                             8192K      20K      20K       0K       0K       0K       0K        1 
VM_ALLOCATE                          4K       4K       4K       0K       0K       0K       0K        1 
__DATA                             199K     116K      49K       0K       0K       0K       0K       36 
__DATA_CONST                       247K     184K       4K       0K       0K       0K       0K       34 
__DATA_DIRTY                        63K      63K      63K       0K       0K       0K       0K       23 
__LINKEDIT                       181.8M    15.8M       0K       0K       0K       0K       0K        3 
__OBJC_RO                         65.5M    28.5M       0K       0K       0K       0K       0K        1 
__OBJC_RW                         1989K    1341K     1520       0K       0K       0K       0K        2 
__TEXT                            5236K    4356K       0K       0K       0K       0K       0K       42 
dyld private memory                256K      28K      28K       0K       0K       0K       0K        1 
shared memory                       16K      16K      16K       0K       0K       0K       0K        2 
unused but dirty shlib __DATA       15K      15K      15K       0K       0K       0K       0K       17 
===========                     ======= ========    =====  ======= ========   ======    =====  ======= 
TOTAL                             31.6G     2.1G     2.0G       0K       0K       0K       0K      195 

                                 VIRTUAL   RESIDENT      DIRTY    SWAPPED ALLOCATION      BYTES DIRTY+SWAP          REGION
MALLOC ZONE                         SIZE       SIZE       SIZE       SIZE      COUNT  ALLOCATED  FRAG SIZE  % FRAG   COUNT
===========                      =======  =========  =========  =========  =========  =========  =========  ======  ======
DefaultMallocZone_0x10c454000       2.1G       2.0G       2.0G         0K        176      31.3G         0K      0%      20
```