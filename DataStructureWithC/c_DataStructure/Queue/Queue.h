#define MaxQueue 5

typedef struct
{
 int Arr[MaxQueue];
 int Start;
 int Last;

}Queue;
void Queue_init( Queue *PtrQueue);

typedef enum
{
    Queue_Empty,
    Queue_Full,
    Done
}Queue_States;
