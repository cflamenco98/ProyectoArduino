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

potenciometro potVibra(A2);
motorVibracion mot1(8);
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
 Serial.println(lectura); 
}