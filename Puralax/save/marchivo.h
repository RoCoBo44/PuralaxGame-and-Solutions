#ifndef MARCHIVO_H
#define MARCHIVO_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>


class MArchivo
{
public:
    MArchivo(QString nombre);
    QString TextLevel(int i);
    void Save(int i);
    int MaxMArchivo();
    int Level();
    ~MArchivo();


private:
    QString FileName;
    int Max;
    QString * Niveles;

    int CantidadLineas();



};

#endif // MARCHIVO_H
