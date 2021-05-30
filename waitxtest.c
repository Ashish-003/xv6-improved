#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int main(int argc, char *argv[]) {
    int pid = fork();
    if (pid < 0) {
        printf(1, "Couldn't fork\n");
    } else if (pid == 0) {
        volatile int c = 0;
        for (volatile int i = 0; i < 1000000000; i++)
            c++;
    } else {
        int w, r;
        waitx(&w, &r);
        // printf(1, "Wait time - %d\n", *w);
        // printf(1, "Wait time%d \n", ww);
        printf(1, "Wait time %d\nRun time %d\n", w, r);
        // printf(1, "Run time - %d\n", *r);
    }
    exit();
}