/*
   SigFox environment sensor

   Sketch collecting environmental data on a SmartEverything board

   Created: 2016/11/14
    Author: Alexandre Bouillot @abouillot
*/

#include <Arduino.h>
#include <Wire.h>

#include <HTS221.h> // temp + hum
#include <LPS25H.h> // pressure + ~temp
#include <VL6180.h> // light

#include <SmeSFX.h> // sigfox module

#define DEBUG_LOG 0

struct dataFrame {
  short hum;
  short temp1;
  short pressure;
  short temp2;
  long lux;
} ;

void setup() {
  // light the blue led to indicate start of initialisation
  ledBlueLight(HIGH);
  delay(1000);
#if (DEBUG_LOG)
  SerialUSB.begin(115200);
#endif
  //Initiate the Wire library and join the I2C bus
  Wire.begin();

  smeHumidity.begin();
  smePressure.begin();
  smeAmbient.begin();

  sfxAntenna.begin();

  delay(500);

  // switch off blue light, as initialisation is complete and succeed
  ledBlueLight(LOW);
}



// the loop function runs over and over again forever
void loop() {
  dataFrame data;

  data.hum = smeHumidity.readHumidity() * 100;
#if (DEBUG_LOG)
  SerialUSB.print("Humidity   : ");
  SerialUSB.print(data.hum);
  SerialUSB.println(" %");
#endif

  data.temp1 = smeHumidity.readTemperature() * 100;
#if (DEBUG_LOG)
  SerialUSB.print("Temperature: ");
  SerialUSB.print(data.temp1);
  SerialUSB.println(" celsius");
#endif

  data.pressure = smePressure.readPressure();
#if (DEBUG_LOG)
  SerialUSB.print("Pressure   : ");
  SerialUSB.print(data.pressure);
  SerialUSB.println(" mbar");
#endif

  data.temp2 = smePressure.readTemperature() * 100;
#if (DEBUG_LOG)
  SerialUSB.print("Temperature: ");
  SerialUSB.print(data.temp2);
  SerialUSB.println(" celsius");
#endif

  data.lux = smeAmbient.ligthPollingRead();
#if (DEBUG_LOG)
  SerialUSB.print("Light: ");
  SerialUSB.print(data.lux);
  SerialUSB.println(" lx");
#endif
  sfxAntenna.sfxSendData((char*) &data, sizeof(dataFrame));

  ledRedLight(HIGH);
  delay(100);

  ledRedLight(LOW);
  delay(10 * 60 * 1000);              // wait for 10 minutes

}
