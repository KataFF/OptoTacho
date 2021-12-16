#include <LiquidCrystal.h>

//PINY od LCD
#define rs 7
#define en 8
#define d4 9
#define d5 10
#define d6 11
#define d7 12

#define analog_pin A5
#define interruptPin 2
#define ledPin 13

volatile int i = 0;
unsigned int rpmtime;
float rpmfloat;
unsigned int rpm;


volatile byte state = LOW;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

#include "global.h"
#include "interrupt.h"  // Andrzej
#include "matma.c"      // Kajetan
//include "display.c"    // Jakub

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  //setup licznika
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12); //Prescaler 256
  TIMSK1 |= (1 << TOIE1); //enable timer overflow
  
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(interruptPin), przerwanie, FALLING);
  lcd.clear();
}

void loop() {
  digitalWrite(ledPin, state);
}
/*
void blink() {
  Serial.write("X; i=");
  Serial.write(i);
  Serial.println("");
  i++;
}*/
