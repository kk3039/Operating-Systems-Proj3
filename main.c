#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "testq.h"
#include "prob2.h"

int main(){
	int i;
	int id[20];
	//printf("%s\n", "test1");
	for(i=0;i<4;i++){
		sem_init(&sem[i],0,1);//suppose there is a car at each region in the first place
	}
	for(i=0;i<4;i++){
		sem_init(&mut[i],0,1);
	}
	//printf("%s\n", "test2");
	//create new threads
	for(i=0;i<20;i++){
		id[i]=i;
	}
	for(i=0;i<20;i++){
	
		pthread_create(&cars[i],NULL,vehicle,(void *)(id+i));
		printf("thread %d created \n",i);
	}
	//printf("%s\n", "test3");
	for(i=0;i<20;i++){

	 	pthread_join(cars[i],NULL);
	}

	//free pointers
	//free(para);
	for(i=0;i<4;i++){
		sem_destroy(&mut[i]);
	}
	return 0;
}