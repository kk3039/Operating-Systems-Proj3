/* queue.h
*queue definitions
*Ying Lu ylu6@wpi.edu
*Qiaoyu Liao qliao@wpi.edu
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
// queueNode for thread
struct queueNode{
	int info;
	struct queueNode* next;
};

// queue for thread
struct queue{
	struct queueNode* head;
	struct queueNode* tail;
};


void enQueue(struct queue* q, pthread_t thread);
void skipToTwo(struct queue* q, pthread_t thread);
void skipQueue(struct queue* q, pthread_t thread);
void deQueue(struct queue* q);
int sizeOfQueue(struct queue *q);
int isEmpty(struct queue *q);