/////////////////////////////////////////////////////////////////////////////////////////////
// Este programa recibe la informacion de la raspberry para proporcionar el movimiento
//tambien evalua si el carro debe moverse o detenerse
//Este programa esta basado para una tarjeta arduino Mega

/////////////////////////////////////////////////////////////////////////////////////////////
//Definicion de pines de valor de pines de salida y entradas

////Pines de trabajo del sensor ultrasonico
//Para hacer mas facil la programacion, decidi poner todos los pines trigger en numeros pares
//mientras que los echos son numeros impares
const int trigAdder=22;
const int echoAdder=23;
const int trigAddiz=24;
const int echoAddiz=25;
const int trigAtder=26;
const int echoAtder=27;
const int trigAtdiz=28;
const int echoAtdiz=29;

//Pines de trabajo de los servomotores
//
#include <Servo.h>
Servo SAdder;
Servo SAdiz;
Servo SAtder;
Servo SAtiz;
int sadder=0;//Definir pines PWM para el control de los servos
int sadiz=0;
int satder=0;
int satiz=0;
int an1=0;//an[i] =Angulo de movimiento 1
int an2=0;//
int an3=0;
int angle[3]={an1,an2,an3};//Definir angulos para los servomotores

//Pines de trabajo del motor
int enable=10;
int dir=11;
int velcon=9;
int svcon=8;

//Pines de trabajo de la direccion
int direna=7;
int dirdi=6;
int endder=5;
int endiz=4;
int endmid=3;

/////////////////////////////////////////////////////////////////////////////////////////////
//Definicion de variables de trabajo

//Estatico
int tolerancia=0;

//Dinamico
long duracion[4]={0,0,0,0};
int distancia[4]={0,0,0,0};
int mid=0;

//
int i,j;

void setup() 
{
  //Configuracion de pines de los sensores ultrasonicos
  for(i=22;i<30;i++)
  {
    if(i%2==0){pinMode(i,OUTPUT);}//Configura los pines trigger como salidas
    else {pinMode(i,INPUT);}
  }
  
  //Configuracion de los pines del servo
  SAdder.attach(sadder);
  SAdiz.attach(sadiz);
  SAtder.attach(satder);
  SAtiz.attach(satiz);

  //Configuracion de los pines del motor
  pinMode(enable,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(velcon,OUTPUT);
  pinMode(svcon,OUTPUT);

  //Configuracion de los pines de direccion
  pinMode(direna,OUTPUT);
  pinMode(dirdi,OUTPUT);
  pinMode(endder,INPUT);
  pinMode(endiz,INPUT);
  pinMode(endmid,INPUT);
  

  Serial.begin(9600); // Starts the serial communication
}
void loop() 
{
  
}


//////////////////////////////////////////////////////////////////////
//Analisis del movimiento
void obtenerDistancia()
{
  for(j=0;i<10;j++)
  {
    //Inicia dispara el echo
    for(i=22;i<30;i=i+1){digitalWrite(i,LOW);}
    delayMicroseconds(2);
    for(i=22;i<30;i=i+1){digitalWrite(i,HIGH);}
    delayMicroseconds(10);
    for(i=22;i<30;i=i+1){digitalWrite(i,LOW);}

    //Lee la distancia en cada uno de los sensores
    for(i=0;i<4;i++)
    {
      duracion[i]=pulseIn(i*2+23,HIGH);
      distancia[i]=duracion[i]*0.034/2;
    }

  }
}

void evaluarDistancia()
{
  digitalWrite(enable,HIGH);
  for(i=0;i<4;i++)
  {
    if(distancia[i]>tolerancia){digitalWrite(enable,LOW);}
  } 
}

void checkdir()
{
  if(mid==1 and digitalRead(endder)==HIGH){digitalWrite(direna,LOW);}
  if(mid==2 and digitalRead(endiz)==HIGH){digitalWrite(direna,LOW);}
  if(mid==0 and digitalRead(endmid)==HIGH){digitalWrite(direna,LOW);}
}
