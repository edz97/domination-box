#include <TM1637Display.h>
#include <Pushbutton.h>


// data pins for comunication 7 segment displays
#define DIO0 14 // display 0
#define CLK0 15 // display 0
#define DIO1 18 // display 1
#define CLK1 19 // display 1


TM1637Display display0(CLK0, DIO0); // red display
TM1637Display display1(CLK1, DIO1); // blue display


Pushbutton pushButtonRed(A0); // red button
Pushbutton pushButtonBlue(A1); // blue button
int tick = 1000; // tick rate of game in ms

int scoreRedTeam = 0; // score red team
int scoreBlueTeam = 0; // score blue team

String pointOwner = "Natrual"; // determines who is current owner of point

void lightUpdate(String color){
  if(color == "Red"){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);

  //internal led
  digitalWrite(10, LOW); // BLUE
  digitalWrite(11, HIGH); // RED
  }

  if (color == "Blue"){
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);

  //internal led
  digitalWrite(10, HIGH); // BLUE
  digitalWrite(11, LOW); // RED

  }
  
  if (color == "Natrual"){
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  
  //internal led
  digitalWrite(10, LOW); // BLUE
  digitalWrite(11, LOW); // RED
  }

}

bool redStatus = pushButtonRed.isPressed();
bool blueStatus = pushButtonBlue.isPressed();

void gameUpdate(){
  redStatus = pushButtonRed.isPressed();
  blueStatus = pushButtonBlue.isPressed();

  if(!redStatus & !blueStatus){
    pointOwner = "Natrual";
    lightUpdate(pointOwner);

  }
  else if(!redStatus){
    pointOwner = "Red";
    lightUpdate(pointOwner);

  }
  else if(!blueStatus){
    pointOwner = "Blue";
    lightUpdate(pointOwner);
  }

}

void scoreUpdate(){
  if (pointOwner == "Red"){
    scoreRedTeam++;
  }
  if (pointOwner == "Blue"){
    scoreBlueTeam++;
  }

  display0.showNumberDec(scoreRedTeam);
  display1.showNumberDec(scoreBlueTeam);



}



void setup() {
  Serial.begin(9600);

  // input buttons
  pinMode(A1, INPUT); // red
  pinMode(A0, INPUT); // blue
  
  // outgoing led strip pins
  pinMode(4, OUTPUT);  // red
  pinMode(5, OUTPUT);  // green
  pinMode(6, OUTPUT);  // blue
  pinMode(7, OUTPUT);  // white

  // internal led strip 1
  pinMode(8, OUTPUT);  // red
  pinMode(9, OUTPUT);  // green
  pinMode(10, OUTPUT); // blue

  // internal led strip 2
  pinMode(11, OUTPUT); // red
  pinMode(12, OUTPUT); // green
  pinMode(13, OUTPUT); // blue


  // boot up 7 segment displays
  display0.setBrightness(6); // red display
  display1.setBrightness(6); // blue display 

  display0.showNumberDec(0,true); // sets display to all 0 
  display1.showNumberDec(0, true); // sets display to all 0

  // led strip bootup
  digitalWrite(4, HIGH); // set red off
  digitalWrite(5, LOW); // set green on
  digitalWrite(6, HIGH); // set blue off
  digitalWrite(7, HIGH); // set white off

  //digitalWrite(8, HIGH);
  //digitalWrite(9, HIGH);
  digitalWrite(10, HIGH); // BLUE

  //digitalWrite(13, HIGH);
  digitalWrite(11, HIGH); // RED
  //digitalWrite(12, HIGH);
}

void loop() {
  gameUpdate();
  scoreUpdate();
  delay(tick);
}