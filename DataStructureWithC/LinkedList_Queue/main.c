#include <stdio.h>
#include <stdlib.h>
#include "QueueLinkedList.h"
int main()
{
    Queue q1;
    int Data;
    CreateQueue(&q1);
    inQueue(&q1,10);
    inQueue(&q1,11);
    inQueue(&q1,12);
    DeQueue(&q1,&Data);
    printf("my data is %d\n",Data);
    DeQueue(&q1,&Data);

    printf("my data is %d\n",Data);
    DeQueue(&q1,&Data);

    printf("my data is %d\n",Data);
    if(DeQueue(&q1,&Data)==EmptyQueue)
    {
        printf("it is empty Queue");
    }



    printf("Hello world!\n");
    return 0;
}
