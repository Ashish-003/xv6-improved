// Struct for getpinfo c4c76835d1286fa240fe02c4da81f6d4
struct proc_stat {
    int pid;
    int runtime;
    int num_run;
    int current_queue;
    int ticks[5];
};