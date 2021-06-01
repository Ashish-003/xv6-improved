// c4c76835d1286fa240fe02c4da81f6d4

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "proc_stat.h"

int main(void) {
    set_priority(0);
    int pid;
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            // set_priority(i*10);
#ifndef DEBUG
            int my_pid = getpid();
            for (int g = 0; g < 5; g++)
                printf(1, "i: %d pid: %d\n", i, my_pid);
#endif
            volatile int j = 0;
            for (volatile int k = 0; k < 100000000; k++) {
                j++;
                j = j % 12;
            }
            exit();
        }
        // printf(2, "***Made %d\n", pid);
    }
    for (int i = 0; i < 5; i++) {
        wait();
    }

    // struct proc_stat p;
    // if (getpinfo(getpid(), &p) == 0) {
    //     printf(1, "Process information for process with pid %d:\nTotal running time: %d ticks\nNumber of scheduler selections: %d\nCurrent queue: %d\nNumber of running ticks per queue: %d %d %d %d %d\n\n", p.pid, p.runtime, p.num_run, p.current_queue, p.ticks[0], p.ticks[1], p.ticks[2], p.ticks[3], p.ticks[4]);
    // }
    
    exit();
}