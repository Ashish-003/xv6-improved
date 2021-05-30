
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    // printf(1, "ok\n");
    int pid = fork();
    if (pid < 0) {
        printf(1, "Forkerror\n");
        exit();
    } else if (pid == 0) {
        exec(argv[1], (argv + 1));
    } else {
        int r, w;
        waitx(&w, &r);
        printf(1, "Runtime - %d\nWaittime - %d\n", r, w);
    }
    exit();
}