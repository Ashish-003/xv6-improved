// Per-CPU state
struct cpu {
  uchar apicid;                // Local APIC ID
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table
  volatile uint started;       // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.
  int intena;                  // Were interrupts enabled before pushcli?
  struct proc *proc;           // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

#define NUM_QUEUES (int)5 // c4c76835d1286fa240fe02c4da81f6d4

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)

  int start_time;              // Start time of the process c4c76835d1286fa240fe02c4da81f6d4
  int end_time;                // End time of the process
  int run_time;                // Run time of the process

  int priority;                // The priority of process for PBS, between [0,100], default 60, less is higher
  int timeslices;              // The number of CPU timeslices received by the process c4c76835d1286fa240fe02c4da81f6d4

  int age_time;                // The time when it entered the current queue and is waiting since
  int cur_timeslices;          // The number of timeslices received in current run c4c76835d1286fa240fe02c4da81f6d4
  int queue;                   // The ready queue in which the process is waiting
  int punish;

  int num_run;                // Extra stuff needed for pinfo c4c76835d1286fa240fe02c4da81f6d4
  int ticks[NUM_QUEUES];
};

// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap

// Scheduling algorithms used by scheduler c4c76835d1286fa240fe02c4da81f6d4
#define SCHED_RR 0
#define SCHED_FCFS 1
#define SCHED_PBS 2
#define SCHED_MLFQ 3


// Struct for MLFQ scheduling queue nodes c4c76835d1286fa240fe02c4da81f6d4
struct node {
    struct node *next;
    struct proc *p;
    int use;
};

#define TIMESLICE(i) (int)(1<<i)
#define AGE_LIMIT (int)30

struct node surplus_nodes[NPROC];
struct node *queues[NUM_QUEUES];  // lower indices are higher priority