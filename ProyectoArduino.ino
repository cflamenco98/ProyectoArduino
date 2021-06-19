#include <LiquidCrystal_I2C.h> //Include de libreria para utilizar pantalla LCD

//Clase padre de los Componentes
class Componentes{
  public:
    Componentes(byte _pinC){
      pinC = _pinC;
    }
  protected:
    byte pinC;
};

class SensorVibracion : public Componentes{
  public: 
      SensorVibracion(byte _pinC):Componentes(_pinC){
         pinMode(pinC,INPUT);       
      }
    
  bool ActivarSensorVibracion(){
    if(digitalRead(pinC)){
      return 1;
    }else{
      return 0;
    }
  
  }

};

//clase buzzer para modulo que emite alarmas
class Buzzer : public Componentes{
  public:
    Buzzer(byte _pinC):Componentes(_pinC){
     pinMode(pinC, OUTPUT);
      digitalWrite(pinC, HIGH);
    }

    bool ActivarBuzzer(bool activar) {
      if (activar == 1) {
        for (int i = 0; i < 4; i++) {
          digitalWrite(pinC, LOW);
          delay(500);
          digitalWrite(pinC, HIGH);
          delay(500);
        }
      } else {
        digitalWrite(pinC, HIGH);
        delay(500);
      }
    }

};

//clase sensor de agua
class SensorAgua:public Componentes{
  public:
    SensorAgua(byte _pinC):Componentes(_pinC) {
      pinMode(pinC, INPUT);
    }

    int GetNivelDeAgua() {
      return  analogRead(pinC);
    }

};

//clase potenciometro para controlar vibraciones del motor
class potenciometro : public Componentes{
  public:
      potenciometro(byte _pinC):Componentes(_pinC){
            pinMode(pinC,INPUT);
    }

    int getValor(){
      return analogRead(pinC);
    }
    int getRango(){
      return rango;
    }
    private:
      const int rango=1023;
};

//clase motor de vibracion
class motorVibracion : public Componentes{
  public:
      motorVibracion(byte _pinC):Componentes(_pinC){
            pinMode(pinC,OUTPUT);
      }

      void potencia(byte valor){
        if(valor > 100)
        {
          digitalWrite(pinC, HIGH);
          delay(200);
        }
        else
        {
          digitalWrite(pinC, LOW);
          delay(200);
        }
        
      }
      
    private:
      //byte pin;
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
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Nivel actual");
 lcd.setCursor(1,1);
 lcd.print(SensorAgua.GetNivelDeAgua());

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
