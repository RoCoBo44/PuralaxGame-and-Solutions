#ifndef TABLERO_H
#define TABLERO_H

#include "bloque.h"
#include <QDebug>


class Tablero
{
public:

    Tablero();
    Tablero(int Max_X, int Max_Y);
    void CreateTablero(int Max_X, int Max_Y);
    void LoadTablero(int * Arr);
    void SetTaBloque(int x, int y, Bloque Blo);
    void SetTaBloque(int x, int y, int Color, int Mov);
    Bloque GetBloque(int x, int y);
    void operator = (Tablero & OtroTa);

    ///////////////////
    int * ArregloTablero();

    int GetMaxX();
    int GetMaxY();

    bool EstaCargadoElTam ();



    ~Tablero();

private:

    Bloque ** Mat;
    int MaxX;
    int MaxY;
    bool PoseeTam;

};

#endif // TABLERO_H
