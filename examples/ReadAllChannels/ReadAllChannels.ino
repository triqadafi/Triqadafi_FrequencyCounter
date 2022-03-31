#include <Triqadafi_FrequencyCounter.h>

#define MAIN_PERIOD 1000
#define CHANNEL_MAX 8

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
  for (int i = 0; i < CHANNEL_MAX; i++) {
    double frequency = QCM_Array.frequencyRead(i);
    Serial.print(frequency, 3); // 3 decimal places
    Serial.print(";");
  }
  Serial.println();

  delay(MAIN_PERIOD);
}