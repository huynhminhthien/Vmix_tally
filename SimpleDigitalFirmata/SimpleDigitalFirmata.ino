
#include <Firmata.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int previous=0,i=0;
byte send_data[]={1,48,48,48,48,59};


void setPinModeCallback(byte pin, int mode) {
  if (IS_PIN_DIGITAL(pin)) {
    pinMode(PIN_TO_DIGITAL(pin), mode);
  }
}

void analys_data(int value){
  
  byte check_bit;
  for ( byte i = 0; i < 7; i=i+2) {
    check_bit = (byte) (value >> i) & 1;
    if(check_bit == 1){
      send_data[(i/2)+1]= 49;
    }
  }
  for ( byte i = 1; i < 8; i=i+2) {
    check_bit = (byte) (value >> i) & 1;
    if(check_bit == 1){
      send_data[((i-1)/2)+1]= 50;
    }
  }
  mySerial.write(send_data,6);
  for(byte i = 1; i < 5; i++){
    send_data[i]=48;
  }
}

void digitalWriteCallback(byte port, int value)
{

  if (value!= 0 && value!= 1 && value!= 2 && value!= 4 && value!= 8 && value!= 16 &&
      value!= 32 && value!= 64 && value!= 128 && value != previous) {
      analys_data(value);

      mySerial.write(value);

      previous = value;
    }
}


void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);
  Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
  Firmata.attach(SET_PIN_MODE, setPinModeCallback);
  Firmata.begin(57600);
  mySerial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7,HIGH);
  
}

void loop()
{
  while (Firmata.available()) {
    Firmata.processInput();
  }
}

