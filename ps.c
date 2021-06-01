#include "types.h"
#include "fcntl.h"
#include "stat.h"
#include "user.h"
#include "proc_stat.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf(2, "ps: Fatal error: Invalid arguments. Please specify the pid of the process\n");
        exit();
    }

    int pid = atoi(argv[1]);
    if (pid <= 0) {
        printf(2, "ps: Fatal error: Invalid arguments. Please specify the pid of the process\n");
        exit();
    }

    struct proc_stat p;
    if (getpinfo(pid, &p) < 0) {
        printf(2, "ps: Error: Process with pid %d does not exist.\n", pid);
        exit();
    }
    printf(1, "Process information for process with pid %d:\nTotal running time: %d ticks\nNumber of scheduler selections: %d\nCurrent queue: %d\nNumber of running ticks per queue: %d %d %d %d %d\n\n", p.pid, p.runtime, p.num_run, p.current_queue, p.ticks[0], p.ticks[1], p.ticks[2], p.ticks[3], p.ticks[4]);
    exit();
}