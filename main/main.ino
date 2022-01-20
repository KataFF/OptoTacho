#include <LiquidCrystal.h>

//PINY od LCD
#define RS A0
#define EN A2
#define D4 A3
#define D5 A4
#define D6 11
#define D7 3

#define ANALOG_PIN A7
#define INTERRUPT_PIN 2
#define LED_PIN 13

#define VREF 100

unsigned int rpmtime;
float rpm;
bool tooslow;


LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

void setup()
{
  //setup licznika
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12) | (1<<CS10); //Prescaler 1024
  TIMSK1 |= (1 << TOIE1); //enable timer overflow
  
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), przerwanie, FALLING); //konfiguracja przerwania

  lcd.begin(16,2); //konfiguracja LCD
  lcd.clear();
  wyswietlInit();
}

void loop()
{
  lcd.clear();
  if (tooslow == 1)
  {
    wyswietlZaWolno();
  }
  else
  {
    rpm = obliczRPM(rpmtime);
    wyswietlRpm(rpm);
  }
}


ISR(TIMER1_OVF_vect)
{
 //kiedy cos kreci sie za wolno, i mamy timer overflow
  tooslow = 1;
}


void przerwanie() 
{
  if(analogRead(ANALOG_PIN) < VREF)
  {
  rpmtime = TCNT1; //wartość z licznika
  TCNT1 = 0; //zerowanie flagi
  tooslow = 0; //zerowanie flagi timer overflow
  }
}


// Przeliczanie czasu z licznika na wynik w RPM - by Kajetan Wierszelis 16.12.2021r
// Zalozono zegar 16 MHz / prescaler 1024 =  15 625 Hz czest przerwania
// czyli 1 tick = 64 us... ok
float obliczRPM(unsigned int rpmtime)
{
  float obliczone = 0;
  // obliczone = 10^6 / (rpmtime * 64); // *64 to po prostu 2^6 czyli 6 bitshiftów w lewo
  // inaczej obliczone = 10^6/64 / rpmtime;
  obliczone = 15625.0 / rpmtime;
  // Poniewaz powyszsza wartosc jest w Hertzach/Rotations Per Second, to
  obliczone *= 60;
  return obliczone;
}

void wyswietlInit()
{
  lcd.setCursor(0,0); //postawienie kursora w lewym gornym rogu LCD 
  lcd.write("Inicjalizacja..."); //wyswietl komunikat
  for(int i=0; i<16;i++) //LCD ma 16 znaków w jednym wierszu
  {
    lcd.setCursor(i,1); // wyswietl kropke w kazdym wierszu
    lcd.write(".");
    delay(100); //co 100 ms
  }
  delay(200); //odczekaj 
  lcd.clear(); //wyczysc
  lcd.setCursor(0,0); //kursor w lewym gornym rogu
  lcd.write("Inicjalizacja"); //wyswietl komunikat
  lcd.setCursor(1,5); //kursor na srodku dolnego wiersza
  lcd.write("zakonczona"); //wyswietl komunikat
  delay(1000); //odczekaj
}

void wyswietlZaWolno()
{
    lcd.setCursor(0,0); //postawienie kursora w lewym gornym rogu LCD 
    lcd.write("Za wolno"); //wyswietl komunikat
    delay(100); //poczekaj
    lcd.clear(); //odswiez
}

void wyswietlRpm(float rpm)
{
lcd.clear();    //czyszczenie ekranu z wszelkich pozostałości
lcd.setCursor(0,0); //postawienie kursora w lewym gornym rogu LCD 
lcd.write("RPM: ");  // wyswietlenie 1. linijki tekstu
lcd.setCursor(0,1); //postawienie kursora w drugiej linijce
lcd.print(rpm); //wypisz wynik
delay(500); //delay zeby moc odczytac wynik
lcd.clear(); //po pół sekundy odśwież
}
