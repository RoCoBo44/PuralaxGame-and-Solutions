#include "paleta.h"

Paleta::Paleta()
{


    Colores = new QString[6];

    Colores[0]="rgb(229,229,229)";
    Colores[1]="rgb(154,151,255)";
    Colores[2]="rgb(232,144,124)";
    Colores[3]="rgb(222,193,255)";
    Colores[4]="rgb(144,214,159)";
    Colores[5]="rgb(225,217,142)";


}

QString Paleta::Color(int i)
{
    return Colores[i];
}

Paleta::~Paleta()
{
    delete[] Colores;
}

