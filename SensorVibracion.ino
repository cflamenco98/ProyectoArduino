//clase para componente sensor de vibracion
class SensorVibracion{
  public:
      byte sensorPreviousValue = 0;
      byte sensorCurrentValue = 0;
      long lastTimeMoved = 0;
      byte shakeTime = 50;
  
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

class Buzzer{
  public:
  Buzzer(byte _pin){
    pin = _pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin,HIGH);
  }
  
  bool ActivarBuzzer(bool activar){
     if(activar == 1){
      for(int i=0; i<4; i++){
        Serial.println("Activado");
        digitalWrite(pin,LOW);
        delay(1000);
        digitalWrite(pin,HIGH);
        delay(1000);
    }
    }else{   
        Serial.println("Desactivado");
        digitalWrite(pin,HIGH);
        delay(1000);
    
    }
  }
  private:
  byte pin;

};

SensorVibracion sen(2);
Buzzer buzzer(8);


void setup() {
  Serial.begin(9600);
}

void loop() {
  sen.sensorCurrentValue = sen.ActivarSensorVibracion();
  
  if(sen.sensorPreviousValue != sen.sensorCurrentValue ){
    sen.lastTimeMoved = millis();
      sen.sensorPreviousValue = sen.sensorCurrentValue;       
  }
  
  if(millis()-sen.lastTimeMoved < sen.shakeTime){
    //Logica para activar la alarma o buzzer
    Serial.println("activado");
      buzzer.ActivarBuzzer(1);
  }else{
        Serial.println("Desactivado");
          buzzer.ActivarBuzzer(0);
        
    }


    
}
