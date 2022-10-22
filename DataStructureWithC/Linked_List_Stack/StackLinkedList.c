#include "StackLinked.h"
#include <stdio.h>
#include <stdlib.h>
void CreateStack(Stack *Head)
{
    Head->Head=0;
}
void push(Stack *Head,int Data)
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
        Head->Head=Temp;
        Temp->Next=Count;
    }

}

States pop(Stack *Head,int *Data)
{

    if(Head->Head==0)
        return EmptyStack;
    else
    {
        Node *Temp=Head->Head;
        *Data=Head->Head->Data;
        Head->Head=Head->Head->Next;
        free(Temp);
                return Done;

    }

}
