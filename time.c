// c4c76835d1286fa240fe02c4da81f6d4

#include "types.h"
#include "fcntl.h"
#include "stat.h"
#include "user.h"

int main(int argc, char** argv) {

    if (argc <= 1) {
        printf(2, "time: Fatal error: No command to time\n");
        exit();
    }

    int pid;
    pid = fork();
    if (pid < 0) {
        printf(2, "time: Fatal error: Unable to run command\n");
        exit();
    } else if (pid == 0) {
        printf(1, "Timing %s\n", argv[1]);
        if (exec(argv[1], argv + 1) < 0) {
            printf(2, "time: Fatal error: Unable to run command\n");
            exit();
        }
    } else if (pid > 0) {
        int wtime, rtime;
        int wid = waitx(&wtime, &rtime);
        printf(1, "Time report for %s\nProcess ID: %d\nWaiting time: %d\nRunning time: %d\n\n", argv[1], wid, wtime, rtime);
        exit();
    }
}