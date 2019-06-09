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
  Serial.begin(9600);
  pinMode(dir,OUTPUT);
  pinMode(paso,OUTPUT);
  digitalWrite(paso,LOW);
  for(i=8;i<12;i++)
  {
    pinMode(i,OUTPUT);
  }
}

void loop() 
{
  //Piso actual
  Af=rango(analogRead(sAf));
  //Piso a mover
  Df=rango(analogRead(sDf));
  Serial.print("Valor del piso Af : ");
  Serial.println(Af);
  Serial.print("Valor del piso Df : ");
  Serial.println(Df);
  moveStepper(Af,Df);
  delay(1000);
}

//Evalua en que piso se encuentra actualmente
//determina la direccion del movimiento
//ejecuta el movimiento
void moveStepper(int Af, int Df)
{
  if(Af>Df)
  {
    digitalWrite(dir,LOW);
    Serial.println("Abajo");
    pasos();
    stepC(-1);
    
  }
  if(Af<Df)
  {
    digitalWrite(dir,HIGH);
    Serial.println("Arriba");
    pasos();
    stepC(1);
  }
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
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}  
};

/////////////////////////////////////////////////////////
//Para simulacion
void stepC(int d)
{
  Pos=Pos+d;
  if(Pos<0)
  {
    Pos=4;
  }
  if(Pos>4)
  {
    Pos=0;
  }
  for(i=8;i<12;i++)
  {
    for(int s=0;s<4;s++)
    {
      digitalWrite(i,secuencia[Pos][s]);
    }
  }
  delay(10);
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
