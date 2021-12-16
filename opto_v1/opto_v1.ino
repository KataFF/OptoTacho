#include <LiquidCrystal.h>

#include "interrupt.h"  // Andrzej
#include "matma.c"      // Kajetan
#include "display.c"    // Jakub

int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
volatile int i=0;

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  Serial.write("X; i=");
  Serial.write(i);
  Serial.println("");
  i++;
}
