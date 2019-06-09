//////////////////////////////
//Pines digitales de entrada
int bE=1; //Sensor del boton del elevador
int p1=2;//bpi = Botones de piso
int p2=3;
int p3=4;
int p4=5;
int pul=6; //Valor de la pulsera
int pos1=7; //posi=Sensor de posicion del elevador
int pos2=8;
int pos3=9;
int pos4=10;
int speso=11;//Sensor de peso

//////////////////////////////
//Pines digitales de salida
int ena= 12; //Pin enable del motor
int dir=13; //Pin direccion del motor

//////////////////////////////
//Pines analogos de entrada
int t1=A0; //ti=Sensores de temperatura
int t2=A1;
int t3=A2;
int t4=A3;

////////////////////////////////////////////////////
////////////////////////////////////////////////////
///////////////////////////////////////////////////

//////////////////////////////
//Valores de trabajo

//Valores de trabajo dinamicos
int pa; //Piso actual
int wt1=0;//Temperatura
int wt2=0;
int wt3=0;
int wt4=0;
int persona=0;//Valor de persona
int Pul=0; // Valor del pulso
int P1=0; //Pi solicitud de piso
int P2=0;
int P3=0;
int P4=0;
int aux=0;//Auxiliar para cambio de valores
int sPes=0; //Valor del sensor del peso

boolean ordenado=false;
boolean rep=false;
//
int i;
int j;

//Valores de trabajo estatico
int pesopul=1; //Valor del peso de la pulsera
int tole=255; //Valor de la tolerancia de temperatura
int valtemp=1; //Valor del peso de la temperatura
int Td=10;//Tiempo de espera de lectura
int ppiso=1;//Peso de coincidencia de piso

//Arreglos
int pes[4]={0,0,0,0};//Pesos del elevador
int ac[4]={0,0,0,0};//Peso del piso actual
int ord[4]={0,0,0,0};//Pesos ordenados
int pord[4]={0,0,0,0};//Orden de pisos a mover

void setup() 
{
  //Configuracion pines de entrada digital
  pinMode(bE,INPUT);
  pinMode(p1,INPUT);
  pinMode(p2,INPUT);
  pinMode(p3,INPUT);
  pinMode(p4,INPUT);
  pinMode(pul,INPUT);
  pinMode(pos1,INPUT);
  pinMode(pos2,INPUT);
  pinMode(pos3,INPUT);
  pinMode(pos4,INPUT);
  pinMode(speso,INPUT);
  
  //Configuracion pines de salida digital
  pinMode(ena,OUTPUT);
  pinMode(dir,OUTPUT);
}

void loop()
{
  
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Etapa de lectura y adquisicion de datos


//Lee la temperatura desde la entrada analoga
//cambia los valores de wti
//utiliza los valores de tole y valtemp 
void leertemperatura()
{
  wt1=0;
  wt2=0;
  wt3=0;
  wt4=0;
  if(analogRead(t1)>tole)
  {
    wt1=valtemp;
    wt4=valtemp;
  }
  if(analogRead(t2)>tole)
  {
    wt2=valtemp;
    wt4=valtemp;
  }
  if(analogRead(t3)>tole)
  {
    wt3=valtemp;
    wt4=valtemp;
  }
  if(analogRead(t4)>tole)
  {
    wt4=valtemp;
  }  
}

//Lee la Posicion
void leerP()
{
  //delay(Td); 
  if(digitalRead(pos1)==HIGH)
  {
    pa=0;
  }
  if(digitalRead(pos2)==HIGH)
  {
    pa=1;
  }
  if(digitalRead(pos3)==HIGH)
  {
    pa=2;
  }
  if(digitalRead(pos4)==HIGH)
  {
    pa=3;
  }
}

//Lee si alguien esta solicitando el elevador
void leerpiso()
{
  delay(Td);
  P1=0;
  P2=0;
  P3=0;
  P4=0;
  if(digitalRead(p1)==HIGH){P1=1;}
  if(digitalRead(p2)==HIGH){P2=1;}
  if(digitalRead(p3)==HIGH){P3=1;}
  if(digitalRead(p4)==HIGH){P4=1;}
}

void leerpeso()
{
  sPes=0;
  if(digitalRead(speso)==HIGH){sPes=1;}
}
void leertodo()
{
  leertemperatura();
  leerP();
  leerpiso();
  
  //Lee el estado de la pulsera
  if(digitalRead(pul)==HIGH)
  {
    Pul=pesopul; 
  }
  else
  {
    Pul=0;
  }
  
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Etapa de analisis

//Otorga el valor de los pesos dependiendo de las variables que se tienen
void peso()
{
  leertodo();
  for(i=0;i<4;i++)
  {
    if(i==pa){ac[i]=ppiso;}
    else{ac[i]=0;}
  }
  pes[0]=(P1*1+wt1+ac[0])*P1;
  pes[1]=(P2*1+wt1+ac[1])*P2;
  pes[2]=(P3*1+wt1+ac[2])*P3;
  pes[3]=(P4*1+wt1+ac[3]+Pul)*P4;
}

//Ordena la matriz de tal forma que se ordenan los pesos del piso
void sortBubble()
{
  for(i=0;i<4;i++){ord[i]=pes[i];}
  i=1;
  ordenado=false;
  while(i<4 && ordenado==false)
  {
    i=i+1;
    ordenado=true;
    for(j=0;j<3;j++)
    {
      if(ord[j]>ord[j+1])
      {
        ordenado=false;
        aux=ord[j];
        ord[j]=ord[j+1];
        ord[j+1]=aux;
      }
    }
  }
}

//Ordena la secuencia en la que el elevador debe moverse
void orden()
{
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(ord[i]==pes[j]){pord[i]=j;}
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Manipulacion de actuadores

//Espera hasta que la persona toque el boton del elevador que indique
//que ya se subio
//modifica el valor persona
void comprobarPersona()
{
  //a;adir tiempo de espera
  persona=0;
  while(persona==0)
  {
   if(digitalRead(bE)==HIGH)
   {
    persona=1;
   } 
  }
  persona=0;
}

//Activa el motor y le da direccion de movimiento
//dependiendo si se quiere subir o bajar
void mover( int Apos, int Fpos)
{
  if(Apos>Fpos)
  {
    digitalWrite(dir,HIGH);
  }
  if(Apos<Fpos)
  {
    digitalWrite(dir,LOW);
  }
  digitalWrite(ena,HIGH);
  while(Apos!= Fpos)
  {
    leerP();
    Apos=pa;
  }
  digitalWrite(ena,LOW);
}

//Hace las lecturas necesarias para generar la secuencia de pisos
void ordenar()
{
  peso();
  sortBubble();
  orden();
}

//Mueve el elevador al piso de mayor prioridad, despues se deplaza
//al siguiente piso de mayor prioridad hasta que se llena por completo
void moverapiso()
{
  ordenar();
  i=3;
  mover(pa,pord[i]);
  leerP();
  comprobarPersona();
  leerpeso();
  rep=false;
  while(sPes!=1 && not(rep))
  {
    i=i-1;
    if(i>0)
    {
      mover(pa,pord[i]);
      comprobarPersona();
      leerP();
      leerpeso();
    }
    else
    {
      if(i>2)
      {
        if(pord[i-1]==pord[i-2])
        {
          rep=true;
        }
      }
    }
    if(i==0){rep=true;}
  }
  leerP();
  mover(pa,0);  
}
