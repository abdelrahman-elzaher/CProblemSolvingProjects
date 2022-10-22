
#include "Queue.h"
void Queue_init( Queue *PtrQueue)
{
    PtrQueue->Start=0;
    PtrQueue->Last=0;


}
Queue_States InQueue(Queue *PtrQueue,int Data)
{
    if((PtrQueue->Last)-(PtrQueue->Start)>=MaxQueue)
        return Queue_Full;
    if((PtrQueue->Last)>=MaxQueue && (PtrQueue->Start)>=MaxQueue)
    {
        (PtrQueue->Last)=(PtrQueue->Last)-MaxQueue;
        (PtrQueue->Start)=(PtrQueue->Start)-MaxQueue;
    }
    if((PtrQueue->Last)>=2*MaxQueue)
        (PtrQueue->Last)=(PtrQueue->Last)-MaxQueue;
    if((PtrQueue->Last)>=MaxQueue)
    {
         PtrQueue->Arr[(PtrQueue->Last)%MaxQueue]=Data;
             (PtrQueue->Last)++;
    }
    else
    {
        PtrQueue->Arr[PtrQueue->Last]=Data;
        (PtrQueue->Last)++;
    }
    return Done;
}
Queue_States DeQueue(Queue *PtrQueue,int *Data)
{
    if((PtrQueue->Last)==(PtrQueue->Start))
    {
        PtrQueue->Start=0;
        PtrQueue->Last=0;

        return Queue_Empty;
    }
        if((PtrQueue->Start)>=MaxQueue &&(PtrQueue->Start)>=MaxQueue)
    {
        (PtrQueue->Last)=(PtrQueue->Last)-MaxQueue;
        (PtrQueue->Start)=(PtrQueue->Start)-MaxQueue;
    }
    if((PtrQueue->Start)>=2*MaxQueue)
        (PtrQueue->Start)=(PtrQueue->Start)-MaxQueue;
    if((PtrQueue->Start)>=MaxQueue)
    {
         *Data=PtrQueue->Arr[(PtrQueue->Start)%MaxQueue];
             (PtrQueue->Start)++;
    }
    else
    {
        *Data=PtrQueue->Arr[PtrQueue->Start];
        (PtrQueue->Start)++;
    }
    return Done;
}
