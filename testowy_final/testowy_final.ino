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

volatile int i = 0;
unsigned int rpmtime;
float rpmfloat;
float rpm;
bool tooslow;

int a = 0;

volatile byte state = LOW;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

unsigned int obliczone = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(INTERRUPT_PIN, INPUT);
  //setup licznika
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12) | (1<<CS10); //Prescaler 1024
  TIMSK1 |= (1 << TOIE1); //enable timer overflow
  
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), przerwanie, FALLING); //konfiguracja przerwania
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  if (tooslow == 1) {
    Serial.println("Za wolno");
    lcd.setCursor(0,0); 
    lcd.write("Za wolno");
    delay(50);
  }
  else {
    float obliczRPM(rpmtime);
    rpm = round(rpmtime);

    Serial.print(rpm);
    Serial.print("  ");
    Serial.print(a);
    Serial.println();
    a++;
    lcd.setCursor(0,0); 
    lcd.write("RPM: "); 
    lcd.setCursor(0,1);
    lcd.print(rpm);
    delay(500);
    lcd.clear();
  }

}


ISR(TIMER1_OVF_vect) {
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
/*
{
  if(analogRead(ANALOG_PIN) < VREF) //analogRead zwraca wartości od 0 do 1024(5V) -> wirtualny przerzutnik schmitta
  {
  rpmtime = TCNT1; //wartość z licznika
  TCNT1 = 0; //zerowanie flagi
  tooslow = 0; //zerowanie flagi timer overflow
  } 
}
*/

// Przeliczanie czasu z licznika na wynik w RPM - by Kajetan Wierszelis 16.12.2021r
// Zalozono zegar 16 MHz / prescaler 1024 =  15 625 Hz czest przerwania
// czyli 1 tick = 64 us... ok
float obliczRPM(unsigned int rpmtime) {
  float obliczone = 0;
  // obliczone = 10^6 / (rpmtime * 64); // *64 to po prostu 2^6 czyli 6 bitshiftów w lewo
  // inaczej obliczone = 10^6/64 / rpmtime;
  obliczone = rpmtime / 15625; //baka, przecież to tak proste xd i wszystko sie miesci w 2 bajtach
  return obliczone;
}
