#ifndef PILATABLEROS_H
#define PILATABLEROS_H

#include "tablero.h"
#include <QStack>
#include <QList>
#include "estado.h"

class PilaTableros
{
public:
    PilaTableros();

    void Agregar(int * Ta);
    int * Tope();
    void SacarTope();
    int GetCantidad();
    bool IsEmpty();

    ~PilaTableros();

private:

    QStack<int *>  Pila;


    int Cantidad;
    bool empty;

};

#endif // PILATABLEROS_H
