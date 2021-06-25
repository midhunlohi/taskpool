#include "core.h"

extern work **workArray;

void taskInsertion(task *ptr, int taskId){    
    if(workArray[taskId] == NULL){
        workArray[taskId] = (work*)malloc(sizeof(work));
        workArray[taskId]->taskPtr = ptr;
        workArray[taskId]->next = NULL;
    }else{
        work *temp = workArray[taskId];        
        while(temp->next != NULL){
            temp = temp->next;
        }
        work *new = (work *)malloc(sizeof(work));
        new->taskPtr = ptr;
        new->next = NULL;
        temp->next = new;
    }
}

// void taskDeletion(){

// }