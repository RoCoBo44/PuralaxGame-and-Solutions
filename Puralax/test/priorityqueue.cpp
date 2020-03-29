#include "priorityqueue.h"

PriorityQueue::PriorityQueue()
{

}

void PriorityQueue::Add(int Key, Estado E)
{
    PQ.insert(Key,E);
}

Estado PriorityQueue::ExtractLowest()
{
    Estado Est = PQ.first();
    QMultiMap<int, Estado>::iterator i = PQ.begin();



    PQ.erase(i);


    return Est;
}

bool PriorityQueue::IsEmpty()
{
    return PQ.isEmpty();
}
