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

class motorVibracion{
  public:
      motorVibracion(byte _pin){
        pin=_pin;
            pinMode(pin,OUTPUT);
      }
    
      void potencia(byte valor, int rangoA[2]){
        digitalWrite(pin,adaptarValor(valor,rangoA));
      }
    private:
      byte pin;
      const byte rango[2]={0,1023};
      byte adaptarValor(int valor, int rangoAlt[2]){
        return map(valor,rangoAlt[0],rangoAlt[2],rangoAlt[0],rangoAlt[1]);
      }
};

potenciometro potVibra(A2);
motorVibracion mot1(A3);
motorVibracion mot2(A4);
int lectura;

void setup()
{
  Serial.begin(9600);  
}

void loop()

{
 lectura=potVibra.getValor();
 int rangoPot[2]={0,potVibra.getRango()};
 mot1.potencia(lectura,rangoPot);
 mot2.potencia(lectura,rangoPot);
 Serial.println(lectura); 
}
