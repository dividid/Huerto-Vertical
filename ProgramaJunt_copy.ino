#include <Adafruit_ADS1X15.h>

//Parte de la humedad
int channelValueHumedad =0;
int sensorValue =0;
int humidityValue=0;

//Sensor de temperatura
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

//Función de la temperatura
float temperatura(int channelValue)
{
  // Captura una muestra del ADS1115

  int16_t adc0 = ads1115.readADC_SingleEnded(channelValue);

  // Aplicamos la formula de la temperatura en funcion de
  // la lectura digital

  float voltaje = (adc0 * 4.096/ 32767);
  float temperatura = ((voltaje-0.786)/0.034)-2;

  //Devolvemos el valor de la temperatura
  return temperatura;

}

//Función de la humedad
float humedad(int channelValue) 
{
  sensorValue=ads1115.readADC_SingleEnded(channelValue);
  humidityValue = map(sensorValue,2590,16090,100,0);

  Serial.print(humidityValue,DEC);

  if(sensorValue > 16200|| sensorValue <2400)
  {
    Serial.println("fora de rango");
  }
  
  //Devolvemos el valor de la humedad
  return humidityValue;

}

void loop() 
{
  //Llamada a la función de temperatura
  float resultadoTemp = temperatura(channelValueTemperatura);

  // Imprime la temperatura en el monitor serie
  Serial.print(resultadoTemp);
  Serial.println("Cº");

  //Llamada a la función de humedad
  float resultadoHume = humedad(channelValueHumedad);

  //Impresión en pantalla de la humedad 
  Serial.print("Humedad: ");
  Serial.print(resultadoHume);
  Serial.println("%");

  //Pequeño retraso antes de imprimir en pantalla
  delay(1000);

}