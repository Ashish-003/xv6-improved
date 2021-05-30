# Sheduling Algorithm Comparison

## Timings

- Timings obtained using time function for each scheduling algorithm.

### Small (10 processes ~ 10 secs)

- `MLFQ` - 2164 ticks
- `RR` (default) - 2160 ticks
- `PBS` - 2152 ticks
- `FCFS` - 2175 ticks

### Large (20 processes ~ > 120 seconds)

- `MLFQ` - 16510 ticks
- `RR` (default) - 16551 ticks
- `PBS` - 16401 ticks
- `FCFS` - 17183 ticks

## Analysis

- The timings are not significantly different as each of them has their own best case performance.
- Round Robin performs specifically well in general case.
- FCFS may penalize IO bound processes and cause convoy effect hence shows excessively high runtime.
- MLFQ performs better in larger case due to more frequent queue change in smaller case.
- PBS performs specifically well due to the specific priority assignment in this tester.

## Conclusion

- No specific algorithm can be termed as the best.
- FCFS can be said to be significantly worse than other scheduling algorithm.
- PBS performs best in both cases.
