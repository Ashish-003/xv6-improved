// c4c76835d1286fa240fe02c4da81f6d4

#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "spinlock.h"
#include "traps.h"
#include "x86.h"

struct node* q_alloc() {
    for (int i = 0; i < NPROC; i++) {
        if (surplus_nodes[i].use == 0) {
            surplus_nodes[i].use = 1;
            return &surplus_nodes[i];
        }
    }
    return 0;
}

void q_free(struct node* p) {
    p->use = 0;
}

struct node* push(struct node* head, struct proc* p) {
    struct node* new = q_alloc();
    new->p = p;
    new->next = 0;

    if (head == 0) {
        return new;
    }

    struct node* cur = head;
    while (cur->next != 0) {
        cur = cur->next;
    }
    cur->next = new;
    return head;
}

struct node* pop(struct node* head) {
    if (head == 0) {
        return 0;
    }

    struct node* temp = head->next;
    q_free(head);
    return temp;
}

// shifts all nodes with node->p->age_time > threshold from FROM list to TO list
// returns the number of nodes shifted and updates the head pointers
int split(struct node** from, struct node** to, int threshold) {
    if (from == 0 || to == 0) {
        return -1;
    }

    if (*from == 0) {
        return 0;
    }

    struct node* cur = *from;
    struct node* prev = 0;

    int count = 0;

    while (cur != 0) {
        if (ticks - cur->p->age_time > threshold) {
            cur->p->queue--;
            cur->p->age_time = ticks;
            count++;
            prev = cur;
            cur = cur->next;
        } else {
            break;
        }
    }
    if (prev == 0) {
        // nothing to move
        return 0;
    }

    if (*to != 0) {
        struct node* to_end = *to;
        while (to_end->next != 0) {
            to_end = to_end->next;
        }

        prev->next = 0;
        to_end->next = *from;
        *from = cur;
    } else {
        prev->next = 0;
        *to = *from;
        *from = cur;
    }

    // something to move
    // prev->next = *to;
    // *to = *from;
    // *from = cur;
    return count;
}

int length(struct node* head) {
    // The argument is a copy of the head pointer, so it is not affected
    int count = 0;
    while (head != 0) {
        head = head->next;
        count++;
    }
    return count;
}