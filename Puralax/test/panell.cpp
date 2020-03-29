#include "panell.h"
#include "ui_panell.h"

Panell::Panell(int Max_X, int Max_Y, int *Arr, int ColorGanador, bool BT, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Panell)
{

    //ui->setupUi(this);



    MaxX = Max_X;
    MaxY = Max_Y;
    ColorGan = ColorGanador;

    Ta.CreateTablero(MaxX,MaxY);


    PrimerClick = true;

    Botones = new QButtonGroup;
    VisualBotones = new QGridLayout;

    Ta.LoadTablero(Arr);

    //MostrarMatriz();


    ReArr = new int [MaxX*MaxY*2];



    memcpy(ReArr,Arr,sizeof(int) *  MaxX*MaxY*2);
    //MostrarArr(Arr);





    CargarVisual();
    VisualBotones->setSizeConstraint(QLayout::SetFixedSize);

   // this->Reset();





    connect(Botones,static_cast <void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),this,&Panell::Accion);


    setLayout(VisualBotones);
    //MostrarArr(ReArr);
    CantidadEntradas=0;


    if (BT) {
       BackTracking();
    }else{
       RyP();
    }



}

void Panell::Reset()
{

    Ta.LoadTablero(ReArr);
    ActualizarVisual();


}

void Panell::Resolver()
{
    QThread Tiempo;
    Ta.LoadTablero(ReArr);
    MostrarSolucion(Solution);
    for (int i =0; i< Solution.size() ; i++){
        ActualizarVisual();
        QApplication::processEvents();
        Tiempo.sleep(1);
        if (!Gano()){
           ResolverRecursion(i);
        }


    }
    ResultadoTablero();

}

bool Panell::PoseeSolucion()
{
    if (Solution.size() > 0 ){
        return true;
    }else{
        return false;
    }
}

Panell::~Panell()
{
    delete[] ReArr;
    delete ui;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void Panell::Accion(const int & n)
{

    Estado::Dupla Pos = VerLugar(n);

    if (PrimerClick){
         if(EsHabilPrimerClick(Pos)){
             DatosPrimerClick = Pos;
             PrimerClick=false;
         }

    }else{
        if(EsHabilSegundoClick(Pos,DatosPrimerClick)){
            Pintar(Pos,DatosPrimerClick);
            ResultadoTablero();
        }
        PrimerClick=true;
    }

}

void Panell::ResultadoTablero()
{

    if  (Gano()){
        QApplication::processEvents();
        emit SignalWin();
     }else{
        if (NoMasMovientos()){
            QTimer::singleShot(3000,this,&Panell::Reset);
        }

    }
}




Estado::Dupla Panell::VerLugar(int numero)
{

    Estado::Dupla Posicion;
    Posicion.x = 0;
    Posicion.y = 0;

    while(numero >= MaxX)
    {
        numero-= MaxX;
        Posicion.y++;
    }
    Posicion.x = numero;

    return Posicion;
}




bool Panell::EsHabilPrimerClick(Estado::Dupla Valores)
{
    if (Ta.GetBloque(Valores.x,Valores.y).GetMov() > 0 ){
        return true;
    }else
        return false;
}




bool Panell::EsHabilSegundoClick(Estado::Dupla SeCl, Estado::Dupla PrCl)
{


    if (EsAdy(PrCl,SeCl) && (Ta.GetBloque(PrCl.x,PrCl.y).GetColor() != Ta.GetBloque(SeCl.x,SeCl.y).GetColor() )){
        return true;
    }else
        return false;

}




bool Panell::EsAdy(Estado::Dupla PrCl, Estado::Dupla SeCl)
{

    if ((PrCl.x == SeCl.x) && ((PrCl.y == SeCl.y+1 ) || (PrCl.y == SeCl.y-1))){
        return true;
    }
    if ((PrCl.y == SeCl.y) && ((PrCl.x == SeCl.x+1 ) || (PrCl.x == SeCl.x-1))){
        return true;
    }
    return false;
}




void Panell::Pintar(Estado::Dupla SeCl, Estado::Dupla PrCl)
{




    ModificarTablero(SeCl,PrCl);
    ActualizarVisual(); //Carga todas la modificaciones






}

void Panell::ModificarTablero(Estado::Dupla SeCl, Estado::Dupla PrCl)
{
    if (Ta.GetBloque(SeCl.x,SeCl.y).GetColor() == 0){

        Ta.SetTaBloque(SeCl.x,SeCl.y,Ta.GetBloque(PrCl.x,PrCl.y).GetColor(),Ta.GetBloque(PrCl.x,PrCl.y).GetMov()-1); //Se corre y resta 1
        Ta.SetTaBloque(PrCl.x,PrCl.y,0,0);

    }else{
        PintarGrupo(Ta.GetBloque(PrCl.x,PrCl.y).GetColor(),SeCl.x,SeCl.y, Ta.GetBloque(SeCl.x,SeCl.y).GetColor() ); //pinta el grupo


        Ta.SetTaBloque(PrCl.x,PrCl.y,Ta.GetBloque(PrCl.x,PrCl.y).GetColor(),Ta.GetBloque(PrCl.x,PrCl.y).GetMov()-1);//Resta 1 al mov

    }
}



void Panell::PintarGrupo(const int &ColorBase, int PosX, int PosY, int ColorGrupo)
{

    Ta.SetTaBloque(PosX,PosY,ColorBase,Ta.GetBloque(PosX,PosY).GetMov());

    PosibleMoviento(ColorBase,PosX,PosY+1,ColorGrupo);
    PosibleMoviento(ColorBase,PosX,PosY-1,ColorGrupo);
    PosibleMoviento(ColorBase,PosX+1,PosY,ColorGrupo);
    PosibleMoviento(ColorBase,PosX-1,PosY,ColorGrupo);


}

void Panell::PosibleMoviento(const int &ColorBase, int PosX, int PosY, const int &ColorGrupo)
{

    if (((EstaAdentro(PosX,PosY)) && (Ta.GetBloque(PosX,PosY).GetColor() == ColorGrupo ))){
        PintarGrupo(ColorBase,PosX,PosY, ColorGrupo);
    }

}

bool Panell::EstaAdentro(const int &x, const int &y)
{
    if ((x < MaxX)&& (x >= 0)){
       if ((y < MaxY)&& (y >= 0)){
           return true;
       }
    }
    return false;
}

void Panell::CargarVisual()
{


    int i = 0;
    int j = 0;
    while(j < MaxY)
    {
        while (i< MaxX)
        {
        //    qDebug() << "Medio1";
            QPushButton * Button = new QPushButton();
          //  qDebug() << "Medio2";

            Button->setMinimumSize(100,100);
            Button->setMaximumSize(100,100);

            //qDebug() << "Medio3";


            Button->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(Ta.GetBloque(i,j).GetColor()) + ";border-style: outset;font-size: 18pt;");
            //qDebug() << "Medio4";
            if (Ta.GetBloque(i,j).GetMov() != 0){
                Button->setText(QString::number(Ta.GetBloque(i,j).GetMov()));
            }else{
                Button->setText("");
            }

            //qDebug() << "Medio5";




          //  Button->setAutoFillBackground(true);
          //  Button->setPalette(paleta);

            VisualBotones->addWidget(Button, j, i);
            //qDebug() << "Medio6";



            Botones->addButton(Button,i+j*MaxX);
            //qDebug() << "Medio7";


            i++;
        }
        j++;
        i=0;
    }

  //  qDebug() << "salio";




}

void Panell::ActualizarVisual()
{
   // MostrarMatriz();
   // qDebug() << "entro";
    int i = 0;
    int j = 0;



    while(j < MaxY)
    {
        while (i< MaxX)
        {

            Botones->button(i+j*MaxX)->setMinimumSize(100,100);
            Botones->button(i+j*MaxX)->setMaximumSize(100,100);
            Botones->button(i+j*MaxX)->setStyleSheet("color: rgb(255,255,255);background-color: " + Pal.Color(Ta.GetBloque(i,j).GetColor()) + ";border-style: outset;font-size: 18pt;");
            if (Ta.GetBloque(i,j).GetMov() != 0){
                Botones->button(i+j*MaxX)->setText(QString::number(Ta.GetBloque(i,j).GetMov()));
            }else{
                Botones->button(i+j*MaxX)->setText("");
            }


            i++;
        }
        j++;
        i=0;
    }

   // qDebug() << "salio";


}

bool Panell::Gano()
{


        for(int i=0; i< MaxY; i++){
            for(int j=0; j < MaxX ; j++){
                if ((Ta.GetBloque(j,i).GetColor() != 0)&& (Ta .GetBloque(j,i).GetColor() != ColorGan)){
                    return false;
                }

            }
        }
        return true;




}

bool Panell::Gano(Tablero Table)
{


        for(int i=0; i< MaxY; i++){
            for(int j=0; j < MaxX ; j++){
                if ((Table.GetBloque(j,i).GetColor() != 0)&& (Table .GetBloque(j,i).GetColor() != ColorGan)){
                    return false;
                }

            }
        }
        return true;




}

bool Panell::NoMasMovientos()
{

    for(int i=0; i< MaxY; i++){
        for(int j=0; j < MaxX ; j++){
            if (Ta.GetBloque(j,i).GetMov() != 0 ){
                return false;
            }

        }
    }
    return true;


}




void Panell::MostrarMatriz()
{

    for(int i=0; i< MaxY; i++){
        for(int j=0; j < MaxX ; j++){
            qDebug() << Ta.GetBloque(j,i).GetColor() << " " << Ta.GetBloque(j,i).GetMov();

        }
        qDebug() << "----------------------------";

    }
}

void Panell::MostrarArr(int *Arr)
{
    qDebug() << "----------------------------";
    for(int i = 0; i< MaxX*MaxY*2; i++){
        qDebug() << Arr[i];
    }
    qDebug() << "----------------------------";
}


///////////////////////////////////////////////////////////////ALGO2///////////////////////////////////////////////////////////////////////////////////////////////////



void Panell::BackTracking()
{
    int TamMovimientos = CantidadMovimientos();


    Estado::Dupla * Movimientos = new Estado::Dupla[TamMovimientos];

    CargarMovimientos(Movimientos);

    bool Termino = false;

    PilaTableros PTable;

    PTable.Agregar(Ta.ArregloTablero());

    PrimeraEtapa(PTable,Movimientos,Solution,TamMovimientos,Termino);

    //MostrarSolucion(Solution);

    Ta.LoadTablero(ReArr);
    ActualizarVisual();

    delete[] Movimientos;

}


int Panell::CantidadMovimientos()
{
    int aux=0;

    for(int i=0; i< MaxY; i++){
        for(int j=0; j < MaxX ; j++){
            if (Ta.GetBloque(j,i).GetMov() > 0){
                aux++;
            }

        }
    }

    return aux;
}

int Panell::CantidadMovimientosTotales()
{
    int aux=0;

    for(int i=0; i< MaxY; i++){
        for(int j=0; j < MaxX ; j++){
            if (Ta.GetBloque(j,i).GetMov() > 0){
                aux+=Ta.GetBloque(j,i).GetMov();
            }

        }
    }

    return aux;
}

int Panell::CantidadColores()
{
    QList<int> Colores;
    for (int i=0 ; i < MaxX ; i++){
        for(int j=0 ; j<MaxY ;j++){
            if (Ta.GetBloque(i,j).GetColor() != 0 && !Colores.contains(Ta.GetBloque(i,j).GetColor()) ){
                Colores.push_back(Ta.GetBloque(i,j).GetColor());
            }

        }
    }
    return Colores.size();

}

void Panell::CargarMovimientos(Estado::Dupla *Mov)
{

    int Pos=0;
    Estado::Dupla Aux;
    for(int i=0; i< MaxY; i++){
        for(int j=0; j < MaxX ; j++){
            if (Ta.GetBloque(j,i).GetMov() > 0){

                Aux.x = j;
                Aux.y = i;
                Mov[Pos] = Aux;
                Pos++;

            }

        }
    }

}

void Panell::PrimeraEtapa(PilaTableros &PTable, Estado::Dupla *Movimientos, QList<Estado::Camino> & LSolucion, int MaxArrMov, bool &Termino)
{

    CantidadEntradas++;

    if (Gano())
    {
        Termino = true;
    }
    else
    {
        if (!Poda(Movimientos,MaxArrMov)){

            for (int i=0; i < MaxArrMov;i++){

                if (Ta.GetBloque(Movimientos[i].x, Movimientos[i].y).GetMov() > 0 ){

                    Mover(PTable,Movimientos,LSolucion,MaxArrMov,Termino,i,0,-1,'U');
                    Mover(PTable,Movimientos,LSolucion,MaxArrMov,Termino,i,0,1,'D');
                    Mover(PTable,Movimientos,LSolucion,MaxArrMov,Termino,i,-1,0,'L');
                    Mover(PTable,Movimientos,LSolucion,MaxArrMov,Termino,i,1,0,'R');
                }
            }
        }
    }
}

void Panell::Mover(PilaTableros &PTable, Estado::Dupla *Movimientos, QList<Estado::Camino> &LSolucion, int MaxArrMov, bool &Termino, int i, int Mx, int My, QChar Dir)
{

    if (!Termino  ){

            Estado::Dupla Aux2;
            Estado::Dupla Aux1;

            Aux1.x = Movimientos[i].x;
            Aux1.y = Movimientos[i].y;

            Aux2.x = Movimientos[i].x + Mx;
            Aux2.y = Movimientos[i].y + My;

            if (EstaAdentro(Aux2.x , Aux2.y) && EsHabilPrimerClick(Aux1) && EsHabilSegundoClick(Aux2,Aux1) ){

                bool Corrimiento = false;

                if(Ta.GetBloque(Aux2.x,Aux2.y).GetColor() == 0){

                    Movimientos[i].x += Mx;
                    Movimientos[i].y += My;
                    Corrimiento = true;
                }

                Estado::Camino C;
                C.direccion = Dir;
                C.x = Aux1.x;
                C.y = Aux1.y;

                if (!PTable.IsEmpty()){
                    Ta.LoadTablero(PTable.Tope());
                }

                Pintar(Aux2,Aux1);

                PTable.Agregar(Ta.ArregloTablero());
                LSolucion.push_back(C);

                PrimeraEtapa(PTable,Movimientos,LSolucion,MaxArrMov,Termino);

                if(!Termino){

                    if (Corrimiento){
                        Movimientos[i].x -= Mx;
                        Movimientos[i].y -= My;

                    }

                    LSolucion.pop_back();

                    PTable.SacarTope();
                    Ta.LoadTablero(PTable.Tope());
                }
            }
    }

}

void Panell::MostrarSolucion(QList<Estado::Camino> LSolucion)
{
    for (int i = 0; i < LSolucion.size() ; i++){
        qDebug() << LSolucion[i].direccion << " ";
    }
}

bool Panell::HayMovColorGanador()
{
    for (int i =0; i < MaxX; i++){
        for (int j =0 ; j < MaxY ;j++){
            if (ColorGan == Ta.GetBloque(i,j).GetColor() && Ta.GetBloque(i,j).GetMov() > 0){
                return true;
            }
        }
    }
    return false;
}

bool Panell::Poda(Estado::Dupla *Movimientos, int MaxArrMov)
{
    if (!HayMovColorGanador()){
        return true;
    }else{
        if (CantidadMovimientosTotales() < CantidadColores()-1){
            return true;
        }
        if (!HayConexion(Movimientos, MaxArrMov)){
            return true;
        }
        return false;

    }

}

bool Panell::HayConexion(Estado::Dupla *Movimientos, int MaxArrMov)
{

    Tablero AUX ;
    AUX.CreateTablero(MaxX,MaxY);
    AUX.LoadTablero(Ta.ArregloTablero());



    for (int i = 0 ; i < MaxArrMov ; i++){
        ExpandirMovimiento(Movimientos[i].x,Movimientos[i].y,Ta.GetBloque(Movimientos[i].x,Movimientos[i].y).GetMov(),Ta.GetBloque(Movimientos[i].x,Movimientos[i].y).GetColor());
    }

    RePintar(Movimientos,MaxArrMov,AUX);
    bool EsMismoColor = Gano();

    Ta.LoadTablero(AUX.ArregloTablero());

    return EsMismoColor;

}



void Panell::ExpandirMovimiento(int X, int Y, int Cantidad, int ColorGrupo)
{
        if (Cantidad > 0 ){
            ExpancionDeMovimientos(X,Y-1, Cantidad-1,ColorGrupo);
            ExpancionDeMovimientos(X,Y+1, Cantidad-1,ColorGrupo);
            ExpancionDeMovimientos(X-1,Y, Cantidad-1,ColorGrupo);
            ExpancionDeMovimientos(X+1,Y, Cantidad-1,ColorGrupo);
        }



}

void Panell::ExpancionDeMovimientos(int X, int Y, int Cantidad, int ColorGrupo)
{
    if (EstaAdentro(X,Y)){
        if (Ta.GetBloque(X,Y).GetColor() < 1){
            Ta.SetTaBloque(X,Y,ColorGrupo,Ta.GetBloque(X,Y).GetMov());
            ExpandirMovimiento(X,Y,Cantidad,ColorGrupo);
        }else{
            if (Ta.GetBloque(X,Y).GetColor() != ColorGrupo){
                PintarGrupo(ColorGrupo,X,Y,Ta.GetBloque(X,Y).GetColor());
                ExpandirMovimiento(X,Y,Cantidad,ColorGrupo); //no lo agrego afuera porque no quiero que se expanda si es del mismo grupo

            }
        }
    }
}



void Panell::RePintar(Estado::Dupla *Movimientos, int MaxArrMov, Tablero & Aux)
{
    for (int i =0; i < MaxArrMov ; i++ ){
        if (Aux.GetBloque(Movimientos[i].x,Movimientos[i].y).GetColor() == ColorGan && Ta.GetBloque(Movimientos[i].x,Movimientos[i].y).GetColor() != ColorGan ){
            PintarGrupo(ColorGan, Movimientos[i].x,Movimientos[i].y,Ta.GetBloque(Movimientos[i].x,Movimientos[i].y).GetColor());
        }
    }
}

void Panell::RyP()
{
    PriorityQueue P;


    int TamMovimientos = CantidadMovimientos();
    Estado::Dupla * Movimientos = new Estado::Dupla[TamMovimientos];
    CargarMovimientos(Movimientos);

    QList<Estado::Camino> Solucion;


    Estado Inicio(Ta,Movimientos,TamMovimientos,Solucion);
    P.Add(100,Inicio);
    bool Termino = false;



    Estado E  = Inicio;//Para poder usarlo
    while (!P.IsEmpty() && !Termino){
           E = P.ExtractLowest();
           QList<Estado> Hijos = GenerateChildren(E,TamMovimientos);

           for (int i =0; i < Hijos.size(); i++){
               CantidadEntradas++;
               Ta.LoadTablero(Hijos[i].GetTablero());
               //ActualizarVisual();

               if (Gano()){

                   Solucion = Hijos[i].GetSolucion();
                   Termino = true;

                }else{
                   P.Add(CantidadGrupos(),Hijos[i]);
                }

           }
   }

    delete[] Movimientos;

    Solution = Solucion;
    Ta.LoadTablero(ReArr);
    ActualizarVisual();
    QApplication::processEvents();

}

QList<Estado> Panell::GenerateChildren(Estado e, int TamMov)
{
    QList<Estado> ListaDeHijos;
    Ta.LoadTablero(e.GetTablero());

    int i = 0;
    Estado::Dupla * Movimientos= e.GetMovimientos();

    while (i < TamMov ){
        if (Ta.GetBloque(Movimientos[i].x,Movimientos[i].y).GetMov() >0 ){

            OneChild (ListaDeHijos, e,0,-1,'U',i);
            OneChild (ListaDeHijos, e,0,1,'D',i);
            OneChild (ListaDeHijos, e,-1,0,'L',i);
            OneChild (ListaDeHijos, e,1,0,'R',i);
        }
        i++;


    }
    return ListaDeHijos;
}

void Panell::OneChild(QList<Estado> &ListaDeHijos, Estado e, int MovX, int MovY, char Dir, int i)
{
    Ta.LoadTablero(e.GetTablero());
    Tablero TAux;
    TAux.CreateTablero(MaxX,MaxY);
    TAux.LoadTablero(Ta.ArregloTablero()); //Mantengo un aux

    Estado::Dupla Aux2;
    Estado::Dupla Aux1;

    Aux1.x =  e.GetMovimientos()[i].x;
    Aux1.y =  e.GetMovimientos()[i].y;

    Aux2.x = Aux1.x + MovX;
    Aux2.y = Aux1.y + MovY;



    if (EstaAdentro(Aux2.x , Aux2.y) && EsHabilPrimerClick(Aux1) && EsHabilSegundoClick(Aux2,Aux1) ){

        Estado::Dupla * Movimi = e.GetMovimientos();

        if(Ta.GetBloque(Aux2.x,Aux2.y).GetColor() == 0){
            Movimi[i].x = Aux2.x;
            Movimi[i].y = Aux2.y;

        }

        Estado::Camino C;

        C.direccion = Dir;
        C.x = Aux1.x;
        C.y = Aux1.y;

        QList<Estado::Camino> Solution = e.GetSolucion();
        Solution.push_back(C);

        Pintar(Aux2,Aux1);

        Estado NewE(Ta,Movimi,e.GetTam(),Solution);

        if (Gano() || !Poda(Movimi,e.GetTam())){
            ListaDeHijos.push_back(NewE);
        }

        Ta.LoadTablero(TAux.ArregloTablero());
    }
}

int Panell::CantidadGrupos()
{
    bool ** Pasadas;

    Pasadas = new bool*[MaxX];
    for (int k = 0 ;k < MaxX ;k++){
        Pasadas[k]= new bool[MaxY];
    }

    for (int i= 0; i < MaxX ; i++){
        for (int j = 0 ; j < MaxY ; j++){
            Pasadas[i][j] = false;
        }
    }

    int Colores = 1; //por el color ganador, si no hubiera sido podado
    for (int i= 0; i < MaxX ; i++){
        for (int j = 0 ; j < MaxY ; j++){

                if (!Pasadas[i][j] && Ta.GetBloque(i,j).GetColor() != 0){
                    if (Ta.GetBloque(i,j).GetColor() != ColorGan){
                        Colores++;
                    }
                    CargarPasadas(i,j,Pasadas,Ta.GetBloque(i,j).GetColor());


                 }


        }
    }


    delete[] Pasadas;

    return Colores;
}

void Panell::CargarPasadas(int x, int y, bool **Pasadas, int ColorG)
{
    if ((EstaAdentro(x,y))&& !Pasadas[x][y] &&(Ta.GetBloque(x,y).GetColor() == ColorG)){
        Pasadas[x][y] = true;
        CargarPasadas(x,y-1,Pasadas,ColorG);
        CargarPasadas(x,y+1,Pasadas,ColorG);
        CargarPasadas(x-1,y,Pasadas,ColorG);
        CargarPasadas(x+1,y,Pasadas,ColorG);
    }
}



void Panell::ResolverRecursion(int i)
{

    if(i< Solution.size() ){

        QChar Direc = Solution[i].direccion;

        Estado::Dupla PrimClick;
        PrimClick.x = Solution[i].x;
        PrimClick.y = Solution[i].y;

        Estado::Dupla SegundoClick;
        SegundoClick.x = Solution[i].x;
        SegundoClick.y = Solution[i].y;

        if (Direc == 'U'){
            SegundoClick.y = SegundoClick.y -1;
        }else{
            if(Direc== 'D'){
                SegundoClick.y = SegundoClick.y +1;
            }else{
                if (Direc == 'L'){
                    SegundoClick.x = SegundoClick.x-1;
                }else{
                    if(Direc == 'R'){
                        SegundoClick.x = SegundoClick.x +1;
                    }
                }
            }
        }

        Pintar(SegundoClick, PrimClick);

    }
}





