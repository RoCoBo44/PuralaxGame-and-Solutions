#ifndef ESTADO_H
#define ESTADO_H



#include <QList>
//#include "camino.h"
//#include "duplaC.h"
#include "tablero.h"

class Estado
{
public:
    //PREGUNTAR SOBRE ESTO
    struct Camino{

        int x;
        int y;
        QChar direccion;

    };

    struct Dupla{
        int x;
        int y;
    };

    Estado(Tablero &Tab, Dupla* Mov, int Tam, QList<Camino> Sol);


    int *GetTablero();
    Dupla *GetMovimientos();
    QList <Camino> GetSolucion();
    int GetTam();





private:


        int Tam;
        int * Table;
        Dupla * Movimientos;
        QList <Camino> Solucion; //Podria crear una clase solucion la cual se encarga de guardar estos valores






};

#endif // ESTADO_H
