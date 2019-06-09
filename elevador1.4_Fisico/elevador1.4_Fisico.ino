//////////////////////////////
//Pines digitales de entrada
//int bE=2; //Sensor del boton del elevador  //para detectar que ya entró la persona??
int bE = 22; //bpi = Botones de piso
int p2 = 3;
int p3 = 4;
int p4 = 5;
int pos1 = 7; //posi=Sensor de posicion del elevador
int pos2 = 8;
int pos3 = 9;
int pos4 = 10;
int speso = 11; //Sensor de peso
char cel; //Valor del celular
bool subircel;
bool yaestoy;


//volatile void moverapiso(); //Por que se puso en volatile?

//////////////////////////////
//Pines digitales de salida
int ena = 12; //Pin enable del motor
int dir = 13; //Pin direccion del motor
int k2 = 23; //control de flipflops
int k3 = 24;
int k4 = 25;

//////////////////////////////
//Pines analogos de entrada
int t1 = A0; //ti=Sensores de temperatura
int t2 = A1;
int t3 = A2;
int t4 = A3;

////////////////////////////////////////////////////
////////////////////////////////////////////////////
///////////////////////////////////////////////////

//////////////////////////////
//Valores de trabajo

//Valores de trabajo dinamicos
int pa; //Piso actual
int wt1 = 0; //Temperatura
int wt2 = 0;
int wt3 = 0;
int wt4 = 0;
int vt1 = 0;
int vt2 = 0;
int vt3 = 0;
int vt4 = 0;
int persona = 0; //Valor de persona
int Pul = 0; // Valor del pulso
int P1 = 0; //Pi solicitud de piso
int P2 = 0;
int P3 = 0;
int P4 = 0;
int aux = 0; //Auxiliar para cambio de valores
int sPes = 0; //Valor del sensor del peso

boolean ordenado = false;
boolean rep = false;
//
int i;
int j;

//Valores de trabajo estatico
int pesopul = 10; //Valor del peso del celular
int tole = 100;
//Valor de la tolerancia de temperatura
int valtemp = 2; //Valor del peso de la temperatura
int Td = 10; //Tiempo de espera de lectura
int ppiso = 1; //Peso de coincidencia de piso

//Arreglos
int pes[4] = {0, 0, 0, 0}; //Pesos del elevador
int ac[4] = {0, 0, 0, 0}; //Peso del piso actual
int ord[4] = {0, 0, 0, 0}; //Pesos ordenados
int pord[4] = {0, 0, 0, 0}; //Orden de pisos a mover
int prome[4] = {0, 0, 0, 0};

int tesp = 1000;

void setup()
{
  //Configuracion pines de entrada digital
  //pinMode(bE,INPUT);
  Serial.begin(9600);
  pinMode(bE, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  //pinMode(pul,INPUT);
  pinMode(pos1, INPUT);
  pinMode(pos2, INPUT);
  pinMode(pos3, INPUT);
  pinMode(pos4, INPUT);
  pinMode(speso, INPUT);

  //Configuracion pines de salida digital
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(k4, OUTPUT);
  pinMode(k2, OUTPUT);
  pinMode(k3, OUTPUT);


  digitalWrite(ena, HIGH);
}

void loop()
{
  //peso();
  //delay(tesp);
  moverapiso();
  //leertodo();
  //delay(2000);
  //mover(1,3);
  //sortBubble();
  delay(1000);
  //leerpiso();




}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Etapa de lectura y adquisicion de datos


//Lee la temperatura desde la entrada analoga
//cambia los valores de wti
//utiliza los valores de tole y valtemp
void leertemperatura()
{
  wt1 = 0;
  wt2 = 0;
  wt3 = 0;
  wt4 = 0;
  vt1 = 0;
  vt2 = 0;
  vt3 = 0;
  vt4 = 0;
  for (i = 0; i < 4; i++) {
    prome[i] = 0;
  }

  //for (i = 0; i < 1; i++)
  for (i = 0; i < 10; i++)
  {
    vt1 = analogRead(t1);
    //vt1 = LeerCompu("Simular vt1");
    if (vt1 != 0)
    {
      wt1 = wt1 + vt1;
      prome[0] = prome[0] + 1;
    }

    vt2 = analogRead(t2);
    //vt2 = LeerCompu("Simular vt2 :");
    if (vt2 != 0)
    {
      wt2 = wt2 + vt2;
      prome[1] = prome[1] + 1;
    }

    //vt3 = LeerCompu("Simular vt3 :");
    vt3 = analogRead(t3);
    if (vt3 != 0)
    {
      wt3 = wt3 + vt3;
      prome[2] = prome[2] + 1;
    }

    //vt4 = LeerCompu("Simular vt4 :");
    vt4 = analogRead(t4);
    if (vt4 != 0)
    {
      wt4 = wt4 + vt4;
      prome[3] = prome[3] + 1;
    }
    vt1 = wt1 / prome[0];
    vt2 = wt2 / prome[1];
    vt3 = wt3 / prome[2];
    vt4 = wt4 / prome[3];
  }
  if (vt1 > tole)
  {
    wt1 = valtemp;
    wt4 = valtemp;
  }
  else {
    wt1 = 0;
    wt4 = 0;
  }
  if (vt2 > tole)
  {
    wt2 = valtemp;
    wt4 = valtemp;
  }
  else {
    wt2 = 0;
    wt4 = 0;
  }
  if (vt3 > tole)
  {
    wt3 = valtemp;
    wt4 = valtemp;
  }
  else {
    wt3 = 0;
    wt4 = 0;
  }
  if (vt4 > tole)
  {
    wt4 = valtemp;
  }

  Serial.println("wt1");
  Serial.println(vt1);
  Serial.println("wt2");
  Serial.println(vt2);
  Serial.println("wt3");
  Serial.println(vt3);
  Serial.println("wt4");
  Serial.println(vt4);
  delay(tesp);
}

//Lee la Posicion
void leerP()
{
  delay(Td);

  if (digitalRead(pos1) == LOW)
  {
    pa = 0;
  }
  if (digitalRead(pos2) == LOW)
  {
    pa = 1;
  }
  if (digitalRead(pos3) == LOW)
  {
    pa = 2;
  }
  if (digitalRead(pos4) == LOW)
  {
    pa = 3;
  }
  //pa = LeerCompu("Posicion actual");
  Serial.println("pa");
  Serial.println(pa);
  //delay(tesp);

}

//Lee si alguien esta solicitando el elevador
void leerpiso()
{
  P2 = 0;
  P3 = 0;
  P4 = 0;
  //P2 = LeerCompu("Alguien solicita al piso 2 (1)si (0)no :");
  //P3 = LeerCompu("Alguien solicita al piso 3 (1)si (0)no :");
  //P4 = LeerCompu("Alguien solicita al piso 4 (1)si (0)no :");
  if (digitalRead(p2) == HIGH)
  {
    P2 = 1;
    Serial.print("p2=");
    Serial.println(P2);
    digitalWrite(k2, HIGH);
    digitalWrite(k2, LOW);
  }
  if (digitalRead(p3) == HIGH)
  {
    P3 = 1;
    Serial.print("p3=");
    Serial.println(P3);
    digitalWrite(k3, HIGH);
    digitalWrite(k3, LOW);
  }
  if (digitalRead(p4) == HIGH)
  {
    P4 = 1;
    Serial.print("p4=");
    Serial.println(P4);
    digitalWrite(k4, HIGH);
    digitalWrite(k4, LOW);
  }
}

void leerpeso() //peso fisicooooooo
{
  sPes = 0;
  if (digitalRead(speso) == HIGH)
  {
    //if (LeerCompu("Leer peso (1)si (0)no") == 1) {
    sPes = 1;
    Serial.println("spes");

    Serial.println(sPes);
  }
}
void leertodo()
{
  leertemperatura();
  leerP();
  leerpiso();
  //leerpeso();
  celular();

}


void celular()
{

  //Lee el estado de la pulsera
  Pul = 0;

  if (Serial.available() > 0)
  {
    cel = Serial.read();

    if (cel == 'A' ) {
      subircel = true;
      Serial.println("HIGH");
      delay(20);
      Pul = 10;
      P4 = 1;
    }

    if (cel == 'B') {

      yaestoy = false;
      Serial.println("YA ESTOY");
      delay(20);
    }

  }

  /*if (LeerCompu("La pulsera esta activa?") > 0) {
    Pul = 10;
    P4 = 1;
    }
  */
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Etapa de analisis

//Otorga el valor de los pesos dependiendo de las variables que se tienen
void peso()
{
  leertodo();
  for (i = 0; i < 4; i++)
  {
    if (i == pa) {
      ac[i] = ppiso;
    }
    else {
      ac[i] = 0;
    }
  }
  pes[0] = (P1 * 1 + wt1 + ac[0]) * P1;
  pes[1] = (P2 * 2 + wt2 + ac[1]) * P2;
  pes[2] = (P3 * 3 + wt3 + ac[2]) * P3;
  pes[3] = (P4 * 4 + wt4 + ac[3] + Pul) * P4;
  for (i = 0; i < 2; i++)
  {
    if (pes[i] == pes[i + 1])
    {
      pes[i + 1] = pes[i + 1] + 1;
    }
  }
  //printMA(pes, "El peso del piso es : ");
}

//Ordena la matriz de tal forma que se ordenan los pesos del piso
void sortBubble()
{
  for (i = 0; i < 4; i++) {
    ord[i] = pes[i];
  }
  i = 1;
  ordenado = false;
  while (i < 4 && ordenado == false)
  {
    i = i + 1;
    ordenado = true;
    for (j = 0; j < 3; j++)
    {
      if (ord[j] > ord[j + 1])
      {
        ordenado = false;
        aux = ord[j];
        ord[j] = ord[j + 1];
        ord[j + 1] = aux;
      }
    }
  }
}

//Ordena la secuencia en la que el elevador debe moverse
void orden()
{
  //Serial.println("Antes de ordenar");
  //printMA(pes, "El peso del piso es");
  //printMA(ord, "El orden de peso es");
  //printMA(pord, "La prioridad es");

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      if (ord[i] == pes[j]) {
        pord[3 - i] = j;
      }
    }
  }
  //Serial.println("Despues de ordenar");
  //printMA(pes, "El peso del piso es");
  //printMA(ord, "El orden de peso es");
  //printMA(pord, "La prioridad es");
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Manipulacion de actuadores

//Espera hasta que la persona toque el boton del elevador que indique
//que ya se subio
//modifica el valor persona
void comprobarPersona()
{
  int espera = 0;
  persona = 0;
  while (persona == 0 and espera < 10)
  {
    if (digitalRead(bE) == HIGH) {
      persona = 1;
    }
    espera++;
    delay(1000);
  }
  persona = 0;
}

//Activa el motor y le da direccion de movimiento
//dependiendo si se quiere subir o bajar
void mover( int Apos, int Fpos)
{
  if (Apos > Fpos)
  {
    digitalWrite(dir, LOW);
  }
  if (Apos < Fpos)
  {
    digitalWrite(dir, HIGH);
  }
  digitalWrite(ena, LOW);
  while (Apos != Fpos)
  {
    leerP();
    Apos = pa;
    Serial.print("Posicion final :");
    Serial.println(Fpos);
  }
  digitalWrite(ena, HIGH);
}

//Hace las lecturas necesarias para generar la secuencia de pisos
void ordenar()
{
  peso();
  sortBubble();
  orden();
}

void start()
{
  Serial.println("In start");
  rep = true;
  while (rep)
  {
    int sum = 0;
    ordenar();
    for (i = 0; i < 4; i++)
    {
      sum = pes[i] + sum;
    }
    if (sum != 0)
    {
      rep = false;
    }
  }
  Serial.println("End start");
}

//Mueve el elevador al piso de mayor prioridad, despues se deplaza
//al siguiente piso de mayor prioridad hasta que se llena por completo
void moverapiso()
{
  //Serial.println("Inicio");
  rep = false;
  //Serial.println("Before start");
  start();
  i = 0;
  //printMA(pord, "Orden de prioridad");
  //leerP();
  mover(pa, pord[i]);
  //Serial.print("Movimiento a primer piso");
  //Serial.println(pord[i]);
  comprobarPersona();
  leerpeso();

  Serial.println("While");
  //delay(stopp);
  while (sPes != 1 && not(rep))
  {
    if (i < 3)
    {
      if (pord[i] == pord[i + 1])
      {
        Serial.println();
        rep = true;
      }
    }
    if (i == 3)
    {
      rep = true;
    }
    i++;
    if (not(rep))
    {
      mover(pa, pord[i]);
      comprobarPersona();
      //leerP();
      leerpeso();
    }
  }
  mover(pa, 0);
}

void printMA(int A[], String B)
{
  Serial.println("----");
  for (int x = 0; x < 4; x++)
  {
    Serial.print(B);
    Serial.println(A[x]);
  }
  Serial.println("****");
}
int LeerCompu(String A)
{
  String ret;
  boolean whiread = true;
  Serial.println(A);
  while (whiread)
  {
    if (Serial.available() > 0)
    {
      ret = Serial.readString();
      whiread = false;
    }
  }
  Serial.println("Dato recibido");
  return ret.toInt();
}
