#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
int main()
{
    Queue q1;
    Queue_init(&q1);
    InQueue(&q1,5);
    InQueue(&q1,6);
    InQueue(&q1,7);
    InQueue(&q1,7);
    InQueue(&q1,7);
    if(InQueue(&q1,7)==Queue_Full)
        printf("Queue is full\n");

    int Data;
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    InQueue(&q1,3000);

    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);

    if(DeQueue(&q1,&Data)==Queue_Empty)
    {
        printf("Queue is empyy\n");
    }
    InQueue(&q1,200);
    InQueue(&q1,400);
    InQueue(&q1,600);
    InQueue(&q1,800);
    InQueue(&q1,900);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    InQueue(&q1,10000);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
        DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
        DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
        DeQueue(&q1,&Data);
    printf("q1 ---> %d\n",Data);
    if(DeQueue(&q1,&Data)==Queue_Empty)
    {
        printf("Queue is empyy\n");
    }
    return 0;
}
