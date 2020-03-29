#include "randomizer.h"

Randomizer::Randomizer()
{
qsrand(QTime::currentTime().msec());
}

int Randomizer::GenerateRandom(int Min, int Max)
{


    return  ((rand()%(Max-Min+1))+Min);
}
