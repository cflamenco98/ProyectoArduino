#include <LiquidCrystal_I2C.h> //Include de libreria para utilizar pantalla LCD

//clase para componente sensor de vibracion
class SensorVibracion{
  public:
  
      SensorVibracion(byte _pinS){
        pinS = _pinS;
         pinMode(pinS,INPUT);
        
      }
    
  bool ActivarSensorVibracion(){
    if(digitalRead(pinS)){
      return 1;
    }else{
      return 0;
    }
  
  }
    private:
      byte pinS;
};

//clase para componente buzzer para emitir sonidos de alerta
class Buzzer {
  public:
    Buzzer(byte _pin) {
      pin = _pin;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
    }

    bool ActivarBuzzer(bool activar) {
      if (activar == 1) {
        for (int i = 0; i < 2; i++) {
          digitalWrite(pin, LOW);
          delay(500);
          digitalWrite(pin, HIGH);
          delay(500);
        }
      } else {
        digitalWrite(pin, HIGH);
        delay(500);
      }
    }
  private:
    byte pin;
};

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

//clase potenciometro para controlar vibraciones del motor
class potenciometro{
  public:
      potenciometro(byte _pin){
        pin=_pin;
            pinMode(pin,INPUT);
    }

    int getValor(){
      return analogRead(pin);
    }
    int getRango(){
      return rango;
    }
    private:
      byte pin;
      const int rango=1023;
};

//clase motor de vibracion
class motorVibracion{
  public:
      motorVibracion(byte _pin){
        pin=_pin;
            pinMode(pin,OUTPUT);
      }

      void potencia(byte valor){
        if(valor > 100)
        {
          digitalWrite(pin, HIGH);
          delay(200);
        }
        else
        {
          digitalWrite(pin, LOW);
          delay(200);
        }
        
      }
      
    private:
      byte pin;
      const byte rango[2]={0,1023};
      byte adaptarValor(int valor, int rangoAlt[2]){
        return map(valor,rangoAlt[0],rangoAlt[2],rangoAlt[0],rangoAlt[1]);
      }
};

//Instancias de objetos/variables globales
SensorVibracion sen(2);
Buzzer buzzer(8);
SensorAgua SensorAgua(A0);
potenciometro potVibra(A2);
motorVibracion mot1(9);
LiquidCrystal_I2C lcd(0x27,20,4);
int lectura;


void setup() {
  Serial.begin(9600);
  lcd.init();                   
  lcd.backlight();
}

void loop() {
 lectura=potVibra.getValor();
 mot1.potencia(lectura);

if(sen.ActivarSensorVibracion()){
  lcd.clear();
    lcd.print("SISMO, CORRE!!");
          buzzer.ActivarBuzzer(1);
   }else{
      Serial.println("Sensor desactivado");
        buzzer.ActivarBuzzer(0);
  }
  
  if(SensorAgua.GetNivelDeAgua() > 500)
  {
    lcd.clear();
    lcd.print("INUNDADO, CORRE!!");
    buzzer.ActivarBuzzer(1);
    delay(500);
  }
  else
  {
    buzzer.ActivarBuzzer(0);
    delay(500);
  }

}
