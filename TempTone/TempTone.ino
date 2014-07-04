#include <OneWire.h>
#include <DallasTemperature.h>

byte addr[8];
OneWire  oneWire(7);  // Connect your 1-wire device to pin 3
DallasTemperature sensor(&oneWire);

void setup()
{
  Serial.begin(9600);
  discoverOneWireDevices();
  sensor.setResolution(addr, 9);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  
  sensor.requestTemperaturesByAddress(addr);
}

void loop()
{
  if(sensor.isConversionAvailable(addr))
  {
    float tempC = sensor.getTempC(addr);
    tone(3, 100 + tempC * 10);
    sensor.requestTemperaturesByAddress(addr);
  }
}

void discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  
  Serial.print("Looking for sensor address...\n\r");
  while(oneWire.search(addr)) {
    Serial.print("\n\rFound device with address:\n\r");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }
  }
  oneWire.reset_search();
  return;
}
