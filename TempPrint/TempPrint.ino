#include <OneWire.h>
#include <DallasTemperature.h>

byte addr[8];

OneWire  oneWire(7);  // Connect your 1-wire device to pin 3
DallasTemperature sensor(&oneWire);

void setup(void) {
  Serial.begin(9600);
  discoverOneWireDevices();
  sensor.setResolution(addr, 9);
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

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensor.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print("C: ");
    Serial.print(tempC);
    Serial.print(" F: ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
  }
}

void loop(void) {
  //delay(2000);
  //Serial.print("Getting temperature...\n\r");
  sensor.requestTemperaturesByAddress(addr);
  
  //Serial.print("Temperature is: ");
  printTemperature(addr);
  Serial.print("\n\r");
}
