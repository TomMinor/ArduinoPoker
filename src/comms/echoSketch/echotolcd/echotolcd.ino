#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.clear();
}

void loop() {
   /*  check if data has been sent from the computer: */
  if (Serial.available()) {
    /* read the most recent byte */
    Byte byteRead = Serial.read();
    /*ECHO the value that was read, back to the serial port. */
    Serial.write(byteRead);
    lcd.print(byteRead);
  }
}
