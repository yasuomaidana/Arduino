//Turn on the led when the buttom is pressed and keep it after it is relased
const int led=13;
//const int led2=12;
const int buttom = 7;
int val=0;
int val_old=0;
int state=0;
void setup()
{
  pinMode(led,OUTPUT);
  //pinMode(led2,OUTPUT);
  pinMode(buttom,INPUT);
}

void loop() 
{
  val = digitalRead(buttom);
  if((val==HIGH)&&(val_old==LOW))
  {
    state=1-state;
    delay(10);
  }
  val_old=val;
  if (state==1)
  {
    digitalWrite(led,HIGH);
    //digitalWrite(led2,LOW);
  }
  else
  {
    digitalWrite(led,LOW);
    //digitalWrite(led2,HIGH);
  }
  if((val==LOW&&val_old==HIGH))
  {
    delay(10);
  }
}
