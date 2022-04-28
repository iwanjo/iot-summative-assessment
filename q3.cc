//C++ Code
//Q3 Summative Assessment Implementation - Ian Kamanu Wanjohi
// include the library code
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(12,11,5,4,3,2);

// Initializing the pins used by the distance sensors relating to their position on the Arduino
#define pin1 8
#define pin2 13
#define pin3 7
#define pin4 10

//Initializing the buzzer
int buzzer = 6;
long time, distance, door1,door2;
void setup()
{
  // set up the LCD's number of columns and rows:
  
  lcd.begin(16,2);
  Serial.begin (9600);
  lcd.clear(); 
  //Pins used by distance sensor and buzzer
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, INPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(buzzer, LOW);
  // Print a message to the LCD with what the system is about
  lcd.setCursor(0,0);lcd.print("Home Security ");
  // set the cursor to column 0, line 1
  
  lcd.setCursor(0,1);lcd.print("System ");
  delay(1000);lcd.clear();
  
}

void loop() 
{

  Detect(pin1, pin2);
  door1 = distance;
  Detect(pin3, pin4);
  door2 = distance;
  digitalWrite(buzzer, LOW);
  Serial.print("D1:");Serial.println(door1); delayMicroseconds(50);
  Serial.print("D2:");Serial.println(door2);delayMicroseconds(50);

  lcd.setCursor(0,0);lcd.print("D1:");lcd.setCursor(4,0);lcd.print(door1);
  lcd.setCursor(9,0);lcd.print("D2:");lcd.setCursor(12,0);lcd.print(door2);
  delay(500);lcd.clear();

  if(door1 < 150) {
  
    digitalWrite(buzzer, HIGH);delay(200);
    Serial.print("Door 1:");Serial.println(door1); delayMicroseconds(50);
    lcd.setCursor(0,0);lcd.print("Door 1:");lcd.setCursor(7,0);lcd.print(door1);
    delay(500);lcd.clear();
  
  }
  
  if(door2 < 150) {
  
    digitalWrite(buzzer, HIGH);delay(200);
    Serial.print("Door 2:");Serial.println(door2); delayMicroseconds(50);
    lcd.setCursor(0,0);lcd.print("Door 2:");lcd.setCursor(7,0);lcd.print(door2);
    delay(500);lcd.clear();
  }
  
  

}
void Detect(int dpin,int dpin2)
{
  digitalWrite(dpin, LOW);
  delayMicroseconds(2);
  digitalWrite(dpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(dpin, LOW);
  time = pulseIn(dpin2, HIGH);
  distance = (time/2) / 29.1;

}