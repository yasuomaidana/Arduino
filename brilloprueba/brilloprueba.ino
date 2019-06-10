int i=0;
void setup() 
{
  pinMode(13,OUTPUT);
}

void loop() 
{
  for(i=0;i<255;i++)
  {
    analogWrite(13,i);
    delay(10);
  }
    for(i=255;i>255;i--)
  {
    analogWrite(13,i);
    delay(10);
  }
}
