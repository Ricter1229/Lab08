#include <LiquidCrystal.h> 
#include <Ultrasonic.h>
#define TRIGGER_PIN 4
#define ECHO_PIN 5
volatile boolean state=LOW;
const byte intPin=2;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
LiquidCrystal lcd(8, 9, 11, 12, 13, 14);

void setup() {
  pinMode(6,INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  attachInterrupt(intPin, int0, FALLING);
}
float cmMsec, inMsec;
long microsec;

void loop() {
  if(digitalRead(6) == LOW) {
    noInterrupts();
  }
  else {
    interrupts();
  } 
  Serial.print("MS: "); Serial.print(microsec);
  Serial.print(", CM: "); Serial.print(cmMsec);
  Serial.print(", IN: "); Serial.println(inMsec);
  lcd.print("MS:");  lcd.print(microsec);
  lcd.setCursor(0,1);
  lcd.print("CM:"); lcd.print(cmMsec);
  lcd.print(", IN:"); lcd.println(inMsec);
  delay(1000);
}
void int0() { //interrupt handler
  microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  lcd.clear();
}
