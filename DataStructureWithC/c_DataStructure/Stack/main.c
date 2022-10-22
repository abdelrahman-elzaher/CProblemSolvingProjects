#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
int main()
{
    int Data;
    Stack s1,s2;
    stack_Init(&s1);
    stack_Init(&s2);
    push(&s1,5);
    push(&s1,6);
    push(&s1,7);
    Pop(&s1,&Data);
    printf("s1   %d\n",Data);
    Pop(&s1,&Data);
    printf("s1    %d\n",Data);
    push(&s2,10);
    push(&s2,12);
    push(&s2,50);
    Pop(&s2,&Data);
    printf("s2    %d\n",Data);
    Pop(&s2,&Data);
    printf("s2   %d\n",Data);
    printf("Hello world!\n");
    return 0;
}
