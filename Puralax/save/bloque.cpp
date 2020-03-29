#include "bloque.h"

Bloque::Bloque()
{
    Color = 0;
    Mov = 0;
}

void Bloque::SetBloque(int NewColor, int NewMov)
{
    Color = NewColor;
    Mov = NewMov;
}

int Bloque::GetColor()
{
    return Color;
}

int Bloque::GetMov()
{
    return Mov;
}

Bloque::~Bloque()
{

}
