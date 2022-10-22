#include "stack.h"



stack_status_t push(Stack *StPtr,int data)
{
    if(StPtr->sp<STACK_SIZE)
    {
        StPtr->StackArr[StPtr->sp]=data;
        StPtr->sp++;
        return DONE;
    }
    else
    {
        return STACK_FULL;
    }

}
stack_status_t Pop(Stack *StPtr,int *Ptr)
{
    if(StPtr->sp>0)
    {
            (StPtr->sp)--;
            *Ptr=StPtr->StackArr[StPtr->sp];
            return DONE;

    }
    else
        return STACK_EMPTY;
}

void stack_Init(Stack *StPtr)
{
     StPtr->sp=0;
}
