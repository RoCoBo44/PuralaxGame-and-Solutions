#include "pilatableros.h"

PilaTableros::PilaTableros()
{
    Cantidad=0;
    empty = true;


}

void PilaTableros::Agregar(int * Ta)
{
     Pila.push(Ta);

    empty = false;
    Cantidad++;
}

int *PilaTableros::Tope()
{
        return Pila.top();






}

void PilaTableros::SacarTope()
{
    if (Cantidad > 0){
        Cantidad--;
        int * Tab = Pila.pop();

        if (Cantidad == 0){
            empty = true;
        }
    }
}

int PilaTableros::GetCantidad()
{
    return Cantidad;
}

bool PilaTableros::IsEmpty()
{
    return empty;
}

PilaTableros::~PilaTableros()
{

}
