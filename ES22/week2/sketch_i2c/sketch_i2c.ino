#include <Wire.h>

#define ARDUINO_ADDRESS       (42)
#define ARDUINO_WRITE_ADDRESS (ARDUINO_ADDRESS << 1)
#define ARDUINO_READ_ADDRESS (ARDUINO_WRITE_ADDRESS  + 1)

void setup()
{
  Wire.begin(ARDUINO_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  Serial.println("Serial start");
}

void loop()
{
  delay(100);
}

int lastNumber = 0;
byte registers[2] = {0, 0};

void processRegister(char c)
{
  switch (c)
  {
    case 21:
    case 22:
      registers[c-21] = Wire.read();
      break;
  }
}

void receiveEvent(int howMany)
{
  while (Wire.available() > 1)
  {
    char c = Wire.read();
    processRegister(c);
    lastNumber = c;
    Serial.print(c);
  }
}

void requestEvent()
{
  switch(lastNumber)
  {
    case 23:
      Wire.write(min(registers[0], registers[1]));
      break;
    case 24:
      Wire.write(max(registers[0], registers[1]));
      break;      
  }  
}
