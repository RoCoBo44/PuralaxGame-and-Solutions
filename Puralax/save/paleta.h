#ifndef PALETA_H
#define PALETA_H
#include <QString>


class Paleta
{

public:

    Paleta();
    QString Color(int i);
    ~Paleta();

private:

    QString * Colores;
};

#endif // PALETA_H
