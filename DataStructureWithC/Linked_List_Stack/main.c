#include <stdio.h>
#include <stdlib.h>
#include "StackLinked.h"
int main()
{
    Stack s1;
    int Data;
    CreateStack(&s1);
    push(&s1,10);
    push(&s1,11);
    push(&s1,12);
    pop(&s1,&Data);
    printf("my data is %d",Data);
    pop(&s1,&Data);
    printf("my data is %d",Data);
    pop(&s1,&Data);
    printf("my data is %d",Data);
    if(pop(&s1,&Data)==EmptyStack)
    {
        printf("it is empty stack");
    }



    printf("Hello world!\n");
    return 0;
}
