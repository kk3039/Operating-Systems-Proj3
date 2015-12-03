#include "testq.h"
// add an thread in the current queue
void enQueue(struct queue* q, pthread_t thread){
	struct queueNode* temp;
	temp = (struct queueNode *)malloc(sizeof(struct queueNode));
	if (temp == 0){
		printf("nothing created, out of memory\n");
		exit(-1);
	}
	else{
		temp->info = thread;
		temp->next = NULL;
	}

	if(q->head == NULL){
		q->head = temp;
		q->tail = temp;
	}
	else{
		q->tail->next = temp;
		q->tail = temp;
	}
}

//add a thread to the second place of the queue
void skipToTwo(struct queue* q, pthread_t thread){
	struct queueNode* temp;
	//struct queueNode* tempHead;
	struct queueNode* current;
	struct queueNode* current_next;

	temp = (struct queueNode *)malloc(sizeof(struct queueNode));
	if (temp == 0){
		printf("nothing created, out of memory\n");
		exit(-1);
	}
	else{
		temp->info = thread;
		temp->next = NULL;
	}

	if(q->head == NULL){
		q->head = temp;
		q->tail = temp;
	}
	else{
		current=q->head;
		current_next=current->next;
		current->next=temp;
		temp->next=current_next;
	}
}

// add a thread in the front of current queue (add_to_front)
void skipQueue(struct queue* q, pthread_t thread){
	struct queueNode* temp;
	struct queueNode* tempHead;
	temp = (struct queueNode *)malloc(sizeof(struct queueNode));
	if (temp == 0){
		printf("nothing created, out of memory\n");
		exit(-1);
	}
	else{
		temp->info = thread;
		temp->next = NULL;
	}

	if(q->head == NULL){
		q->head = temp;
		q->tail = temp;
	}
	else{
		tempHead=q->head;
		q->head = temp;
		temp->next=tempHead;
	}
}

// take the head off the current queue
void deQueue(struct queue* q){
	struct queueNode* temp;
	temp = (struct queueNode *)malloc(sizeof(struct queueNode));

	temp = q->head;
	if(temp == NULL){
		printf("no node left in the queue\n");
	}

	else{
		// loop to the next queueNode
		q->head = q->head->next;
		if(q->head == NULL){
			q->tail = NULL;
		}
	}

	free(temp);
}

// check the size of the queue
int sizeOfQueue(struct queue *q){
	int i = 0;
	struct queueNode* temp;
	temp = q->head;
	while(temp != NULL){
		temp = temp->next;
		i++;
	}
	return i;
}

// check if the queue is empty
int isEmpty(struct queue *q){
	return q->head != NULL;
}
