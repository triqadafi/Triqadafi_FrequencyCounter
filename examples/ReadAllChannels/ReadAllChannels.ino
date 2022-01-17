#include <Triqadafi_FrequencyCounter.h>

Triqadafi_FrequencyCounter QCM_Array(PA4, 300000000);
// Using SS pin PA4 STM32 Bluepill
// Reference Frequency 300MHz

void setup() {
  QCM_Array.begin();

  Serial.begin(115200);
  Serial.println("QCM_Array - @triqadafi");
}

void loop() {
  // print all 8 channels
  for (int i = 0; i < 8; i++)
  {
    double freq = QCM_Array.frequencyRead(i);
    Serial.print(freq, 2); // 2 decimal places
    Serial.print(";");
  }
  Serial.println();

  delay(1000);
}