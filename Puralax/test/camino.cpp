#include "camino.h"

Camino::Camino()
{

}

void Camino::SetCamino(int x, int y, QChar Direccion)
{
    this->x = x;
    this->y = y;
    this->direccion = Direccion;
}

int Camino::GetX()
{
    return x;
}

int Camino::GetY()
{
    return y;
}

QChar Camino::GetDireccion()
{
    return direccion;
}
