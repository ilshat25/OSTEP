# Chapter 6 LIMITED DIRECT EXECUTION

## Measure the costs of a system call and context switch

### Cost of system call (0-byte read)

start time: 1689742487813352 ms
end time: 1689742487880254 ms
diff: 66902 ms
it's *~0.67 ms* for a system call (0-byte read)

### Cost of context switch

On OSX *sched setaffinity* is not implemeted, that's why I tried a code from: http://www.hybridkernel.com/2015/01/18/binding_threads_to_cores_osx.html.
But the time doesn't change netherless I tried to set only 1 code.

The time of 4 system calls are substracted from the result as in 1 loop 2 read and 2 write are performed.

start time: 1689746977185639 ms
end time: 1689746977884850 ms
diff: 699211 ms
it's ~4.31 ms for a context switch
