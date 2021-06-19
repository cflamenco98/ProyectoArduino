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
         pinMode(_pinC,INPUT);       
      }
    
  bool ActivarSensorVibracion(){
    if(digitalRead(_pinC)){
      return 1;
    }else{
      return 0;
    }
  
  }

};


class Buzzer: public Componentes{
  public:
    Buzzer(byte _pinC):Componentes(_pinC){
     pinMode(_pinC, OUTPUT);
      digitalWrite(_pinC, HIGH);
    }

    bool ActivarBuzzer(bool activar) {
      if (activar == 1) {
        for (int i = 0; i < 2; i++) {
          digitalWrite(_pinC, LOW);
          delay(500);
          digitalWrite(_pinC, HIGH);
          delay(500);
        }
      } else {
        digitalWrite(_pinC, HIGH);
        delay(500);
      }
    }

};

//clase sensor de agua
class SensorAgua:public Componentes{
  public:
    SensorAgua(byte _pinC):Componentes(_pinC) {
      pinMode(_pinC, INPUT);
    }

    int GetNivelDeAgua() {
      return  analogRead(_pinC);
    }

};

//clase potenciometro para controlar vibraciones del motor
class potenciometro:public Componentes{
  public:
      potenciometro(byte _pinC):Componentes(_pinC){
            pinMode(_pinC,INPUT);
    }

    int getValor(){
      return analogRead(_pinC);
    }
    int getRango(){
      return rango;
    }
    private:
      const int rango=1023;
};


class motorVibracion:Componentes{
  public:
      motorVibracion(byte _pinC):Componentes(_pinC){
            pinMode(_pinC,OUTPUT);
      }

      void potencia(byte valor){
        if(valor > 100)
        {
          digitalWrite(_pinC, HIGH);
          delay(200);
        }
        else
        {
          digitalWrite(_pinC, LOW);
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
