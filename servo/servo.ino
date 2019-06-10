#include <Servo.h>
//int button1 = 11; //button pin, connect to ground to move servo
int press1=0;
Servo servoMS3;


void setup()
{
//  pinMode(button1, INPUT);
  servoMS3.attach(7);
  Serial.begin(9600);

}

void loop()
{
  if(press1>180)
  {
    servoMS3.write(180);
    press1=0;
  }
    press1=press1+2;
    servoMS3.write(press1);
    Serial.println(press1);
    delay(100);
}
