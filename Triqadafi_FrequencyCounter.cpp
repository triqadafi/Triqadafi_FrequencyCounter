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
	unsigned long chx = readRegister(FI_REGISTER_READ | FI_REGISTER_CHANNEL | channel);
	unsigned long ref = readRegister(FI_REGISTER_READ | FI_REGISTER_REFERENCE | channel);
  // Serial.print(chx);
  // Serial.print(";");
  // Serial.print(ref);
  // Serial.print(";");
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
bool Triqadafi_FrequencyCounter::getACK(){
  uint32_t result = readRegister(FI_REGISTER_ACK);
  if (result == 200) return true;
  return false;
}
uint32_t Triqadafi_FrequencyCounter::getDeviceID(){
  uint32_t result = readRegister(FI_REGISTER_READ | FI_REGISTER_DEVICE_ID);
  return result;
}
void Triqadafi_FrequencyCounter::setGatePeriodMS(unsigned long period){
  unsigned long gate_frequency_hz = 100000000;
  unsigned long gate_period_half = gate_frequency_hz/2;
  float period_ms_to_s = period / 1000.0;
  unsigned long result = period_ms_to_s * gate_period_half;

  writeRegister(0b10000001, result);
}

void Triqadafi_FrequencyCounter::writeRegister(byte addr, uint32_t value){
  digitalWrite(_PIN_SS, LOW);
  SPI.transfer(addr);  // instruction byte
  SPI.transfer((value >> 24) & 0xFF);
  SPI.transfer((value >> 16) & 0xFF);
  SPI.transfer((value >> 8) & 0xFF);
  SPI.transfer((value >> 0) & 0xFF);
  digitalWrite(_PIN_SS, HIGH);
  delay(1);
}

uint32_t Triqadafi_FrequencyCounter::readRegister(byte addr){
  uint32_t result = 0;
  uint8_t temp;

  digitalWrite(_PIN_SS, LOW);
  SPI.transfer(addr);  // instruction byte
  // Split Request into 8-bit sections and sending them one byte at a time
  // uint8_t checkbyte = SPI.transfer(0x00);
  // if(checkbyte != 0 ) Serial.println("Byte Error");
  temp = SPI.transfer(0x00);
  result = temp;
  temp = SPI.transfer(0x00);
  result = (result << 8) | temp;
  temp = SPI.transfer(0x00);
  result = (result << 8) | temp;
  temp = SPI.transfer(0x00);
  result = (result << 8) | temp;

  digitalWrite(_PIN_SS, HIGH);
  delay(1);
  return (result);
}