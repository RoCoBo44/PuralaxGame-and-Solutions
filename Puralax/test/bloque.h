#ifndef BLOQUE_H
#define BLOQUE_H


class Bloque
{
public:

    Bloque();
    void SetBloque(int NewColor, int NewMov);
    int GetColor();
    int GetMov();
    ~Bloque();

private:

    int Color;
    int Mov;
};

#endif // BLOQUE_H
