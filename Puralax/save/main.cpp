#include "mainwindow.h"
#include <QApplication>
#include "panell.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int MaxX = 2;
    int MaxY = 2;
    int * Arr = new int [MaxX*MaxY*2];

    Arr[0] = 1;
    Arr[1] = 3;
    Arr[2] = 0;
    Arr[3] = 0;
    Arr[4] = 2;
    Arr[5] = 1;
    Arr[6] = 2;
    Arr[7] = 0;


    //Panell wa(MaxX,MaxY,Arr,1) ;
    MainWindow wa;
    //SecondaryWindow wa;

    //wa.Iniciar(1);
    wa.showNormal();
    //wa.show();




    delete[] Arr;

    return a.exec();
}
