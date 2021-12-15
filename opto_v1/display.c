#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

int wynik;

void setup()
{
lcd.begin(16, 2);
lcd.clear();
}

void loop()
{
lcd.setCursor(0,0); 
lcd.print("Obroty/minute: "); 
lcd.print(wynik);
delay(500); 
}
