void wyswietlRpm(unsigned int rpm)
{
lcd.clear();    //czyszczenie ekranu z wszelkich pozostałości
lcd.setCursor(0,0); //postawienie kursora w lewym gornym rogu LCD 
lcd.write("RPM: ");  // wyswietlenie 1. linijki tekstu
lcd.setCursor(0,1); //postawienie kursora w drugiej linijce
lcd.print(rpm); //wypisz wynik
delay(500); //delay zeby moc odczytac wynik
lcd.clear(); //po pół sekundy odśwież
}