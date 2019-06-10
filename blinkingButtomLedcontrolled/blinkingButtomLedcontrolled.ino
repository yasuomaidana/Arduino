//Control brightness with a button
const int Led=9;
const int But=7;

int val=0; //store the state of the input pin

int old_val=0; // store the previus value of val
int state=0; //led=0 off while led=1 on
int brightness=128; //store the brightness value
unsigned long startTime=0; //when did we begin pressing?

void setup() 
{
  pinMode(Led,OUTPUT);
  pinMode(But,INPUT);
}

void loop() 
{
  val=digitalRead(But);
  
  //Check if there was a transition
  if((val==HIGH)&&(old_val==LOW))
  {
    state=1-state;//Change to on or off
    startTime = millis(); //millis() is the arduino clock
                          //it returns how many milliseconds
                          //have passed since the board has been
                          //reset
    //this line remembers when the button was las pressed
    delay(10);
  }
  //Check if the button is being held on
  if((val==HIGH)&&(old_val==HIGH))
  {
    //If the buttom is held for more than 500 milliseconds
   if((state==1)&&((millis()-startTime)>500))
   {
     brightness++;
     delay(10); //delay to avoid brightness going up too fast
     if (brightness>255)
     {
      brightness=0; //255 is the max brightness
     }
   }
  }
  old_val=val; //val now is the old_val
  if(state==1)
  {
    analogWrite(Led,brightness);
  }
  else
  {
    analogWrite(Led,0);
  }
}
