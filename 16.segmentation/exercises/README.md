# Chpater 16 SEGMANTATION

## Exercise 1

###  First let’s use a tiny address space to translate some addresses. Here’s a simple set of parameters with a few different random seeds; can you translate the addresses?

```
ilssshat$ python segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
ARG seed 0
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> 108 == 0b1101100 -> segment 2 -> 128 - 108 = 20 <= 20 --> valid, PA = 512 - 20 = 492
  VA  1: 0x00000061 (decimal:   97) --> 97  == 0b1100001 -> segment 2 -> 128 - 97  = 31 > 20 --> segmentation violation
  VA  2: 0x00000035 (decimal:   53) --> 53  == 0b0110101 -> segment 1 -> 53 - 0 = 53 >= 20     --> segmentation violation
  VA  3: 0x00000021 (decimal:   33) --> 33  == 0b0100001 -> segment 1 -> 33 - 0 = 33 >= 20     --> segmentation violation
  VA  4: 0x00000041 (decimal:   65) --> 65  == 0b1000001 -> segment 2 -> 128 - 65 = 63 >= 20   --> segmentation violation
```

```
ilssshat$ python segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
ARG seed 1
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> 17  == 0b0010001 -> segment 1 -> 17 - 0 = 17 < 20 -> valid, PA = 0 + 17 = 17
  VA  1: 0x0000006c (decimal:  108) --> 108 == 0b1101100 -> segment 2 -> 128 - 108 = 20 <= 20 --> valid, PA = 512 - 20 = 492
  VA  2: 0x00000061 (decimal:   97) --> 97  == 0b1100001 -> segment 2 -> 128 - 97  = 31 >= 20 --> segmentation violation
  VA  3: 0x00000020 (decimal:   32) --> 32  == 0b0100000 -> segment 1 -> 32 - 0 = 32 >= 20 --> segmentation violation
  VA  4: 0x0000003f (decimal:   63) --> 63  == 0b0111111 -> segment 1 -> 63 - 0 = 63 >= 20 --> segmentation violation
```

```
ilssshat$ python segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
ARG seed 2
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000007a (decimal:  122) --> 122 == 0b1011010 -> segment 2 -> 128 - 122 = 6 <= 20 --> valid, PA = 512 - 6 = 506
  VA  1: 0x00000079 (decimal:  121) --> 121 == 0b1011001 -> segment 2 -> 128 - 121 = 7 <= 20 --> valid, PA = 512 - 7 = 505
  VA  2: 0x00000007 (decimal:    7) --> 7   == 0b0000111 -> segment 1 -> 7 - 0 = 7 < 20 --> valid, PA = 0 + 7 = 7
  VA  3: 0x0000000a (decimal:   10) --> 10  == 0b0001010 -> segment 1 -> 10 - 0 = 10 < 20 --> valid, PA = 0 + 10 = 10
  VA  4: 0x0000006a (decimal:  106) --> 106 == 0b1101010 -> segment 2 -> 128 - 106 = 22 > 20 -> segmentation violation
```

## Exercise 2

### Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). What is the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? What are the lowest and highest illegal addresses in this entire address space? Finally, how would you run segmentation.py with the -A flag to test if you are right?

highest legal virtual address in segment 0 = base0 + border0 - 1
lowest legal virtual address in segment 1 = base1 - border1
lowest illegal address in entire address space = base0 - 1
highest illegal address in entire address space = base1

```
ilssshat$ python segmentation.py -a 128 -p 512 -b 128 -l 20 -B 512 -L 20 -A 0,19,108,127,20,128 -c
ARG seed 0
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000080 (decimal 128)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000000 (decimal:    0) --> VALID in SEG0: 0x00000080 (decimal:  128)
  VA  1: 0x00000013 (decimal:   19) --> VALID in SEG0: 0x00000093 (decimal:  147)
  VA  2: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
  VA  3: 0x0000007f (decimal:  127) --> VALID in SEG1: 0x000001ff (decimal:  511)
  VA  4: 0x00000014 (decimal:   20) --> SEGMENTATION VIOLATION (SEG0)
Error: virtual address 128 cannot be generated in an address space of size 128
```

## Exercise 3

### Let’s say we have a tiny 16-byte address space in a 128-byte physical memory. What base and bounds would you set up so as to get the simulator to generate the following translation results for the specified address stream: valid, valid, violation, ..., violation, valid, valid? Assume the following parameters: segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 ? --l0 ? --b1 ? --l1 ?

```
ilssshat$ python segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 8 --l0 2 --b1 12  --l1 2 -c
ARG seed 0
ARG address space size 16
ARG phys mem size 128

Segment register information:

  Segment 0 base  (grows positive) : 0x00000008 (decimal 8)
  Segment 0 limit                  : 2

  Segment 1 base  (grows negative) : 0x0000000c (decimal 12)
  Segment 1 limit                  : 2

Virtual Address Trace
  VA  0: 0x00000000 (decimal:    0) --> VALID in SEG0: 0x00000008 (decimal:    8)
  VA  1: 0x00000001 (decimal:    1) --> VALID in SEG0: 0x00000009 (decimal:    9)
  VA  2: 0x00000002 (decimal:    2) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000003 (decimal:    3) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000004 (decimal:    4) --> SEGMENTATION VIOLATION (SEG0)
  VA  5: 0x00000005 (decimal:    5) --> SEGMENTATION VIOLATION (SEG0)
  VA  6: 0x00000006 (decimal:    6) --> SEGMENTATION VIOLATION (SEG0)
  VA  7: 0x00000007 (decimal:    7) --> SEGMENTATION VIOLATION (SEG0)
  VA  8: 0x00000008 (decimal:    8) --> SEGMENTATION VIOLATION (SEG1)
  VA  9: 0x00000009 (decimal:    9) --> SEGMENTATION VIOLATION (SEG1)
  VA 10: 0x0000000a (decimal:   10) --> SEGMENTATION VIOLATION (SEG1)
  VA 11: 0x0000000b (decimal:   11) --> SEGMENTATION VIOLATION (SEG1)
  VA 12: 0x0000000c (decimal:   12) --> SEGMENTATION VIOLATION (SEG1)
  VA 13: 0x0000000d (decimal:   13) --> SEGMENTATION VIOLATION (SEG1)
  VA 14: 0x0000000e (decimal:   14) --> VALID in SEG1: 0x0000000a (decimal:   10)
  VA 15: 0x0000000f (decimal:   15) --> VALID in SEG1: 0x0000000b (decimal:   11)
```

## Exercise 4

### Assume we want to generate a problem where roughly 90% of the randomly-generated virtual addresses are valid (not segmentation violations). How should you configure the simulator to do so? Which parameters are important to getting this outcome?

address space * 0.9 ~= border0 + border1

example:
128 * 0.9 = 115.2 ~= 60 + 55 

```
segmentation.py -a 128 -p 512 -b 128 -l 60 -B 512 -L 55 -n 10 -c
ARG seed 10
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000080 (decimal 128)
  Segment 0 limit                  : 60

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 55

Virtual Address Trace
  VA  0: 0x00000049 (decimal:   73) --> VALID in SEG1: 0x000001c9 (decimal:  457)
  VA  1: 0x00000036 (decimal:   54) --> VALID in SEG0: 0x000000b6 (decimal:  182)
  VA  2: 0x00000049 (decimal:   73) --> VALID in SEG1: 0x000001c9 (decimal:  457)
  VA  3: 0x0000001a (decimal:   26) --> VALID in SEG0: 0x0000009a (decimal:  154)
  VA  4: 0x00000068 (decimal:  104) --> VALID in SEG1: 0x000001e8 (decimal:  488)
  VA  5: 0x00000069 (decimal:  105) --> VALID in SEG1: 0x000001e9 (decimal:  489)
  VA  6: 0x00000053 (decimal:   83) --> VALID in SEG1: 0x000001d3 (decimal:  467)
  VA  7: 0x00000014 (decimal:   20) --> VALID in SEG0: 0x00000094 (decimal:  148)
  VA  8: 0x00000042 (decimal:   66) --> SEGMENTATION VIOLATION (SEG1)
  VA  9: 0x00000029 (decimal:   41) --> VALID in SEG0: 0x000000a9 (decimal:  169)
```

## Exercise 5

### Can you run the simulator such that no virtual addresses are valid? How?

set border to 0

```
ilssshat$ python segmentation.py -a 128 -p 512 -b 128 -l 0 -B 512 -L 0 -n 10 -c -s 10
ARG seed 10
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000080 (decimal 128)
  Segment 0 limit                  : 0

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 0

Virtual Address Trace
  VA  0: 0x00000049 (decimal:   73) --> SEGMENTATION VIOLATION (SEG1)
  VA  1: 0x00000036 (decimal:   54) --> SEGMENTATION VIOLATION (SEG0)
  VA  2: 0x00000049 (decimal:   73) --> SEGMENTATION VIOLATION (SEG1)
  VA  3: 0x0000001a (decimal:   26) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000068 (decimal:  104) --> SEGMENTATION VIOLATION (SEG1)
  VA  5: 0x00000069 (decimal:  105) --> SEGMENTATION VIOLATION (SEG1)
  VA  6: 0x00000053 (decimal:   83) --> SEGMENTATION VIOLATION (SEG1)
  VA  7: 0x00000014 (decimal:   20) --> SEGMENTATION VIOLATION (SEG0)
  VA  8: 0x00000042 (decimal:   66) --> SEGMENTATION VIOLATION (SEG1)
  VA  9: 0x00000029 (decimal:   41) --> SEGMENTATION VIOLATION (SEG0)
```