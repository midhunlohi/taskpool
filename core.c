#include "core.h"

sem_t mutex[TASKS];
pthread_mutex_t lock;
int gTask;

task *headPtr = NULL;
//extern int gTask;
work **workArray = NULL;
extern int (*fPtrArray[])(int, int);

void sig_handler(int signum){
    // printf("Recevied signal is %d \n", signum);
    for(int i = 0 ; i < TASKS; i++){
        sem_post(&mutex[i]);
    }
}

void *scheduler(void *args){    
    // while(1){
    //     sleep(1);
    //     raise(SIGUSR1);
    // }
    task *temp = headPtr;
    int counter = 0;
    while(temp != NULL){
        int threadId = counter % TASKS;
        taskInsertion(temp, threadId);
        sem_post(&mutex[threadId]);
        temp = temp->next;
        counter ++;
    }    
    while(1);
}   

void *taskThreadFunc(void *args){
    int mutexId = *(int *)args;    
    while(1){
        sem_wait(&mutex[mutexId]);
        // printf("Starting the task %d \n", mutexId);        
        work *temp = workArray[mutexId];
        int val;
        while(temp != NULL){
            pthread_mutex_lock(&lock);                
            if( temp->taskPtr->status == TODO){                
                temp->taskPtr->status = DONE;
                val = temp->taskPtr->fPtr(temp->taskPtr->args[0], temp->taskPtr->args[1]);
                printf("Task - %d Output %d gTask %d\n", mutexId, val, gTask) ;
                gTask--;
                pthread_mutex_unlock(&lock);                                
                sem_wait(&mutex[mutexId]);
            }
            temp = temp->next;
            pthread_mutex_unlock(&lock);                
        }
    }
}

void initTasks(void){
    pthread_t main_thread, task_thread[TASKS];
    int tasks[TASKS]; 
    signal(SIGUSR1, sig_handler);
    workArray = ( work **)malloc( TASKS * sizeof(work));
    for( int i = 0 ; i < TASKS ; i ++){
        workArray[i] = NULL;
    }
    pthread_create(&main_thread, NULL, scheduler, NULL);
    for(int i = 0 ; i < TASKS; i++){
        tasks[i] = i;
        pthread_create(&task_thread[i], NULL, taskThreadFunc, &tasks[i]);
    }  
    pthread_join(main_thread, NULL);
}

void queueTasks(input *list, int len){
    gTask = len;
    for( int i = 0; i < len ; i++){
        task *new = (task *)malloc(sizeof(task));
        new->next = NULL;   
        new->fPtr = fPtrArray[list[i].opcode];     
        new->args[0] = list[i].args[0];
        new->args[1] = list[i].args[1];        
        new->status = TODO;
        if(headPtr == NULL){
            headPtr = new;        
        }
        else{
            task *temp = headPtr;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new;
        }                
    }
}