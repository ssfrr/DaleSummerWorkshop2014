#include <OneWire.h>
#include <DallasTemperature.h>

byte addr[8];
OneWire  oneWire(7);  // Connect your 1-wire device to pin 3
DallasTemperature sensor(&oneWire);
float tempC = 20.0;

void updateTemp()
{
  if(sensor.isConversionAvailable(addr))
  {
    tempC = sensor.getTempC(addr);
    sensor.requestTemperaturesByAddress(addr);
  }
}

void note(int freq, int length)
{
  long endTime = millis() + length * 200-50;
  while(millis() < endTime)
  {
    float freq_scale = 1 + (tempC-20)/4;
    //float freq_scale = 1;
    tone(3, (int)(freq * freq_scale));
  }
  noTone(3);
  delay(length*10);
  
  updateTemp();
}

void setup()
{
  Serial.begin(9600);
  discoverOneWireDevices();
  sensor.setResolution(addr, 9);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  
  sensor.requestTemperaturesByAddress(addr);
  updateTemp();
}

int DO = 262;
int RE = 294;
int MI = 330;
int FA = 349;
int SO = 392;
int LA = 440;
int TI = 494;
int DO2 = 523;

void loop()
{
  note(DO, 2);
  note(RE, 2);
  note(MI, 2);
  note(DO, 2);
  
  note(DO, 2);
  note(RE, 2);
  note(MI, 2);
  note(DO, 2);
  
  note(MI, 2);
  note(FA, 2);
  note(SO, 4);
  
  note(MI, 2);
  note(FA, 2);
  note(SO, 4);
  
  note(SO, 1);
  note(LA, 1);
  note(SO, 1);
  note(FA, 1);
  note(MI, 2);
  note(DO, 2);
  
  note(SO, 1);
  note(LA, 1);
  note(SO, 1);
  note(FA, 1);
  note(MI, 2);
  note(DO, 2);
  
  note(DO, 2);
  note(SO, 2);
  note(DO, 4);
  
  note(DO, 2);
  note(SO, 2);
  note(DO, 4);
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
