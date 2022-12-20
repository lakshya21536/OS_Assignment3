#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *func(int n);
void eat(int);
void thinking(int);
void finished(int);

pthread_t phil[5];
pthread_mutex_t chopstick[5];

int main()
{
int i,k;
void *msg;
for(i=0;i<5;i++)
{
k=pthread_mutex_init(&chopstick[i],NULL);
}
for(i=0;i<5;i++)
{
k=pthread_create(&phil[i],NULL,(void *)func,(int *)i);
}
for(i=0;i<5;i++)
{
k=pthread_join(phil[i],&msg);
}
for(i=0;i<5;i++)
{
k=pthread_mutex_destroy(&chopstick[i]);
}
return 0;
}

void *func(int n)
{
while(1){
    thinking(n);
    pthread_mutex_lock(&chopstick[n]);
    pthread_mutex_lock(&chopstick[(n+1)%5]);
    eat(n);
    sleep(3);
    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[(n+1)%5]);
    finished(n);
}
}

void eat(int phil)
{
	printf("Philosopher %d is eating\n",phil);
}

void thinking(int phil){
    printf("Philosopher %d is thinking\n",phil);
}

void finished(int phil){
    printf("Philosopher %d has finished eating\n",phil);
}