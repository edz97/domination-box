#include <LiquidCrystal.h>

const int buttonPinRed = 8; // input red button
const int buttonPinBlue = 9; // input blue button
const int outputPinRedLed = 10; // output red led
const int outputPinBlueLed = 11; // output blue led
const int outputPinGreenLed = 12; // output green led 

int buttonStateRed = 0; // to store value of button pushed or not
int buttonStateBlue = 0; // to store value of button pushed or not

String pointOwner = "Natural"; // used to derermine point owner can be value Red/Blue/Natural

int scoreRedTeam = 0; // score red team
int scoreBlueTeam = 0; // score blue team


int tick = 1000;  // tick rate of game 

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);



void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
  lcd.clear();

  pinMode(buttonPinRed, INPUT); // sets IO to input
  pinMode(buttonPinBlue, INPUT); // sets IO to input
  pinMode(outputPinRedLed, OUTPUT); // sets IO to output
  pinMode(outputPinBlueLed, OUTPUT); // sets IO to output
  pinMode(outputPinGreenLed, OUTPUT); // sets IO to output
}

void loop() 
{
  buttonStateRed = digitalRead(buttonPinRed); // checks if red button is pressed
  buttonStateBlue = digitalRead(buttonPinBlue); // checks if blue button is pressed
  buttonPressedUpdate(buttonStateRed, buttonStateBlue);
  scoreUpdate(pointOwner);
  screenUpdate(pointOwner);
  delay(tick);
}

void screenUpdate(String team)
{
  lcd.clear();
  lcd.print(team + " point");
  lcd.setCursor(0, 1); // moves cursor to colum 0 row 1
  lcd.print("Red");
  lcd.print(scoreRedTeam);
  lcd.print(" Blue");
  lcd.print(scoreBlueTeam);
}

void scoreUpdate(String team)
{
  if (team == "Red")
  {
    scoreRedTeam++;
  }
  else if (team == "Blue")
  {
    scoreBlueTeam++;
  }
}

void buttonPressedUpdate(int button1, int button2)
{
  if (button1 == HIGH & button2 == HIGH) // natural status
  {
    pointOwner = "Natural";
    digitalWrite(outputPinRedLed, LOW);
    digitalWrite(outputPinBlueLed, LOW);
    digitalWrite(outputPinGreenLed, HIGH);
  }
  
  else if (button1 == HIGH) // red status
  {
    pointOwner = "Red";   
    digitalWrite(outputPinRedLed, HIGH);
    digitalWrite(outputPinBlueLed, LOW);
    digitalWrite(outputPinGreenLed, LOW);
  }

  else if (button2 == HIGH) // blue status
  {
    pointOwner = "Blue";
    digitalWrite(outputPinRedLed, LOW);
    digitalWrite(outputPinBlueLed, HIGH);  
    digitalWrite(outputPinGreenLed, LOW);
  }
}