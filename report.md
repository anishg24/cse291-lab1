## 1-1

**Fill in the blanks in the following table using the information you gathered about the cache configuration of the lab machine.**

| Cache | Cache Line Size | Total Size | Associativity | Number of Sets | Raw Latency |
| ----- | --------------- | ---------- | ------------- | -------------- | ----------- |
| L1-I  | 64 B            | 32 KiB     | 8             | 64             | --          |
| L1-D  | 64 B            | 32 KiB     | 8             | 64             | 24          |
| L2    | 64 B            | 256 KiB    | 4             | 1024           | 24          |
| L3    | 64 B            | 6 MiB      | 12            | 8192           | 46          |

## 1-3

**After completing your code, generate the histogram pdf file and include it in the lab report.**

<!-- ![Histogram](./Part1-Timing/Histogram.pdf) -->

## 1-4

**Based on the generated histogram, report two thresholds, one to distinguish between L2 and L3 latency and the other to distinguish between L3 and DRAM latency.**

L2-L3 threshold: Taking greater than 40 cycles is L3 otherwise its likely L1/L2

L3-DRAM threshold: Taking greater than 60 cycles is DRAM otherwise its likely L3

## 2-2

**In the victim's pseudocode above, the victim attempts to load the data indexed by `flag` into the `value` variable. How can you change the victim's code to load the desired data without leaking the flag to the attacker?**


## 3-1

**Given a 64-bit virtual address, fill in the table below.**

| Page Size                             | 4KB     | 2MB     |
| ------------------------------------- | ------- | ------- |
| Page Offset Bits                      |         |         |
| Page Number Bits                      |         |         |
| L2 Set Index Bits                     |         |         |
| L2 Set Index Bits Fully Under Control |         |         |
