# Chapter 7 SCHEDULER INTRODUCTION

## Exercice 1

### Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

FIFO: \

Job 0 -- Response: 0,   Turnaround: 200, Wait: 0 \ 
Job 1 -- Response: 200, Turnaround: 400, Wait: 200 \
Job 2 -- Response: 400, Turnaround: 600, Wait: 400 \

Avg Response:   (0 + 200 + 400) / 3 = 200 \
Avg Turnaround: (200 + 400 + 600) / 3 = 400 \
Avg Wait:       (0 + 200 + 400) / 3 = 200 \

SJF: \

Job 0 -- Response: 0,   Turnaround: 200, Wait: 0 \ 
Job 1 -- Response: 200, Turnaround: 400, Wait: 200 \
Job 2 -- Response: 400, Turnaround: 600, Wait: 400 \

Avg Response:   (0 + 200 + 400) / 3 = 200 \
Avg Turnaround: (200 + 400 + 600) / 3 = 400 \
Avg Wait:       (0 + 200 + 400) / 3 = 200 \

Metrics the same for both polices because jobs are starting the same time and the length of the jobs are the same.
