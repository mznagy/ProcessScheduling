#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int processID = 0;
typedef struct Process
{
    int ID;
    int burst;
} Process;

typedef struct Queue
{
    Process* arr;
    int size;
    int front;
    int back;
} Queue;

void initializeQueue(Queue* queue)
{
    queue->arr = (Process*)malloc(SIZE * sizeof(Process));
    queue->size = 0;
    queue->front = 0;
    queue->back = -1;
}

int enqueue(Queue* queue, Process process)
{
    if(queue->size == SIZE)
    {
        return 0;
    }
    queue->back = (queue->back + 1) % SIZE;
    queue->arr[queue->back] = process;
    queue->size++;
    return 1;
}

Process dequeue(Queue* queue)
{
    if(queue->size == 0)
    {
        Process dummy = {-1, -1};
        return dummy;
    }
    Process temp = queue->arr[queue->front];
    queue->front = (queue->front + 1) % SIZE;
    queue->size--;
    return temp;
}

int isEmpty(Queue* queue)
{
    return queue->size == 0;
}

int isFull(Queue* queue)
{
    return queue->size == SIZE;
}

Process createProcess()
{
    Process newProcess;
    newProcess.ID = processID;
    processID++;
    newProcess.burst = rand() % 100 + 1;
    return newProcess;
}

int main()
{
    srand(time(NULL));

    Queue rr8;
    Queue rr16;
    Queue fcfs;

    initializeQueue(&rr8);
    initializeQueue(&rr16);
    initializeQueue(&fcfs);
    int count = 0;
    for(int i=0;i<5;i++){
        Process p = createProcess();
        count++;
        enqueue(&rr8,p);
    }
    while(!isEmpty(&rr8) || !isEmpty(&rr16) || !isEmpty(&fcfs) || count < 100)
    {
        int random = rand() % 100;

        if(count < 100)
        {
            Process p = createProcess();
            count++;
            enqueue(&rr8,p);
        }

        if(random < 50)
        {
            if(isEmpty(&rr8))
            {
                continue;
            }
            // processors works on the rr8
            Process current = dequeue(&rr8);
            if(current.burst <= 8)
            {
                printf("Process id = %d\n", current.ID);
            }
            else
            {
                current.burst -= 8;
                if(!isFull(&rr16))
                {
                    enqueue(&rr16, current);
                }
                else
                {
                    enqueue(&rr8, current);
                }
            }
        }
        else if(random < 80)
        {
            if(isEmpty(&rr16))
            {
                continue;
            }
            // processors works on the rr16
            Process current = dequeue(&rr16);
            if(current.burst <= 16)
            {
                printf("Process id = %d\n", current.ID);
            }
            else
            {
                current.burst -= 16;
                int random2 = rand() % 100;
                if(random2 < 50)
                {
                    enqueue(&rr16, current);
                }
                else
                {
                    if(!isFull(&fcfs))
                    {
                        enqueue(&fcfs, current);
                    }
                    else
                    {
                        enqueue(&rr16, current);
                    }

                }
            }
        }
        else
        {
            if(isEmpty(&fcfs))
            {
                continue;
            }
            // processors works on the fcfs
            Process current = dequeue(&fcfs);
            printf("Process id = %d\n", current.ID);
        }
    }

    return 0;
}