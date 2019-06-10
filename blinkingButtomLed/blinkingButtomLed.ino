//Turn on a led with a button
const int Led = 13; //pin for the Led
const int Buttom = 7; //pin for the Buttom
int val = 0; //Val will be used to store the state of the input led

void setup()
{
  pinMode(Led,OUTPUT);
  pinMode(Buttom,INPUT);
}

void loop() 
{
  val = digitalRead(Buttom);
  if(val==HIGH)
  {
    digitalWrite(Led,HIGH);
  }
  else
  {
    digitalWrite(Led,LOW);
  }
}
