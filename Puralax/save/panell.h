#ifndef PANELL_H
#define PANELL_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QThread>

#include <QList>
#include <QChar>

#include "tablero.h"
#include "paleta.h"

#include "priorityqueue.h"
#include "pilatableros.h"


namespace Ui {
class Panell;
}

class Panell : public QWidget
{
 Q_OBJECT

public:
    explicit Panell(int Max_X, int Max_Y, int * Arr, int ColorGanador,bool BT, QWidget *parent = 0 );
    void Reset();
    void Resolver();
    bool PoseeSolucion();
    ~Panell();

signals:
    void SignalWin ();

private:
    Ui::Panell *ui;

//    struct Dupla{ //Voy a tener que sacar
//        int x;
//        int y;
//    };



    //VISUAL
    QGridLayout * VisualBotones;
    QButtonGroup * Botones;
    Paleta Pal;


    //Manejo de informacion
    int MaxX;
    int MaxY;
    int ColorGan;
    bool PrimerClick; //para saber si esta en el primero o en el segundo click
    Tablero Ta;
    Estado::Dupla DatosPrimerClick; //para guardar los datos del primer click
    int * ReArr;






    void Accion(const int &n);
    void ResultadoTablero();

    Estado::Dupla VerLugar (int numero);
    bool EsHabilPrimerClick(Estado::Dupla Valores);
    bool EsHabilSegundoClick(Estado::Dupla SeCl, Estado::Dupla PrCl);
    bool EsAdy (Estado::Dupla PrCl, Estado::Dupla SeCl);

    void Pintar (Estado::Dupla SeCl, Estado::Dupla PrCl);

    void ModificarTablero(Estado::Dupla SeCl, Estado::Dupla PrCl);


    void PintarGrupo (const int & ColorBase, int PosX, int PosY, int ColorGrupo);
    void PosibleMoviento(const int & ColorBase, int PosX, int PosY, const int &ColorGrupo) ;
    bool EstaAdentro(const int & x, const int & y);

    void CargarVisual();
    void ActualizarVisual();

    bool Gano(); //todo lo que esta pintado es del color ganador
    bool Gano(Tablero Table); //Algo 2
    bool NoMasMovientos(); //No quedan mas movimientos

    void MostrarMatriz();
    void MostrarArr(int * Arr);

    /////////////////ALGO2/////////////////

//    struct Camino{
//        int x;
//        int y;
//        QChar direccion;
//    };

    QList<Estado::Camino> Solution;


    void BackTracking();
    int CantidadMovimientos();
    int CantidadMovimientosTotales();
    int CantidadColores();
    void CargarMovimientos(Estado::Dupla * Mov);

    void PrimeraEtapa(PilaTableros  & PTable, Estado::Dupla *Movimientos, QList<Estado::Camino> & LSolucion, int MaxArrMov, bool &Termino);
    void Mover(PilaTableros & PTable, Estado::Dupla *Movimientos, QList<Estado::Camino> & LSolucion, int MaxArrMov, bool &Termino, int i, int Mx, int My, QChar Dir);

    void MostrarSolucion(QList<Estado::Camino> LSolucion);

    bool HayMovColorGanador();
    bool Poda(Estado::Dupla * Movimientos, int MaxArrMov);
    bool HayConexion (Estado::Dupla * Movimientos, int MaxArrMov);
    void ExpandirMovimiento(int X, int Y, int Cantidad, int ColorGrupo);
    void ExpancionDeMovimientos(int X, int Y, int Cantidad, int ColorGrupo);

    int CantidadEntradas;

    void RePintar (Estado::Dupla * Movimientos, int MaxArrMov, Tablero &Aux);



    void RyP();
    QList<Estado> GenerateChildren (Estado e, int TamMov);
    void OneChild (QList<Estado> & ListaDeHijos, Estado e, int MovX, int MovY, char Dir, int i);

    int CantidadGrupos();
    void CargarPasadas(int x, int y, bool** Pasadas, int ColorG);

    void ResolverRecursion(int i);


};

#endif // PANELL_H
