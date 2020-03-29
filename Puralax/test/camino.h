#ifndef CAMINO_H
#define CAMINO_H
#include <QChar>

class Camino
{
public:
    Camino();
    void SetCamino(int x, int y, QChar Direccion);
    int GetX();
    int GetY();
    QChar GetDireccion();

private:

        int x;
        int y;
        QChar direccion;


};

#endif // CAMINO_H
