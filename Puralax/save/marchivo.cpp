#include "marchivo.h"


MArchivo::MArchivo(QString  nombre)
{
    FileName = nombre;
    Max=CantidadLineas();


    //GuardoTodos en una lista Porque es mas facil el access

    Niveles = new QString[Max-1];



    QFile Archivo(FileName);
    Archivo.open(QFile::ReadOnly | QFile::Text);
    QTextStream out(&Archivo);


    QString Primero = out.readLine(); // como en el primero se guarda enq ue nivel esta no es parte de los niveles

    for(int i=0; i< Max-1;i++){
        Niveles[i] = out.readLine();

    }

    Archivo.close();



}

QString MArchivo::TextLevel(int i)
{
  return Niveles[i-1]; // porque el nivel 1 esta en el lugar 0
}



void MArchivo::Save(int i)
{
    QFile Archivo(FileName);

    if(!Archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        return;
    }
    QTextStream in(&Archivo);

    in.seek(0);





    QString Texto;
    Texto = QString::number(i) ;//+ "\n"

    in << Texto;

    Archivo.flush();
    Archivo.close();
}

int MArchivo::MaxMArchivo()
{

    return Max;

}

int MArchivo::Level()
{

    QFile Archivo(FileName);
    Archivo.open( QIODevice::ReadOnly | QIODevice::Text );


    QTextStream out(&Archivo);
    QString Linea;
    Linea = out.readLine();

    int dato = Linea.toInt();

    Archivo.close();

    return dato;

}

MArchivo::~MArchivo()
{

    delete[] Niveles;

}


int MArchivo::CantidadLineas()
{

    QFile Archivo(FileName);
    Archivo.open( QFile::ReadOnly | QFile::Text);

    int Tam = 0;
    QTextStream out(&Archivo);

    out.seek(0);
    QString Linea;

    out.seek(0);


    while(!out.atEnd()){

        Tam++;
        Linea = out.readLine();

    }




    Archivo.flush();
    Archivo.close();


    return Tam;




}
