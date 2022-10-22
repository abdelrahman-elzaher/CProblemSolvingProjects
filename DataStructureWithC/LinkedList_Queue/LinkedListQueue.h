typedef struct Nodes
{
    int Data;
    struct Nodes *Next;
}Node;
typedef struct
{
    Node *Head;
}Queue;
typedef enum Staues
{
    EmptyQueue,
    Done
}States;
void CreateQueue(Queue *Head);
void inQueue(Queue *Head,int Data);
States DeQueue(Queue *Head,int *Data);

