#include "estado.h"


Estado::Estado(Tablero & Tab, Dupla *Mov,int Tam, QList<Camino> Sol)
{
    Table = Tab.ArregloTablero();
    Movimientos = Mov;
    Solucion = Sol;
    this->Tam = Tam;
}


int *Estado::GetTablero()
{
    return Table;
}

Estado::Dupla *Estado::GetMovimientos()
{
    Dupla * Copia = new Dupla [Tam];
    for (int i = 0; i < Tam; i++){
        Copia[i].x = Movimientos[i].x;
        Copia[i].y = Movimientos[i].y;
    }


    return Copia;
}






QList<Estado::Camino> Estado::GetSolucion()
{
    return Solucion;
}

int Estado::GetTam()
{
    return Tam;
}




