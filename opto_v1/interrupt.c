#include "interrupt.h"
#define interruptPin 2
#define Vref 180 // 4,5V/5V * 1024 = 
//volatile j = 0;
bool tooslow = 1;

ISR(TIMER1_OVF_vect) {
 //kiedy cos kreci sie za wolno, i mamy timer overflow
  tooslow = 1;
}

void przerwanie() {
  //for(int i=0; i<5;i++){}//czekamy 5 cykli na ustabilizowanie wejścia
  //if(analogRead(analog_pin) < Vref) //analogRead zwraca wartości od 0 do 1024(5V) -> wirtualny przerzutnik schmitta
   //sprawdzamy czy nie było to zakłócenie
    
    //for(int i=0; i<5;i++){}//czekamy 5 cykli na ustabilizowanie wejścia
    
      if(analogRead(analog_pin) < Vref) //analogRead zwraca wartości od 0 do 1024(5V) -> wirtualny przerzutnik schmitta
      //TODO sprawdzic jakie napiecie mamy na input pinie (Vref)
      {
      rpmtime = TCNT1; //wartość z licznika
      TCNT1 = 0; //zerowanie flagi
      /*
      Serial.print("x ");
      Serial.print(j);
      Serial.print("  ");
      Serial.print(analogRead(analog_pin));
      Serial.println();
      j++;
      */
      }
  
  
}
