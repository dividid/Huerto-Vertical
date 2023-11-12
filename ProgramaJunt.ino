#include <Adafruit_ADS1X15.h>

//humedad
int channelValueHumedad =0;
int sensorValue =0;
int humidityValue=0;

//  sensor de temperatura
int channelValueTemperatura=1;

// Construimos el ADS1115
Adafruit_ADS1115 ads1115;

void setup() 
{
  // Inicializamos el monitor serie
  Serial.begin(9600);
  Serial.println("Inicializando el medidor de Temperatura");

  // Inicializamos el ADS1115
  ads1115.begin(0x48);

  // Configuramos la ganancia del ADS1115
  ads1115.setGain(GAIN_ONE);
}

float temperatura(int channelValue)
{

 // Captura una muestra del ADS1115
  int16_t adc0 = ads1115.readADC_SingleEnded(channelValue);

  // aplicamos la formula de la temperatura en funcion de
  // la lectura digital
  float voltaje = (adc0 * 4.096/ 32767);
  float temperatura = ((voltaje-0.786)/0.034)-2;

  return temperatura;
}

float humedad(int channelValue) 
{
  sensorValue=ads1115.readADC_SingleEnded(channelValue);
  humidityValue = map(sensorValue,150,990,100,0);

  Serial.print(humidityValue,DEC);
  if(sensorValue > 1000 || sensorValue <125)
  {
    Serial.println("fora de rango");
  }

  return humidityValue;
}

void loop() 
{
 
  float resultadoTemp = temperatura(channelValueTemperatura);

  // Imprime la temperatura en el monitor serie
  Serial.print(resultadoTemp);
  Serial.println("Cº");

  float resultadoHume = temperatura(channelValueHumedad);

  delay(1000);

  Serial.print("Humedad: ");
  Serial.print(resultadoHume);
  Serial.println("%");

  delay(1000);

}