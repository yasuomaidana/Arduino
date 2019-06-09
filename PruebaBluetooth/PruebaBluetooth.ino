int val;
 
void setup()
{
  Serial.begin(9600);
  delay(7000);
}
 
void loop()
{
  if(Serial.available() >= 1)
  {
    val = Serial.read();
  
    if(val == 'a')
    {
      analogWrite(11,50);
    }
    else if(val == 'i')
    {
      analogWrite(11,100);
    }
    else if(val == 's')
    {
      analogWrite(11,150);
    }
    else if(val == 'r')
    {
      analogWrite(11,200);
    }
    else if(val == 'd')
    {
      analogWrite(11,255);
    }
    else
    {
      analogWrite(11,0);
    }
  }
}
