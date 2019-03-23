
#include <Firmata.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int previous=0;
byte send_data[]={2,48,48,48,48};


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
      if(i == 0){
        send_data[4]= 49;
      }
      else send_data[(i/2)]= 49;
    }
  }
  for ( byte i = 1; i < 8; i=i+2) {
    check_bit = (byte) (value >> i) & 1;
    if(check_bit == 1){
      if(i == 1){
        send_data[4]= 50;
      }
      send_data[(i-1)/2]= 50;
    }
  }
  mySerial.write(send_data,5);
  for(byte i = 1; i < 5; i++){
    send_data[i]=48;
  }
}

void digitalWriteCallback(byte port, int value)
{

  if (value!= 0 && value!= 1 && value!= 2 && value!= 4 && value!= 8 && value!= 16 &&
      value!= 32 && value!= 64 && value!= 128 && value != previous) {
//      analys_data(value);
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
  
}

void loop()
{
  while (Firmata.available()) {
    Firmata.processInput();
  }
}

