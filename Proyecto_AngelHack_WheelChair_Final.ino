#include <Servo.h>
Servo myservo;  // create servo object to control a servo 
 // a maximum of eight servo objects can be created 

int pos = 90;    // variable to store the servo position 
const int maxDeg = 160;
const int minDeg = 5;

const int leftPin = 3;
const int rightPin = 2;

const int led1Pin = 6; // indicator
const int led2Pin = 5; // indicator

const int outputPin = 9; // pwm function will be disabled on pin 9 and 10 if using servo

int leftPressed = 0;
int rightPressed = 0;
int currentPos =0;

int leftSet = 0;
int rightSet =0;
int noneSet =0;

String comandoEntrada = "";
boolean comandoCompleto = false;

void setup() 
{ 
  Serial.begin(9600);
  
myservo.attach(outputPin);  // attaches the servo on pin 9 to the servo object 
comandoEntrada.reserve(200);
pinMode(leftPin, INPUT);
pinMode(rightPin, INPUT);
pinMode(led1Pin, OUTPUT);
pinMode(led2Pin, OUTPUT);
} 



void goingUp(){
   pos = pos + 3;
   myservo.write(pos);
   setLeds(true,false); 
   delay(200);  
}

void goingDown(){
   pos = pos - 3;
   myservo.write(pos);
   setLeds(false,true);
   delay(200); 
}

void stoping(){
   pos = 90;
   myservo.write(90);
   setLeds(false,false);
   delay(10);
}

void loop() 
{ 
    leftPressed = digitalRead(leftPin);
    rightPressed = digitalRead(rightPin);
 
     if(leftPressed)
     {
      goingUp();
     }
     else if(rightPressed)
     {
      goingDown();
     }else{
       if(leftSet){
         goingUp();
         delay(10);
       }
       if(rightSet){
         goingDown();
         delay(10);
       }
       
       if(rightSet==leftSet){
         stoping();
         
       }
     }
     

     if(comandoCompleto){
      if(comandoEntrada.compareTo("up\n")==0){
         leftSet =1;
         rightSet=0;
      }else if(comandoEntrada.compareTo("down\n")==0){
        leftSet =0;
         rightSet=1;
      }else if(comandoEntrada.compareTo("stop\n")==0){
        leftSet =0;
         rightSet=0;
      }
     }    
     
     comandoCompleto=false;
     comandoEntrada="";

}
void setLeds(boolean led1, boolean led2){
  if(led1 == true){
    digitalWrite(led1Pin,HIGH);
  }else{
    digitalWrite(led1Pin,LOW);
  }
  if(led2 == true){
    digitalWrite(led2Pin,HIGH);
  }else{
    digitalWrite(led2Pin,LOW);
  }
}

void moveLeft(int pos){
  myservo.write(pos);
}

void moveRight(int pos){
  myservo.write(pos);
}

void stop(int pos){
  myservo.write(pos);
}

void serialEvent(){
  while(Serial.available()){
   
   char inChar = (char)Serial.read();
   Serial.print(inChar);
   comandoEntrada +=inChar;
   if(inChar == '\n'){
    comandoCompleto=true; 
   }
  }
}
