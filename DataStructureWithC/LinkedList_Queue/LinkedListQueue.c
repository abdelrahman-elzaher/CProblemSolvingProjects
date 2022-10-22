#include "QueueLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
void CreateQueue(Queue *Head)
{
    Head->Head=0;
}
void inQueue(Queue *Head,int Data)
{
    Node *Temp=malloc(sizeof(Node));
    Temp->Data=Data;
    Temp->Next=0;
    if(Head->Head==0)
    {
        Head->Head=Temp;
    }
    else
    {
        Node *Count;
        Count=Head->Head;
        while(Count->Next!=0)
            Count=Count->Next;
        Count->Next=Temp;
    }
}

States DeQueue(Queue *Head,int *Data)
{

    if(Head->Head==0)
        return EmptyQueue;
    else
    {
        Node *Temp=Head->Head;
        *Data=Head->Head->Data;
        Head->Head=Head->Head->Next;
        free(Temp);
        return Done;

    }

}

