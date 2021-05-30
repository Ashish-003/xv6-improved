#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "procstat.h"

int sys_fork(void) {
    return fork();
}

int sys_exit(void) {
    exit();
    return 0;  // not reached
}

int sys_wait(void) {
    return wait();
}

// Change
int sys_waitx(void) {
    int *wtime, *rtime;
    if (argptr(0, (void *)&wtime, sizeof(wtime)) < 0 ||
        argptr(1, (void *)&rtime, sizeof(rtime)) < 0)
        return -1;
    return waitx(wtime, rtime);
}

int sys_getpinfo(void) {
    struct proc_stat *ps;
    int pid;
    if (argptr(0, (void *)&ps, sizeof(ps)) < 0 || argint(1, &pid) < 0)
        return -1;
    return getpinfo(ps, pid);
}

int sys_set_priority(void) {
    int v, pid;

    if (argint(0, &v) < 0 || argint(1, &pid) < 0)
        return -1;
    return set_priority(v, pid);
}

int sys_printStatus(void) {
    printStatus();
    return 1;
}

int sys_kill(void) {
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

int sys_getpid(void) {
    return myproc()->pid;
}

int sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

int sys_sleep(void) {
    int n;
    uint ticks0;

    if (argint(0, &n) < 0)
        return -1;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (myproc()->killed) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void) {
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}