#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define SIZE 5
#define MAX_ITEMS 20

int buf[SIZE];
int f = -1, r = -1;
int produced = 0;
int consumed = 0;
sem_t mutex, full, empty, limit;
void* produce(void* arg){
    for(int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&limit);     // ensure producer doesn't exceed 10 extra items
        sem_wait(&empty);
        sem_wait(&mutex);

        r = (r + 1) % SIZE;
        buf[r] = i;
        produced++;
        printf("Produced: %d | Total Produced: %d\n", i, produced);
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);}
    return NULL;}
    
void* consume(void* arg){
    for(int i = 0; i < MAX_ITEMS; i++){
        sem_wait(&full);
        sem_wait(&mutex);

        f = (f + 1) % SIZE;
        int item = buf[f];
        consumed++;
        printf("Consumed: %d | Total Consumed: %d\n", item, consumed);
        sem_post(&mutex);
        sem_post(&empty);
        sem_post(&limit);   // allow producer to produce more
        sleep(1);}
    return NULL;}

int main(){
    pthread_t t1, t2;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, SIZE);
    sem_init(&limit, 0, 10);   // producer can be ahead by at most 10
    pthread_create(&t1, NULL, produce, NULL);
    pthread_create(&t2, NULL, consume, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&limit);
    return 0;}
