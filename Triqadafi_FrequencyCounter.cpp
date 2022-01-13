#include "Triqadafi_FrequencyCounter.h"

Triqadafi_FrequencyCounter::Triqadafi_FrequencyCounter(uint8_t PIN_SS, long reference_frequency){
  _PIN_SS = PIN_SS;
  _REFERENCE_FREQUENCY = reference_frequency;
}

void Triqadafi_FrequencyCounter::begin(){
  SPI.begin();
  pinMode(_PIN_SS, OUTPUT);
  digitalWrite(_PIN_SS,HIGH);
}

double Triqadafi_FrequencyCounter::frequencyRead(uint8_t channel){
	unsigned long chx = readRegister(0b00010000 | channel);
	unsigned long ref = readRegister(0b00100000 | channel);
  // Serial.println(chx);
  // Serial.println(ref);
  if(ref == 0){
    return 0;
  }else{
    return chx*_REFERENCE_FREQUENCY/ref;
  }
}
double Triqadafi_FrequencyCounter::frequencyRead(int channel){
  return frequencyRead((uint8_t)channel);
}
double Triqadafi_FrequencyCounter::frequencyRead(Triqadafi_Channels channel){
  return frequencyRead((uint8_t)channel);
}

uint32_t Triqadafi_FrequencyCounter::readRegister(byte addr){
  digitalWrite (_PIN_SS, LOW);        // reset Slave Select
  SPI.transfer(addr);  // instruction byte
  uint32_t a = SPI.transfer(0);  // do a transfer
  uint32_t b = SPI.transfer(0);  // do a transfer
  uint32_t c = SPI.transfer(0);  // do a transfer
  uint32_t d = SPI.transfer(0);  // do a transfer
  digitalWrite (_PIN_SS, HIGH);       //-set Slave Select
  delay(1);
  return d|(c<<8)|(b<<16)|(a<<24);
}
