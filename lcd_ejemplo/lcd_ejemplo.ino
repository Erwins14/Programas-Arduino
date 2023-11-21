#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
// La LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Iniciar LCD
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight(); // Agregar brillo
  // Limpiar
  lcd.clear();
  // Imprimir
  lcd.setCursor(0, 0);
  lcd.print("LCD y ESP8266");
  lcd.setCursor(4, 1); // Segunda fila
  lcd.print("SANDOVAL");
}

void loop()
{
  // put your main code here, to run repeatedly:
  
}
