int FWD_in = 13;
int BWD_in = 12;
int RGH_in = 11;
int LFT_in = 10;
int STP_in;

int dir;

int FWD_out = 2;
int BWD_out = 3;

int DIR_out = 5;
int ENB_out = 6;

void setup() {
  Serial.begin(9600);
  pinMode(FWD_in, INPUT);
  pinMode(BWD_in, INPUT);
  pinMode(RGH_in, INPUT);
  pinMode(LFT_in, INPUT);
  pinMode(STP_in, INPUT);

  pinMode(FWD_out, OUTPUT);
  pinMode(BWD_out, OUTPUT);

  pinMode(DIR_out, OUTPUT);
  pinMode(ENB_out, OUTPUT);
}

void loop() {
  for(int i=0;i<10;i++)
  {
  dir=0;
    if (digitalRead(FWD_in) == 1) {
    dir=1;
    //i++;
  }
  else if (digitalRead(BWD_in) == 1) {
    dir=2;
    //i++;
  }
  else if (digitalRead(RGH_in) == 1) {
    dir=3;
    //i++;
  }
  else if (digitalRead(LFT_in) == 1) {
    dir=4;
    //i++;
  }
  //else if(digitalRead(RGH_in) == 0){if(digitalRead(BWD_in) == 0){if(digitalRead(LFT_in) == 0){if(digitalRead(RGH_in) == 0){dir=0;}}}}
  //delay(10);
  }
  if (dir == 1) {
    digitalWrite(FWD_out, HIGH);
    digitalWrite(BWD_out, LOW);
    digitalWrite(ENB_out, LOW);
    Serial.println("Adelante");
  }
  else if (dir == 2) {
    digitalWrite(FWD_out, LOW);
    digitalWrite(BWD_out, HIGH);
    digitalWrite(ENB_out, LOW);
    Serial.println("Atras");
  }
  else if (dir == 3) {
    digitalWrite(FWD_out, HIGH);
    digitalWrite(BWD_out, LOW);
    digitalWrite(ENB_out, HIGH);
    digitalWrite(DIR_out, LOW);Serial.println("Izquierda");
  }
  else if (dir == 4) {
    digitalWrite(FWD_out, HIGH);
    digitalWrite(BWD_out, LOW);
    digitalWrite(ENB_out, HIGH);
    digitalWrite(DIR_out, HIGH);
    Serial.println("Derecha");
  }
  else if(dir==0) {
    digitalWrite(FWD_out, LOW);
    digitalWrite(BWD_out, LOW);
    digitalWrite(ENB_out, LOW);
    Serial.println("Stop");
  }
}
