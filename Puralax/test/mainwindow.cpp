#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);


    MArchivo Archi("C://Archivo.txt");
    int i = Archi.Level();


    New = new QPushButton("Play");
    Text = new QLabel("Puralax");
    Layout = new QVBoxLayout ;
    ContainerSlider = new QHBoxLayout;
    RandomLevel = new QPushButton ("Random Generator");
    Slider = new QSlider(Qt::Horizontal);

    Text->setAlignment(Qt::AlignCenter);
    Text->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(1) + ";border-style: outset;font-size: 18pt;");
    Text->setMaximumSize(200,100);

    New->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(2) + ";border-style: outset;font-size: 18pt;");
    New->setMaximumSize(200,50);

    RandomLevel->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(4) + ";border-style: outset;font-size: 18pt;");
    RandomLevel->setMaximumSize(200,50);


    Slider->setMinimum(0);
    Slider->setMaximum(1);
    Slider->setMaximumSize(200,50);
    Slider->setStyleSheet("QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ffffff, stop:1 #6666ff);border: 1px solid #5c5c5c;width: 18px;margin: -2px 0; border-radius: 5px;}");
    connect(Slider,&QSlider::sliderReleased, this,&MainWindow::CambiarBoolean);
    QLabel * BT = new QLabel("BT");
    BT->setAlignment(Qt::AlignCenter);
    BT->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(1) + ";border-style: outset;font-size: 12pt;");
    BT->setMaximumSize(100,50);

    QLabel * BaB = new QLabel("B&B");
    BaB ->setAlignment(Qt::AlignCenter);
    BaB ->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(2) + ";border-style: outset;font-size: 12pt;");
    BaB ->setMaximumSize(100,50);

    ContainerSlider->addWidget(BT);
    ContainerSlider->addWidget(Slider);
    ContainerSlider->addWidget(BaB);

    SBackTracking = true;

    Layout->addWidget(Text, 1);

    Layout->addWidget(New);
    Layout->addWidget(RandomLevel);



    if (i > 1){
        Continuar = new QPushButton("Continue");
        Continuar->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(3) + ";border-style: outset;font-size: 18pt;");
        Continuar->setMaximumSize(200,50);
        Layout->addWidget(Continuar);
        connect(Continuar,&QPushButton::clicked,this,&MainWindow::ActivarSecondaryWindow);
    }else{
        Archi.Save(1);
        i = 1;
    }


    Layout->addLayout(ContainerSlider);
    Layout->setSizeConstraint(QLayout::SetFixedSize);
    NivelInicial = i;
    Layout->setContentsMargins(0,0,0,0);


    QWidget * Window = new QWidget ;
    Window->setLayout(Layout);
    this->setCentralWidget(Window);

    connect(New,&QPushButton::clicked,this,&MainWindow::PreActivarSecondaryWindow);
    connect(RandomLevel,&QPushButton::clicked,this,&MainWindow::ActivarRandomLevels);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActivarSecondaryWindow()
{

    this->hide();
    SW.Iniciar(NivelInicial,false, SBackTracking);
    SW.show();


}

void MainWindow::PreActivarSecondaryWindow()
{
    NivelInicial = 1;
    MArchivo Archi("C://Archivo.txt"); //TRATAR DE CREAR MARCHIVO DINAMICO PARA PODER PASARLO Y NO TENER QUE HACER UN n AL PRINCIPIO ()

    Archi.Save(NivelInicial);
    this->ActivarSecondaryWindow();
}

void MainWindow::ActivarRandomLevels()
{
    this->hide();
    SW.Iniciar(1,true, SBackTracking);
    SW.show();

}

void MainWindow::CambiarBoolean()
{
    if (SBackTracking){
        Slider->setStyleSheet("QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ffffff, stop:1 #ff6666);border: 1px solid #5c5c5c;width: 18px;margin: -2px 0; border-radius: 5px;}");
    }else{
        Slider->setStyleSheet("QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ffffff, stop:1 #6666ff);border: 1px solid #5c5c5c;width: 18px;margin: -2px 0; border-radius: 5px;}");
    }
    SBackTracking = !SBackTracking;
}
