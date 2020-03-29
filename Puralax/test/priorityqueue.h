#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <QMultiMap>
#include <QString>
#include <QList>

#include "estado.h"


class PriorityQueue
{
public:
    PriorityQueue();
    void Add(int Key, Estado E);
    Estado ExtractLowest();
    bool IsEmpty();

private:

    QMultiMap <int, Estado> PQ;


};

#endif // PRIORITYQUEUE_H
