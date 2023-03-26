#include <LiquidCrystal.h>

const int buttonPinRed = 8; // input red button
const int buttonPinBlue = 9; // input blue button
const int outputPinRedLed = 10; // output red led
const int outputPinBlueLed = 11; // output blue led 

int buttonStateRed = 0; // to store value of button pushed or not
int buttonStateBlue = 0; // to store value of button pushed or not

String pointOwner = "Natural"; // used to derermine point owner can be value Red/Blue/Natural

int scoreRedTeam = 0; // score red team
int scoreBlueTeam = 0; // score blue team


int tick = 1000;  // tick rate of game 

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);




/*********************************************************/

void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
  lcd.clear();

  pinMode(buttonPinRed, INPUT); // sets IO to input
  pinMode(buttonPinBlue, INPUT); // sets IO to input
  pinMode(outputPinRedLed, OUTPUT); // sets IO to output
  pinMode(outputPinBlueLed, OUTPUT); // sets IO to output
}

/*********************************************************/

void loop() 
{

  buttonStateRed = digitalRead(buttonPinRed);
  buttonStateBlue = digitalRead(buttonPinBlue);


  if (buttonStateRed == HIGH)
  {
    Serial.println("Red");
    //digitalWrite(7, HIGH);
    pointOwner = "Red";
    lcd.clear();
    lcd.print("Red owns point");
  }
  else {
    //digitalWrite(7, LOW);
  }

  if (buttonStateBlue == HIGH)
  {
    Serial.println("Blue");
    pointOwner = "Blue";
    lcd.clear();
    lcd.print("Blue owns point");

  }

  if (buttonStateRed == HIGH & buttonStateBlue == HIGH)
  {
    pointOwner = "Natural";
    lcd.clear();
    lcd.print("Point is natural");

  }
  lcd.clear();

  scoreUpdater(pointOwner);
  screenUpdater(pointOwner);
  delay(tick);

}

void screenUpdater(String team)
{

   
  lcd.print(team + " point");
  lcd.setCursor(0, 1);
  lcd.print("Red");
  lcd.print(scoreRedTeam);
  lcd.print(" Blue");
  lcd.print(scoreBlueTeam);

}

void scoreUpdater(String team)
{
  if (team == "Red") {
  scoreRedTeam++;
  }
  else if (team == "Blue") {
  scoreBlueTeam++;
  }
}




