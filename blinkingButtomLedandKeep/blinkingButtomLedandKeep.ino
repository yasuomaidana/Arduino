//Turn on the led when the buttom is pressed and keep it after it is relased
const int led=13;
const int buttom = 7;
int val=0;
int state=0;
void setup()
{
  pinMode(led,OUTPUT);
  pinMode(buttom,INPUT);
}

void loop() 
{
  val = digitalRead(buttom);
  if(val==HIGH)
  {
    state=1-state;
  }
  if (state==1)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
}
