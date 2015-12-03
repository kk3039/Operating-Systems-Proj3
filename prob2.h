#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NW 0
#define SW 1
#define SE 2
#define NE 3

#define DONE 0
#define RIGHT 1
#define STRAIGHT 2
#define LEFT 3


// struct para{
// 	int num;
// 	int approach;
// 	int turn;
// 	int isMotorcade;
// 	int isEmergency;
// };

// typedef struct para Para;

sem_t sem[4];//counts waiting vehicles
sem_t mut[4];//1 for vacant region, 0 for occupied


int recorder[4];//recording the intersection states to avoid deadlock
pthread_t cars[20];
struct queue queue[4];//queue of threads for four critical regions

void * vehicle(void * para);