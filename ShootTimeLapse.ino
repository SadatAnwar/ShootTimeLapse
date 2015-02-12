/*
    Shoot Time Lapse photos with the help of Arduino
    @Author: Sadat
*/
 
//Declare all the needed variables
int toggleInputButton = 12;
int inputButton = 11; //Pin 11 will serve as input button
int shootButton = 10; // pin 10 will provide the op to the camera
int shootIndicator = 13; // Use the annoying LED as indicator that camera is exposed
int enter = 9; // Pin 9 will be the enter button, i.e. set the vaule

boolean readInput = true; // toggle to read time values  or shoot

long exposure = 0;
long timeLapse = 1000;

// the setup routine runs once when you press reset:
void setup() {     
  pinMode(shootIndicator, OUTPUT);
  digitalWrite(shootIndicator, LOW);  //shotch it off initially
  // initialize the digital pin as an output.
  pinMode(toggleInputButton, INPUT); 
  pinMode(inputButton, INPUT);  
  pinMode(enter, INPUT);  
  pinMode(shootButton, OUTPUT); 
  digitalWrite(shootButton, LOW); //initially not pressed
  
  Serial.begin(9600);  //debug
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("Ready!!");
  if(readInput){
    Serial.println("Waiting for Exposure values");
    readExposure();
    Serial.println("Waiting for Time Lapse values");
    readTimeLapse();
    readInput = !readInput;
  }else {
    Serial.print("Will be shooting pictures with exposeure :");
    Serial.print(exposure);
    Serial.print(" every : ");
    Serial.print(timeLapse/1000);
    Serial.println("seconds. Press enter to stop");
    takeAwesomeTimeLapse();
    readInput = !readInput;
  }
}

void readExposure(){ 
 while(true){
   if(digitalRead(inputButton)==HIGH){
     exposure += 1000; //every push will increase exposure by 1 sec
     Serial.print("Exposure value incresed to : ");
     Serial.println(exposure);
   }
   if(digitalRead(enter)==HIGH){
     return;
   }
 } 
  
}
void readTimeLapse(){
  while(true){
   if(digitalRead(inputButton)==HIGH){
     timeLapse += 10000; //every push will increase time lapse by 10 seconds
     Serial.print("Time Lapse value incresed to : ");
     Serial.println(timeLapse);
   }
   if(digitalRead(enter)==HIGH){
     return;
   }
 }
}

void takeAwesomeTimeLapse(){
  //loop till the enter button is pressed
  while(true){
    //Press the button
   digitalWrite(shootButton, HIGH);
   if(!delayForNextInstruction(exposure)){
     return;
   }
   //Release the button
   digitalWrite(shootButton,LOW);
   //Delay for timeLapse time and then repeat
   if(!delayForNextInstruction(timeLapse)){
     return;
   }
  }
}

boolean delayForNextInstruction(long delayDuration){
 unsigned long startTime = millis();
  unsigned long currentTime = millis();
  while((unsigned long)(currentTime-startTime) < delayDuration){
    if(digitalRead(enter)==HIGH){
      Serial.println("Enter button pressed, aborting!!");
      digitalWrite(shootButton,LOW); //close the exposure
     return false;
   }
    currentTime = millis();
  } 
  return true;
}
