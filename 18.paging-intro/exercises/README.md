# Chapter 18. PAGING: INTRODUCTION

## Exercise 1

### Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the `-v flag`, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags:
###    -P 1k -a 1m -p 512m -v -n 0
###    -P 1k -a 2m -p 512m -v -n 0
###    -P 1k -a 4m -p 512m -v -n 0
### Then, to understand how linear page table size changes as page size grows:
###    -P 1k -a 1m -p 512m -v -n 0
###    -P 2k -a 1m -p 512m -v -n 0
###    -P 4k -a 1m -p 512m -v -n 0
### Before running any of these, try to think about the expected trends. How should page-table size change as the address space grows? As the page size grows? Why not use big pages in general?

As address space grows (with const page size) the page table size grows linear, the number of entries is equal `address space size / page size`

As page size grows (wiht const address space size) the page size shrinks linear.

Big pages leads to small amount of chunks that leads to lower count of processes that can be launched at the same time.

## Exercise 2

### Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example:
###    -P 1k -a 16k -p 32k -v -u 0
###    -P 1k -a 16k -p 32k -v -u 25
###    -P 1k -a 16k -p 32k -v -u 50
###    -P 1k -a 16k -p 32k -v -u 75
###    -P 1k -a 16k -p 32k -v -u 100
### What happens as you increase the percentage of pages that are allocated in each address space?

```
ilssshat$ python paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]  0x00000000
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x00000000
  [       4]  0x00000000
  [       5]  0x00000000
  [       6]  0x00000000
  [       7]  0x00000000
  [       8]  0x00000000
  [       9]  0x00000000
  [      10]  0x00000000
  [      11]  0x00000000
  [      12]  0x00000000
  [      13]  0x00000000
  [      14]  0x00000000
  [      15]  0x00000000

Virtual Address Trace
  VA 0x00003a39 (decimal:    14905) --> 14905 == 0b11101000111001 -> VPN = 14 -> invalid address
  VA 0x00003ee5 (decimal:    16101) --> 16101 == 0b11111011100101 -> VPN = 15 -> invalid address
  VA 0x000033da (decimal:    13274) --> 13274 == 0b11001111011010 -> VPN = 12 -> invalid address
  VA 0x000039bd (decimal:    14781) --> 14781 == 0b11100110111101 -> VPN = 14 -> invalid address
  VA 0x000013d9 (decimal:     5081) --> 5081  == 0b01001111011001 -> VPN = 4  -> invalid address
```

```
ilssshat$ python paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 25
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]  0x80000018
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x00000000
  [       4]  0x00000000
  [       5]  0x80000009
  [       6]  0x00000000
  [       7]  0x00000000
  [       8]  0x80000010
  [       9]  0x00000000
  [      10]  0x80000013
  [      11]  0x00000000
  [      12]  0x8000001f
  [      13]  0x8000001c
  [      14]  0x00000000
  [      15]  0x00000000

Virtual Address Trace
  VA 0x00003986 (decimal:    14726) --> 14726 = 0b11100110000110 -> VPN = 14 -> invalid address
  VA 0x00002bc6 (decimal:    11206) --> 11206 = 0b10101111000110 -> VPN = 10 -> PFN = 19 -> 19 * 1024 + 966 = 20422 -> PA = 0x00004fc6
  VA 0x00001e37 (decimal:     7735) --> 7735  = 0b01111000110111 -> VPN = 7  ->  invalid address
  VA 0x00000671 (decimal:     1649) --> 1649  = 0b00011001110001 -> VPN = 1  ->  invalid address
  VA 0x00001bc9 (decimal:     7113) --> 7113  = 0b01101111001001 -> VPN = 3  ->  invalid address
```

```
ilssshat$ python paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 50
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]  0x80000018
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x8000000c
  [       4]  0x80000009
  [       5]  0x00000000
  [       6]  0x8000001d
  [       7]  0x80000013
  [       8]  0x00000000
  [       9]  0x8000001f
  [      10]  0x8000001c
  [      11]  0x00000000
  [      12]  0x8000000f
  [      13]  0x00000000
  [      14]  0x00000000
  [      15]  0x80000008

Virtual Address Trace
  VA 0x00003385 (decimal:    13189) --> 13189 = 0b11001110000101 -> VPN = 12 -> PFN = 15 -> 15 * 1024 + 901 = 16261 -> PA = 0x00003f85
  VA 0x0000231d (decimal:     8989) --> 8989  = 0b10001100011101 -> VPN = 8  ->  invalid address
  VA 0x000000e6 (decimal:      230) --> 230   = 0b00000011100110 -> VPN = 0  -> PFN = 24 -> 24 * 1024 + 230 = 24806 -> PA = 0x000060e6
  VA 0x00002e0f (decimal:    11791) --> 11791 = 0b10111000001111 -> VPN = 11 -> invalid address
  VA 0x00001986 (decimal:     6534) --> 6534  = 0b01100110000110 -> VPN = 6  -> PFN = 29 -> 29 * 1024 + 390 = 30086 -> PA = 0x00007586
```

With percent increasing the more addresses are available.

## Exercise 3

### Now let’s try some different random seeds, and some different (and sometimes quite crazy) address-space parameters, for variety:
###   -P 8 -a 32 -p 1024 -v -s 1
###   -P 8k -a 32k -p 1m -v -s 2
###   -P 1m -a 256m -p 512m -v -s 3
### Which of these parameter combinations are unrealistic? Why?

Page size for the third example looks too big

## Exercise 4

### Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?

- physical memory size must be GREATER than address space size (for this simulation)
- address space must be a multiple of the pagesize