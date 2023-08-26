# Chapter 14 MEMORY API

## Exercise 1

### First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?

[null.c](https://github.com/ilshat25/OSTEP/tree/main/14.mem-api/exercises/null.c)

```
ilssshat$ gcc -o null null.c
ilssshat$ ./null
Segmentation fault: 11
```

## Exercise 2

### Next,compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?

```
Thread 2 hit Breakpoint 1, main (argc=1, argv=0x7ff7bfeff9d0) at null.c:4
4           int* x = NULL;
(gdb) n
5           printf("The value under null ref pointer is %d", *x);
(gdb) n

Thread 2 received signal SIGSEGV, Segmentation fault.
0x0000000100003f72 in main (argc=1, argv=0x7ff7bfeff9d0) at null.c:5
5           printf("The value under null ref pointer is %d", *x);
(gdb) p x
$1 = (int *) 0x0
```

## Exercise 3

### Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?

```
ilssshat$ valgrind --leak-check=yes ./null
...
==15081== Invalid read of size 4
==15081==    at 0x100003F72: main (null.c:5)
==15081==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==15081== 
...
```


## Exercise 4

### Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?

[mem-alloc.c](https://github.com/ilshat25/OSTEP/tree/main/14.mem-api/exercises/mem-alloc.c)

As was said on the book, for little programs it's not critical not to free memory before exit, because the OS do this anyway.
Nothing was found using gdb.

valgrind noticed that some memory was not freed:
```
==16694== 4 bytes in 1 blocks are definitely lost in loss record 1 of 35
==16694==    at 0x1001AB4F8: malloc (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==16694==    by 0x100003F3F: main (mem-alloc.c:5)
==16694==
```

## Exercise 5

### Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?

[mem-invalid-out-border.c](https://github.com/ilshat25/OSTEP/tree/main/14.mem-api/exercises/mem-invalid-out-border.c)

```
ilssshat$ ./mem-invalid-out-border
Array of size=100 was allocated on address 0x7fd540f05a40
Try to assign value to 100's element of array
x[100] = 100
mem-invalid-out-border(20287,0x7ff844bfd680) malloc: Incorrect checksum for freed object 0x7fd540f05bd0: probably modified after being freed.
Corrupt value: 0x4000000000000064
mem-invalid-out-border(20287,0x7ff844bfd680) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6
```

On program execute there's checksum errro, (0x7fd540f05bd0 - 0x7fd540f05a40) / sizeof(int) = 100 - the number of array element that was modified.

```
ilssshat$ valgrind --leak-check=yes ./mem-invalid-out-border
...
==20365== Invalid write of size 4
==20365==    at 0x100003EF9: main (mem-invalid-out-border.c:9)
==20365==  Address 0x1001c6660 is 0 bytes after a block of size 400 alloc'd
==20365==    at 0x1001AB4F8: malloc (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20365==    by 0x100003EC6: main (mem-invalid-out-border.c:6)
==20365== 
==20365== Invalid read of size 4
==20365==    at 0x100003F07: main (mem-invalid-out-border.c:10)
==20365==  Address 0x1001c6660 is 0 bytes after a block of size 400 alloc'd
==20365==    at 0x1001AB4F8: malloc (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20365==    by 0x100003EC6: main (mem-invalid-out-border.c:6)
==20365== 
...
```

The program is not correct, it tries to assign value out of array border that leads to undefined behavior.

## Exercise 6

### Create a program that allocates an array of integers (as above),frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?

(mem-invalid-read-after-free.c)[https://github.com/ilshat25/OSTEP/tree/main/14.mem-api/exercises/mem-invalid-read-after-free.c]

```
ilssshat$ ./mem-invalid-read-after-free
Array of size=100 was allocated on address 0x7fc8b6705ac0
Array was freed
Try to print value after free
x[50] = 0
```

In contrast with previous exercise there's no error on program execute.

```
ilssshat$ valgrind --leak-check=yes ./mem-invalid-read-after-free
...
==20688== Invalid read of size 4
==20688==    at 0x100003F1B: main (mem-invalid-read-after-free.c:11)
==20688==  Address 0x1001c65d8 is 200 bytes inside a block of size 400 free'd
==20688==    at 0x1001ACF6E: free (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20688==    by 0x100003EFA: main (mem-invalid-read-after-free.c:8)
==20688==  Block was alloc'd at
==20688==    at 0x1001AB4F8: malloc (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20688==    by 0x100003ED6: main (mem-invalid-read-after-free.c:6)
==20688== 
...
```

But valgrind is still seeing the problem.

## Exercise 7

### Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

(mem-invalid-write-after-free.c)[https://github.com/ilshat25/OSTEP/tree/main/14.mem-api/exercises/mem-invalid-write-after-free.c]

```
ilssshat$ ./mem-invalid-write-after-free
Array of size=100 was allocated on address 0x7f85c8f05ac0
Array was freed
Try to assign value after free
x[50] = 100
```

No error occure.

```
ilssshat$ valgrind --leak-check=yes ./mem-invalid-write-after-free
...
==20794== Invalid write of size 4
==20794==    at 0x100003F0B: main (mem-invalid-write-after-free.c:11)
==20794==  Address 0x1001c65d8 is 200 bytes inside a block of size 400 free'd
==20794==    at 0x1001ACF6E: free (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20794==    by 0x100003EEA: main (mem-invalid-write-after-free.c:8)
==20794==  Block was alloc'd at
==20794==    at 0x1001AB4F8: malloc (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20794==    by 0x100003EC6: main (mem-invalid-write-after-free.c:6)
==20794== 
==20794== Invalid read of size 4
==20794==    at 0x100003F19: main (mem-invalid-write-after-free.c:12)
==20794==  Address 0x1001c65d8 is 200 bytes inside a block of size 400 free'd
==20794==    at 0x1001ACF6E: free (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20794==    by 0x100003EEA: main (mem-invalid-write-after-free.c:8)
==20794==  Block was alloc'd at
==20794==    at 0x1001AB4F8: malloc (in /usr/local/Cellar/valgrind/HEAD-8c360fc/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==20794==    by 0x100003EC6: main (mem-invalid-write-after-free.c:6)
==20794== 
...
```

## Exercise 8

### Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.

TODO

## Exercise 9

### Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.

TODO
