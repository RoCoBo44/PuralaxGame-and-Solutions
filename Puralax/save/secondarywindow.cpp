#include "secondarywindow.h"
#include "ui_secondarywindow.h"

SecondaryWindow::SecondaryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondaryWindow)
{
   // ui->setupUi(this);
}

void SecondaryWindow::Iniciar(int Nivel, bool Random, bool BT)
{
    NivelActual = Nivel;
    EsRandom = Random;
    this->BT = BT;

    Texto = new QLabel;
    Texto->setText("Nivel "+QString::number(Nivel));
    Texto->setAlignment(Qt::AlignCenter);
   // Cuadrado = new QRectF(0,0,200,200);
   // Cuadrado->setTop(0);

    Reset = new QPushButton("Reset");
    Solve = new QPushButton("Solution");

    if (!EsRandom){
        MArchivo Archi("C://Archivo.txt");
        NivelMaximo = Archi.MaxMArchivo() -1 ; //porque el primero guarda donde esta el nivel
        QString SLevel = Archi.TextLevel(NivelActual);
        CargarPanel(Panel,SLevel);
    }else{
        NivelMaximo = INT_MAX;
        IniciarRandom();
    }


    Solve->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(ColorFinal) + ";border-style: outset;font-size: 18pt;");
    Reset->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(ColorFinal) + ";border-style: outset;font-size: 18pt;");
    Texto->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(ColorFinal) + ";border-style: outset;font-size: 18pt;");


    HLayout = new QHBoxLayout;
    HLayout->addWidget(Texto);
    HLayout->addWidget(Reset);
    HLayout->addWidget(Solve);

    VLayout = new QVBoxLayout;
    VLayout->addLayout(HLayout);

    Panel->show();
    VLayout->addWidget(Panel);
    VLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(VLayout);

    connect(Solve,&QPushButton::clicked,Panel,&Panell::Resolver);
    connect(Reset,&QPushButton::clicked,Panel,&Panell::Reset);
    connect(Panel,&Panell::SignalWin,this,&SecondaryWindow::AumentarNivel);


}

void SecondaryWindow::IniciarRandom()
{
    QMap<int,int> Colores;
    Randomizer R;
    int MaxX = R.GenerateRandom(2,5);
    int MaxY = R.GenerateRandom(2,5);

    int * Arr = new int[MaxX*MaxY*2];

    if (MaxX + MaxY < 10){
        for (int i = 0 ;  i < MaxX*MaxY*2 ; i++){
                if (i % 2 == 0){ //Es el Color
                        int Posibilidad = R.GenerateRandom(0,10);
                        if (Posibilidad < 6){ // Es blanco el color entonces no tiene movimientos
                            Arr[i] = 0;
                            i++;
                            Arr[i] = 0;
                        }else{
                            int Valor = R.GenerateRandom(1,5);
                            Arr[i] =Valor;
                            if (!Colores.contains(Valor)){ //Para saber que colores tengo
                               Colores.insert(Valor,Valor);
                            }
                        }
                }else{ //Movimientos

                        int Posibilidad = R.GenerateRandom(0,10);
                        if (Posibilidad < 6){ //No mueve
                            Arr[i] = 0;
                        }else{
                            Arr[i] = R.GenerateRandom(1,(qMax(MaxX,MaxY))-1);
                    }
                }
        }
        if (Colores.size() > 1){

              QList<int> ListColores = Colores.values();
              ColorFinal = ListColores[R.GenerateRandom(0,Colores.size()-1)];
              Panel = new Panell(MaxX,MaxY,Arr,ColorFinal,BT);

              if (!Panel->PoseeSolucion()){
                  delete[] Panel;
                  this->IniciarRandom();
              }

        }else{
            this->IniciarRandom();
        }

    }else{
        this->IniciarRandom();
    }
}

SecondaryWindow::~SecondaryWindow()
{
    if (!Panel){
         delete[] Panel;
    }

    delete ui;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SecondaryWindow::CargarPanel(Panell *&Panel, QString Nivel)
{
    //ColorGanado , MaxX ,MaxY - ...arreglo

    int ColorGanador = 0;
    int Pos = 0;

    SacarNumero(Pos,Nivel,ColorGanador);
    ColorFinal = ColorGanador;


    int MaxX = 0;
    Pos++;


    SacarNumero(Pos,Nivel,MaxX);

    int MaxY = 0;
    Pos++;

    SacarNumero(Pos,Nivel,MaxY);

    Pos++;

    int * Arr = new int[MaxX*MaxY*2];

    int Valor;
    int i = 0;
    while (i < MaxX*MaxY*2) {

        Valor = 0 ;
        SacarNumero(Pos,Nivel,Valor);
        Arr[i]=Valor;
        Pos++;
        i++;

    }

   Panel = new Panell(MaxX,MaxY,Arr,ColorGanador,BT);



}

void SecondaryWindow::SacarNumero(int &Pos, QString Linea, int &Num)
{



        while ((Pos < Linea.size()) && (Linea[Pos] != ",") && (Linea[Pos] != "-"))
        {
            Num = Num*10 + Linea[Pos].digitValue();
               //Num = Num*10+ Linea[Pos].unicode() ;
                Pos++;
        }



}

void SecondaryWindow::AumentarNivel()
{
    if (NivelActual+1 <= NivelMaximo){
        QThread Tiempo;
        QApplication::processEvents();
        Tiempo.sleep(1);
        NivelActual++;
        this->ActualizarNivel();
    }
}

void SecondaryWindow::ActualizarNivel()
{
    if (!EsRandom){
        MArchivo Archi("C://Archivo.txt");
        QString SLevel = Archi.TextLevel(NivelActual);
        Archi.Save(NivelActual);
        delete[] Panel; //para que no sobre info
        CargarPanel(Panel,SLevel);
    }else{
        delete[] Panel;
        IniciarRandom();
    }






    VLayout->addWidget(Panel);
    connect(Reset,&QPushButton::clicked,Panel,&Panell::Reset);
    connect(Panel,&Panell::SignalWin,this,&SecondaryWindow::AumentarNivel);
    connect(Solve,&QPushButton::clicked,Panel,&Panell::Resolver);

    Texto->setText("Nivel "+QString::number(NivelActual));
    Reset->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(ColorFinal) + ";border-style: outset;font-size: 18pt;");
    Solve->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(ColorFinal) + ";border-style: outset;font-size: 18pt;");
    Texto->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(ColorFinal) + ";border-style: outset;font-size: 18pt;");

    this->adjustSize();



}
