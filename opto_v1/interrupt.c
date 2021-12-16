#include "interrupt.h"

ISR(TIMER1_OVF_vect) {
 //kiedy cos kreci sie za wolno, i mamy timer overflow
  tooslow = 1;
}


void przerwanie() {
  
  for(int i=0; i<5;i++){}//czekamy 5 cykli na ustabilizowanie wejścia
  if(analogRead(interrupt_pin) > Vref) //analogRead zwraca wartości od 0 do 1024(5V) -> wirtualny przerzutnik schmitta
  { //sprawdzamy czy nie było to zakłócenie
    
    for(int i=0; i<5;i++){}//czekamy 5 cykli na ustabilizowanie wejścia
    {
      if(analogRead(interrupt_pin) > Vref) //analogRead zwraca wartości od 0 do 1024(5V) -> wirtualny przerzutnik schmitta
      //TODO sprawdzic jakie napiecie mamy na input pinie (Vref)
      rpmtime = TCNT1; //wartość z licznika
      TCNT1 = 0; //zerowanie flagi
      tooslow = 0;
    }
  }
  
}
