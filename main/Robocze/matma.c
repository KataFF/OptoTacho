// Przeliczanie czasu z licznika na wynik w RPM - by Kajetan Wierszelis 16.12.2021r
// Zalozono zegar 16 MHz / prescaler 1024 =  15 625 Hz czest przerwania
// czyli 1 tick = 64 us... ok
int obliczRPM(unsigned int rpmtime) {
  unsigned int obliczone = 2137;
  // obliczone = 10^6 / (rpmtime * 64); // *64 to po prostu 2^6 czyli 6 bitshiftów w lewo
  // inaczej obliczone = 10^6/64 / rpmtime;
  obliczone = 15625 / rpmtime; //baka, przecież to tak proste xd i wszystko sie miesci w 2 bajtach
  return obliczone;
}
