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

//creacion de los objetos de cada clase
SensorVibracion sen(2);
Led Roja(12);
Buzzer buzz(8);

//Variables globalizadas
byte sensorPreviousValue = 0;
byte sensorCurrentValue = 0;
long lastTimeMoved = 0;
byte shakeTime = 50;

//----

void setup() {
  Serial.begin(9600); 

}

void loop() {
  //Primera Opcion para el sensor de vibracion
  sensorCurrentValue = sen.ActivarSensorVibracion();
  
  if(sensorPreviousValue != sensorCurrentValue ){
    lastTimeMoved = millis();
      sensorPreviousValue = sensorCurrentValue;       
  }
  
  if(millis()-lastTimeMoved < shakeTime){
    //Logica para activar la alarma o buzzer
    Roja.EncerLed(1);
      buzz.ActivarBuzzer(1);
        delay(1500);
    }else{
      //logica para desactivar la alarma o buzzer
      Roja.EncerLed(0);
        buzz.ActivarBuzzer(0);
    } 

}
