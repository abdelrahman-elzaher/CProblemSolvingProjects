typedef struct Nodes
{
    int Data;
    struct Nodes *Next;
}Node;
typedef struct
{
    Node *Head;
}Stack;
typedef enum Staues
{
    EmptyStack,
    Done
}States;
void CreateStack(Stack *Head);
void push(Stack *Head,int Data);
States pop(Stack *Head,int *Data);
