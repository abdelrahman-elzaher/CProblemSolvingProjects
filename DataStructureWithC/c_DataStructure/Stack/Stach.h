#define STACK_SIZE   5


typedef enum{
STACK_FULL,
STACK_EMPTY,
DONE
}stack_status_t;

typedef struct
{
    int StackArr[STACK_SIZE];
    int sp;
}Stack;
stack_status_t push(Stack *StPtr,int data);
void stack_Init(Stack *StPtr);
stack_status_t Pop(Stack *StPtr,int *Ptr);
