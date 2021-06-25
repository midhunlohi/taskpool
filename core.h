#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>

#define TASKS 10
enum Operation{ADD = 0, SUB, MUL, DIV};
enum Status{TODO = 0, INPROGRESS, DONE};

sem_t mutex[TASKS];
pthread_mutex_t lock;
int gTask;

typedef struct task_t{
    int taskId;
    int (*fPtr)(int, int);
    int args[2];
    int status;
    int output;
    struct task_t *next;
}task;

typedef struct input_t{
    int args[2];
    enum Operation opcode;
}input;

typedef struct work_t{
    struct task_t *taskPtr;
    struct work_t *next;
}work;

int add(int var1, int var2);
int sub(int var1, int var2);
int mul(int var1, int var2);
int divide(int var1, int var2);
void sig_handler(int signum);
void *scheduler(void *args);
void *taskThreadFunc(void *args);
void initTasks(void);
void queueTasks(input *list, int len);
void registerWorkQueue(int );
void taskInsertion(task *ptr, int taskId);
