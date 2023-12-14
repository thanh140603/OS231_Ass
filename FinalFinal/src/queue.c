#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

#ifdef MLQ_SCHED
int exhaust(struct queue_t * q) {
	return (q->slots == 0);
}
#endif

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */
	if (q->size == MAX_QUEUE_SIZE) return;
#ifdef MLQ_SCHED
	++q->size;
	q->proc[(q->tail++) % MAX_QUEUE_SIZE] = proc;
#else
	q->proc[q->size++] = proc;
#endif	
}

struct pcb_t * dequeue(struct queue_t * q) {
	if (empty(q)) return NULL;
#ifdef MLQ_SCHED
	--q->size;
	--q->slots;
	return q->proc[(q->head++) % MAX_QUEUE_SIZE];
#else
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	int i, j;
	for (i = 1, j = 0; i < q->size; ++i) {
		if (q->proc[j]->prio < q->proc[i]->prio) {
			j = i;
		}
	}
	struct pcb_t * ret = q->proc[j];
	q->proc[j] = q->proc[--q->size];
	return ret;
#endif
}
