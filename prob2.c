#include <stdio.h>
#include <stdlib.h>
#include "testq.h"
#include <pthread.h>
#include <semaphore.h>
#include "prob2.h"



void * vehicle(void * para){
	while(1){
	int from,to,next,step,isEmergency,isMotorcade;
	int * plate=para;
	// from=para->approach;
	// to=para->turn;
	// plate=para->num;
	// next=(from+1)%4;
	// step=to-1;
	//printf("create vehicle %d\n",*plate);
	from=rand()%4;
	to=rand()%3+1;
	int r;

	
	printf("%d recorder: %d, %d, %d, %d\n",*plate,recorder[0],recorder[1],recorder[2],recorder[3]);
	getchar();

	if((*plate)%10==0){
		//*plate->
		isEmergency=1;
	}else{
		//para->
		isEmergency=0;
	}
	printf("\t\tcreate vehicle %d, from %d, to %d, turn %d, isEmergency %d\n",*plate,from,(from+to-1)%4,to,isEmergency);

	if((*plate)==10||(*plate)==11||(*plate)==12){
		//*plate->
		isMotorcade=1;
	}else{
		//para->
		isMotorcade=0;
	}
	//isMotorcade=0;
	int sem_val;
	sem_getvalue(sem+from,&sem_val);
	if(sem_val!=0){
		if(isEmergency){
			printf("Emergency skips queue\n");
			skipQueue(queue+from,cars[*plate]);
		}
		else if(isMotorcade){
			printf("Motorcade skips queue\n");
			skipQueue(queue+from,cars[*plate]);
		}
		else{
			enQueue(queue+from,cars[*plate]);
		}
	}

	sem_post(sem+from);
	recorder[from]=to;
	int counter=0;
	while(to>0){ //if has not finished 
		printf("%d recorder: %d, %d, %d, %d\n",*plate,recorder[0],recorder[1],recorder[2],recorder[3]);
		getchar();
		next=(from+1)%4;
		step=to-1;
		printf("plate %d counter %d\n",*plate, counter);
		counter++;
		
		//deadlock situation check
		if(to>1){
			while(recorder[next]>1 && recorder[(from+2)%4]>1 && recorder[(from+3)%4]>1);
		}

		sem_wait(sem+from);//decrease the # of waiting vehicles of current region


		// //deadlock situation check
		// if(to>1){
		// 	while(recorder[next]>1 && recorder[(from+2)%4]>1 && recorder[(from+3)%4]>1);
		// }


		//sem_wait(mut+from);//lock critical region
		deQueue(queue+from);
		recorder[from]=to;
		if(isEmergency){
			printf("Emergency ");
		}
		if(isMotorcade){
			printf("Motorcade ");
		}
		printf("%d entering region %d\n",*plate,from);
		//while(mut+next!=1);
		if(to>1){
			skipToTwo(queue+next,cars[*plate]);//join the queue at the next region
			sem_post(sem+next);//increase of waiting vehicles number in the next region		
			while((*(queue+next)->head).info!=cars[*plate]);//until it's current vehicle's turn to proceed 
		}
		sem_post(mut+from);//unlock critical region	
		
		printf("%d leaving region %d\n",*plate,from);

		to=step;//change moving state
		from=next;//change current location
		//recorder[next]=step;//update recordings at interstections
		printf("plate%d now to is %d\n",*plate,to);
	}
}
}
//===================================================
