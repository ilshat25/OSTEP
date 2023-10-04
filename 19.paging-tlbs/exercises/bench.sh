#!/bin/bash

gcc -o tlb tlb.c
count=12
for i in $(seq $count); do
    p=$((2 ** $i));
    ./tlb $p 10000
done