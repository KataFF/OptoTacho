#include<LiquidCrystal.h>

/*
//PINY od LCD
int RS =A0;
int EN =A1;
int D4 =A2;
int D5 =A3;
int D6 =A4;
int D7 =5;
*/

//NOWE
#define RS A0
#define EN A2
#define D4 A3
#define D5 A4
#define D6 11
#define D7 3



/*
int RS=7;
int EN=8;
int D4=9;
int D5=10;
int D6=A1;
int D7=A0;
*/
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
lcd.setCursor(0,0);
lcd.print("Test projektu");
lcd.setCursor(0,1);
lcd.print("Optoelektronika 2");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Stodolski Wiersz");
lcd.setCursor(0,1);
lcd.print("-elis Malolepszy");
delay(2000);
lcd.clear();
}
