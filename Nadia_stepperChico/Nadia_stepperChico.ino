//Pines de accion del stepper
//  Pin de direccion
#define dir 2
//  Pin de paso
#define paso 3
//  Tiempo de paro en ms
#define paro 500

//Pines de simulacion
//  Simulacion de piso actual
#define sAf A0
//  Simulacion de piso a mover
#define sDf A1
int Af=0;
int Df=0;

//Para el stepper chico
int Pos=0;
int i;
void setup() 
{
  pinMode(dir,OUTPUT);
  pinMode(paso,OUTPUT);
  digitalWrite(paso,LOW);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() 
{
  Af=rango(analogRead(sAf));
  Df=rango(analogRead(sDf));
  moveStepper(Af,Df);
}

//Evalua en que piso se encuentra actualmente
//determina la direccion del movimiento
//ejecuta el movimiento
void moveStepper(int Af, int Df)
{
  if(Af>Df)
  {
    digitalWrite(dir,LOW);
    //pasos();
    stepC(-1);
    
  }
  if(Af<Df)
  {
    digitalWrite(dir,HIGH);
    //pasos();
    stepC(1);
  }
  if(Af==Df){parar();}
}

//Genera el paso mediante la creacion de una transiscion
//alto bajo
void pasos()
{
  Serial.println("Paso activos");
  digitalWrite(paso,HIGH);
  delay(paro);
  digitalWrite(paso,LOW);
  delay(paro);
}
////////////////////////////////////////////////////////
//Step provisional 4 salidas
////////////////////////////////////////////////////////
int secuencia[4][4]=
{
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}  
};

/////////////////////////////////////////////////////////
//Para simulacion
void stepC(int d)
{
  Pos=Pos+d;
  if(Pos<0)
  {
    Pos=3;
  }
  if(Pos>3)
  {
    Pos=0;
  }
  digitalWrite(8,secuencia[Pos][0]);
  digitalWrite(9,secuencia[Pos][1]); 
  digitalWrite(10,secuencia[Pos][2]);
  digitalWrite(11,secuencia[Pos][3]);
  delay(2);
}
void parar()
{
  for(int i=8;i<12;i++)
  {
    digitalWrite(i,LOW);
  }
}
/////////////////////////////////////////////////////////
int rango(int M)
{
  int ret;
  if(M>0&&M<256)
  {
    ret=0;
  }
  if(M>=257&&M<512)
  {
    ret=1;
  }
  if(M>=513&&M<768)
  {
    ret=2;
  }
  if(M>=769&&M<1024)
  {
    ret=3;
  }
  return ret;
}
