#include <LiquidCrystal_I2C.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip

//clase sensor de agua
class SensorAgua {
  public:
    SensorAgua(byte _analogPin) {
      analogPin = _analogPin;
      pinMode(analogPin, INPUT);
    }

    int GetNivelDeAgua() {
      return  analogRead(analogPin);
    }

  private:
    byte analogPin;
};

//Instancias de objetos
LiquidCrystal_I2C lcd(0x20, 16, 2);
SensorAgua SensorAgua(A0);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop()
{
  lcd.display();
  lcd.print("Nivel de agua actual: " + SensorAgua.GetNivelDeAgua());
}
