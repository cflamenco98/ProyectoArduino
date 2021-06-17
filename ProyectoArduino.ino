

//clase para componente sensor de vibracion
class SensorVibracion {
  public:
    byte sensorPreviousValue = 0;
    byte sensorCurrentValue = 0;
    long lastTimeMoved = 0;
    byte shakeTime = 50;

    SensorVibracion(byte _pinS) {
      pinS = _pinS;
      pinMode(pinS, INPUT);
    }

    bool ActivarSensorVibracion() {
      if (digitalRead(pinS)) {
        return 1;
      } else {
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
    
      void potencia(byte valor, int rangoA[3]){
        analogWrite(pin,adaptarValor(valor,rangoA));
      }
    private:
      byte pin;
      const byte rango[3]={0,500,900};
      byte adaptarValor(int valor, int rangoAlt[3]){
        return map(valor,rangoAlt[0],rangoAlt[2],rangoAlt[0],rangoAlt[1]);
      }
};

//Instancias de objetos/variables globales
SensorVibracion sen(2);
Buzzer buzzer(8);
SensorAgua SensorAgua(A0);
potenciometro potVibra(A2);
motorVibracion mot1(8);
int lectura;


void setup() {
  Serial.begin(9600);
}

void loop() {
  sen.sensorCurrentValue = sen.ActivarSensorVibracion();

  if (sen.sensorPreviousValue != sen.sensorCurrentValue ) {
    sen.lastTimeMoved = millis();
    sen.sensorPreviousValue = sen.sensorCurrentValue;
  }

  //Logica para activar la alarma o buzzer
  if (millis() - sen.lastTimeMoved < sen.shakeTime) {
    Serial.println("MOVIMIENTO SISMICO DETECTADO");
    buzzer.ActivarBuzzer(1);
    delay(500);
  }
  else {
    buzzer.ActivarBuzzer(0);
    delay(500);
  }

  
  if(SensorAgua.GetNivelDeAgua() > 500)
  {
    Serial.println("ALERTA DE INUNDACION");
    buzzer.ActivarBuzzer(1);
    delay(500);
  }
  else
  {
    buzzer.ActivarBuzzer(0);
    delay(500);
  }

 lectura=potVibra.getValor();
 int rangoPot[2]={0,potVibra.getRango()};
 mot1.potencia(lectura,rangoPot);

}
