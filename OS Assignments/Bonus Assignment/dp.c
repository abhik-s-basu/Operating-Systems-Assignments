#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <stdlib.h> 
#include <unistd.h>  
#include <pthread.h> 
#include <semaphore.h> 


sem_t room; // counting semaphore for checking the number of people at table at a time. max 4 possible
sem_t forks[5]; // basically 5 forks acting as semaphores,each acts as a binary semaphores


int state[5];
int numbering[5]={0,1,2,3,4};
int mealsHad[5];
// 0 is thinking and 1 is eaten;

void useforks (int num){
	if(state[num] == 0){
		sem_wait(&room);
		printf("Philosopher %d has entered room \n",num+1);
		sem_wait(&forks[(num+1)%5]);
		sem_wait(&forks[num]);
		state[num] = 1;
		mealsHad[num] += 1;
		//incrementing the total meals had
		//converting all parameters to the eat state 	
		printf("Philosopher %d is eating his meal number %d with forks %d and %d \n",num+1,mealsHad[num],(num+1)%5,num);
	}
	
}

void putDownforks (int num){
	if(state[num] == 1){
		state[num]=0;
		sem_post(&forks[(num+1)%5]);
		sem_post(&forks[num]);
		sem_post(&room);
		//reset all parameters to their initial condition/think states
		printf("Philosopher %d is done with his meal \n",num+1);
	}
}

void think(){
	sleep(1);//represent real world state of thinking of a given philosopher
}

void eat(){
	sleep(2);// just a delay of 2 second to show it takes some time to eat
}

void *philosopher_dining (void *args){
	int *philo_num = (int *) args;
	while(1){
		if(mealsHad[*philo_num]>=10000){
			break;//breaking condition, can have an infinite loop as well won't make much of a difference.
		}
		//each philosopher will initally be in
		// a) think state: where he is thinking
		// b) useForks: they then picks the two forks on his side only and no place else
		// c) eat state: they then eat using the two forks 
		// d) putDownForks: after eating they put down the forks so that they can eat again later
		think();
		useforks(*philo_num);
		eat();
		putDownforks(*philo_num);
	}
}

int main(void){
	pthread_t philo [5];
	for(int i=0;i<5;i++){
		state[i]=0;
		// forks[i] = 0;
		mealsHad[i] = 0;
	}

	
	sem_init (&forks[0],0,1);
	sem_init (&forks[1],0,1);
	sem_init (&forks[2],0,1);
	sem_init (&forks[3],0,1);
	sem_init (&forks[4],0,1);
	sem_init (&room,0,4);

	for(int i=0;i<5;i++){
		pthread_create(&philo[i],NULL,philosopher_dining,&numbering[i]);//creation of 5 threads in order to allow the philosophers to start eating
		//sleep(2);
		printf("Philosopher %d is thinking. \n",i+1);
	}

	for(int i=0;i<5;i++){
		pthread_join(philo[i],NULL);//exit condition is each philosopher having 100 meals
	}

	for (int i=0;i<5;i++){
		printf("Philosopher %d had %d meals \n",i+1,mealsHad[i]);
	}

}


