//Blinking a led
const int LED=13; //Led connected to
                  //digital pin 13  
void setup() 
{
  pinMode(LED,OUTPUT); //sets the digital 
                       //pin as output
}

void loop() 
{
 digitalWrite(LED,HIGH); //turns the led ON
 delay(1000); //waits for 500 miliseconds
 digitalWrite(LED,LOW); //turns the led OF
 delay(1000); //waits for 500 miliseconds
}
