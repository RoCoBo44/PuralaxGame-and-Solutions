#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRectF>


#include "panell.h"
#include "marchivo.h"
#include "randomizer.h"

namespace Ui {
class SecondaryWindow;
}

class SecondaryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget *parent = 0);

    void Iniciar(int Nivel, bool Random, bool BT); //Despues hacer que pase el marchivo
    void IniciarRandom();

    ~SecondaryWindow();


private:
    Ui::SecondaryWindow *ui;

    QLabel * Texto;
    QVBoxLayout * VLayout;
    QHBoxLayout * HLayout;
    QPushButton * Reset;
    QPushButton * Solve;

    Panell * Panel;

    int ColorFinal;
    Paleta Pal;
    bool EsRandom;
    bool BT;

    int NivelActual;
    int NivelMaximo;

    void CargarPanel(Panell *&Panel, QString Nivel);
    void SacarNumero(int & Pos, QString Linea, int & Num);

    void AumentarNivel();
    void ActualizarNivel();


};

#endif // SECONDARYWINDOW_H
