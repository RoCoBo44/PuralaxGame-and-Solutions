#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QSlider>



#include "marchivo.h"
#include "secondarywindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton * New;
    QLabel * Text;
    QVBoxLayout * Layout;
    QHBoxLayout * ContainerSlider;
    QPushButton * Continuar;
    QPushButton * RandomLevel;
    QSlider * Slider;

    Paleta Pal;

    SecondaryWindow SW;
    int NivelInicial;
    QString * Lugar;

    bool SBackTracking;

    void ActivarSecondaryWindow();
    void PreActivarSecondaryWindow();
    void ActivarRandomLevels();
    void CambiarBoolean();

};

#endif // MAINWINDOW_H
