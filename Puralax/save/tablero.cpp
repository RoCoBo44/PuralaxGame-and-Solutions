#include "tablero.h"

Tablero::Tablero()
{
    //Para que pueda ser dinamica
    Mat = NULL;
    PoseeTam = false;
}

Tablero::Tablero(int Max_X, int Max_Y)
{
    PoseeTam =true;
    this->CreateTablero(Max_X,Max_Y);
}

void Tablero::CreateTablero(int Max_X, int Max_Y)
{
    PoseeTam = true;
    this->MaxX=Max_X;
    this->MaxY=Max_Y;

    Mat = new Bloque*[MaxX];
    for (int k = 0 ;k < MaxX ;k++){
        Mat[k]= new Bloque[MaxY];
    }

  //  qDebug() << MaxX << "                       " << MaxY ;

}

void Tablero::LoadTablero(int * Arr)
{
  int i =0;
  int j =0;
  int k= 0;

  while (i < MaxX) {
     while (j < MaxY) {

       if (k <= (2*MaxX*MaxY-1)){
         Mat[i][j].SetBloque(Arr[k],Arr[k+1]);
       }

       j++;
       k+=2;

       }

     j=0;
     i++;

    }
}

void Tablero::SetTaBloque(int x, int y, Bloque Blo)
{
    if ((0 <= x) && (0 <= y) && (x < MaxX) && (y < MaxY)){
        Mat[x][y].SetBloque(Blo.GetColor(),Blo.GetMov());
    }

}

void Tablero::SetTaBloque(int x, int y, int Color, int Mov)
{
    if ((0 <= x) && (0 <= y) && (x < MaxX) && (y < MaxY)){
        Mat[x][y].SetBloque(Color,Mov);
    }

}

Bloque Tablero::GetBloque(int x, int y)
{
    Bloque NewBloque;
    NewBloque.SetBloque(Mat[x][y].GetColor(),Mat[x][y].GetMov());
    return NewBloque;
}

void Tablero::operator =(Tablero &OtroTa)
{
//    qDebug() << OtroTa.GetMaxX() << "(Del igual otrota)" << OtroTa.GetMaxY() ;
////    if (((MaxX != OtroTa.GetMaxX()) || (MaxY != OtroTa.GetMaxY())) ){


////        qDebug() << 4.61;



////        qDebug() << 4.62;
////        if (Mat != NULL){
////            delete [] Mat;
////            Mat = NULL;
////        }

////        qDebug() << 4.63;

////        Mat = new Bloque*[OtroTa.GetMaxX()];
////        for (int k = 0 ;k < OtroTa.GetMaxX() ;k++){
////            Mat[k]= new Bloque[OtroTa.GetMaxY()];
////        }


////        qDebug() << 4.64;
////        MaxX = OtroTa.GetMaxX();
////        MaxY = OtroTa.GetMaxY();

////    }



//    qDebug() << MaxX << " " << MaxY ;
//    if ((MaxX == OtroTa.GetMaxX()) && (MaxY == OtroTa.GetMaxY())){

//        for (int i=0; i< MaxX; i++){
//            for (int j=0; j< MaxY; j++ ){
//                Mat[i][j].SetBloque(OtroTa.GetBloque(i,j).GetColor(),OtroTa.GetBloque(i,j).GetMov());

//            }
//         }
//    }else{
//        qDebug() << "ERROR TAMAÑO";


//    }



}

int *Tablero::ArregloTablero()
{
    int * ArrTa;
    ArrTa = new int [2*MaxX*MaxY];
    int k=0;

    for (int i=0; i < MaxX ; i++){
        for(int j=0 ; j< MaxY ; j++){

           ArrTa[k] = Mat[i][j].GetColor();
           ArrTa[k+1] = Mat[i][j].GetMov();
           k+=2;
        }
    }

    return ArrTa;

}

int Tablero::GetMaxX()
{
    return MaxX;


}

int Tablero::GetMaxY()
{
    return MaxY;
}

bool Tablero::EstaCargadoElTam()
{
    return PoseeTam;
}


Tablero::~Tablero()
{

    if (Mat != NULL){
        delete [] Mat;
    }

}
