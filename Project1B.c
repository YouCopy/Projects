#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    int front;
    int rear;
    int size;
    unsigned capacity;
    int* array;

    int first;
    int last;
    int* time;

    int job_front;
    int job_rear;
    int* type;
};

struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;

    queue->front = queue->size = 0;
    queue->first = queue->size = 0;
    queue->job_front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->last = capacity - 1;
    queue->job_rear = capacity - 1;

    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    queue->time = (int*)malloc(queue->capacity * sizeof(int));
    queue->type = (int*)malloc(queue->capacity * sizeof(int));

    return queue;
}

int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

void push(struct Queue* queue, int item, int time, int type)
{
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->last = (queue->last + 1) % queue->capacity;
    queue->job_rear = (queue->job_rear + 1) % queue->capacity;

    queue->array[queue->rear] = item;
    queue->time[queue->last] = time;
    queue->type[queue->job_rear] = type;

    queue->size = queue->size + 1;
}

struct Queue* pop(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        return (struct Queue*)-2147483648;
    }
    struct Queue* popped = queue;

    int item = popped->array[popped->front];
    popped->front = (popped->front + 1)% 1000;

    int time = popped->time[popped->first];
    popped->first = (popped->first + 1)% 1000;

    int type = popped->type[popped->job_front];
    popped->job_front = (popped->job_front + 1)% 1000;

    popped->size = popped->size - 1;

    return popped;
}

void sort(struct Queue* queue)
{
    int i;
    int j;
    for(i = 0; i < queue->size - 1; i++)
    {
        for(j = 0; j < queue->size - i - 1; j++)
        {
            if(queue->time[j] > queue->time[j+1])
            {
                int temp = queue->time[j];
                queue->time[j] = queue->time[j+1];
                queue->time[j+1] = temp;

                int temp2 = queue->array[j];
                queue->array[j] = queue->array[j+1];
                queue->array[j+1] = temp2;

                int temp3 = queue->type[j];
                queue->type[j] = queue->type[j+1];
                queue->type[j+1] = temp3;
            }
        }
    }
    queue->front=queue->array[0];
    queue->first=queue->time[0];
    queue->job_front=queue->type[0];

    queue->rear = queue->array[queue->size];
    queue->last = queue->time[queue->size];
    queue->job_rear = queue->type[queue->size];


}

int front(struct Queue* queue)
{
    if (isEmpty(queue))
    {
        return -2147483648;
    }
    return queue->array[queue->front];
}

int rear(struct Queue* queue)
{
    if (isEmpty(queue))
    {
        return -2147483648;
    }
    return queue->array[queue->rear];
}
int random_number(int max, int min)
{
    return rand() % (max + 1 - min) + min;
}

void print(struct Queue* queue)
{
    int i;
    for(i = 0; i < queue->size; i++)
    {
        switch(queue->type[i])
        {
            case 0:
                printf("%d  Job%d arrived at CPU\n", queue->time[i], queue->array[i]);
                break;
            case 1:
                printf("%d  Job%d finished at CPU\n", queue->time[i], queue->array[i]);
                break;
            case 2:
                printf("%d  Job%d arrived at Disk1\n", queue->time[i], queue->array[i]);
                break;
            case 3:
                printf("%d  Job%d finished at Disk1\n", queue->time[i], queue->array[i]);
                break;
            case 4:
                printf("%d  Job%d arrived at Disk2\n", queue->time[i], queue->array[i]);
                break;
            case 5:
                printf("%d  Job%d finished at Disk2\n", queue->time[i], queue->array[i]);
                break;
            case 6:
                printf("%d  Job%d arrived at Network\n", queue->time[i], queue->array[i]);
                break;
            case 7:
                printf("%d  Job%d finished at Network\n", queue->time[i], queue->array[i]);
                break;
            case 8:
                printf("%d  Job%d finished\n", queue->time[i], queue->array[i]);
                break;
            case 9:
                printf("%d  Simulation over\n", queue->time[i]);
                break;
        }
    }
}

void write_log(struct Queue* queue, int* config)
{
    FILE* fp = fopen("log.txt", "w");
    if(fp == NULL)
    {
        printf("Cannot open file \n");
        exit(1);
    }
    fseek(fp, 0L, SEEK_SET);

    fprintf(fp, "SEED: %d\nINIT_TIME: %d\nFIN_TIME: %d\nARRIVE_MIN: %d\nARRIVE_MAX: %d\nQUIT_PROB: %d\nNETWORK_PROB: %d\nCPU_MIN: %d\nCPU_MAX: %d\nDISK1_MIN: %d\nDISK1_MAX: %d\nDISK2_MIN: %d\nDISK2_MAX: %d\nNETWORK_MIN: %d\nNETWORK_MAX: %d\n\n", config[0], config[1], config[2], config[3], config[4], config[5], config[6], config[7], config[8], config[9], config[10], config[11], config[12], config[13], config[14]);
    int i;
    for(i = 0; i < queue->size; i++)
    {
        switch(queue->type[i])
        {
            case 0:
                fprintf(fp, "%d  Job%d arrived at CPU\n", queue->time[i], queue->array[i]);
                break;
            case 1:
                fprintf(fp, "%d  Job%d finished at CPU\n", queue->time[i], queue->array[i]);
                break;
            case 2:
                fprintf(fp, "%d  Job%d arrived at Disk1\n", queue->time[i], queue->array[i]);
                break;
            case 3:
                fprintf(fp, "%d  Job%d finished at Disk1\n", queue->time[i], queue->array[i]);
                break;
            case 4:
                fprintf(fp, "%d  Job%d arrived at Disk2\n", queue->time[i], queue->array[i]);
                break;
            case 5:
                fprintf(fp, "%d  Job%d finished at Disk2\n", queue->time[i], queue->array[i]);
                break;
            case 6:
                fprintf(fp, "%d  Job%d arrived at Network\n", queue->time[i], queue->array[i]);
                break;
            case 7:
                fprintf(fp, "%d  Job%d finished at Network\n", queue->time[i], queue->array[i]);
                break;
            case 8:
                fprintf(fp, "%d  Job%d finished\n", queue->time[i], queue->array[i]);
                break;
            case 9:
                fprintf(fp, "%d  Simulation over\n", queue->time[i]);
                break;
        }
    }
    fclose(fp);
}

void print_stats(struct Queue* queue)
{
    FILE* fp = fopen("statistics.txt", "w");
    if(fp == NULL)
    {
        printf("Cannot open file \n");
        exit(1);
    }
    fseek(fp, 0L, SEEK_SET);
    fprintf(fp, "Average size of CPU: \n");
    fprintf(fp, "Max size of CPU: \n");

    fprintf(fp, "Average size of Disk1: \n");
    fprintf(fp, "Max size of Disk1: \n");

    fprintf(fp, "Average size of Disk2: \n");
    fprintf(fp, "Max size of Disk2: \n");

    fprintf(fp, "Average size of Network: \n");
    fprintf(fp, "Max size of Network: \n");

    fprintf(fp, "Total utilization of CPU: \n");
    fprintf(fp, "Total utilization of Disk1: \n");
    fprintf(fp, "Total utilization of Disk2: \n");
    fprintf(fp, "Total utilization of Network: \n");

    fprintf(fp, "Average response time of CPU: \n");
    fprintf(fp, "Max response time of CPU: \n");

    fprintf(fp, "Average response time of Disk1: \n");
    fprintf(fp, "Max response time of Disk1: \n");

    fprintf(fp, "Average response time of Disk2: \n");
    fprintf(fp, "Max response time of Disk2: \n");

    fprintf(fp, "Average response time of Network: \n");
    fprintf(fp, "Max response time of Network: \n");

    fprintf(fp, "CPU throughput: \n");
    fprintf(fp, "Disk1 throughput: \n");
    fprintf(fp, "Disk2 throughput: \n");
    fprintf(fp, "Network throughput: \n");
    fclose(fp);
}

int main()
{
    FILE* fp = fopen("config.txt", "r");
    if(fp == NULL)
    {
        printf("Cannot open file \n");
        exit(1);
    }
    int n = 0, i = 0;
    int* config = malloc(sizeof(int)*15);

    while(fscanf(fp, "%d\n", &n) > 0)
    {
        config[i++] = n;
    }
    fclose(fp);
    config[i++] = '\0';

    struct Queue* cpu = createQueue(10000);
    struct Queue* disk1 = createQueue(10000);
    struct Queue* disk2 = createQueue(10000);
    struct Queue* network = createQueue(10000);

    struct Queue* pqueue = createQueue(10000);

    srand(config[0]);
    push(pqueue, -1, config[2], 9);

    int time = config[1];
    push(cpu, 1, time, 0);
    push(pqueue, 1, time, 0);

    int item = 2;

    while(pqueue->size != 0 && time < config[2])
    {
        printf("%d\n", item);
        int number = rand() % 100 + 1;
        if(number <= config[5])
        {

            push(pqueue, cpu->array[cpu->front], time, 8);
            cpu = pop(cpu);
        }
        time = cpu->time[cpu->front];
        time += random_number(config[4], config[3]);

        push(cpu, item, time, 0);

        push(pqueue, item, time, 0);
        item++;

        push(pqueue, cpu->array[cpu->front], cpu->time[cpu->front]+ random_number(config[8], config[7]), 1);

        number = rand() % 100 + 1;
        if(number <= config[6])
        {
            time+= random_number(config[14], config[13]);

            push(network, cpu->array[cpu->front], time, 6);
            push(pqueue, cpu->front+1, time, 6);
        }
        else if(random_number(1,4) % 2 == 0)
        {
            time+= random_number(config[10], config[9]);

            push(disk1, cpu->array[cpu->front], time, 2);
            push(pqueue, cpu->front+1, time,  2);
        }
        else
        {
            time+= random_number(config[12], config[11]);

            push(disk2, cpu->array[cpu->front], time, 4);
            push(pqueue, cpu->front+1, time, 4);

        }
        time+= random_number(config[4], config[3]);
        push(cpu, cpu->array[cpu->front], time, 4);
        cpu = pop(cpu);
    }
    sort(pqueue);

    print(pqueue);
    write_log(pqueue, config);
    print_stats(pqueue);
    return 0;
}
