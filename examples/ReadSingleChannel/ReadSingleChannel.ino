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
  // CH_1 for channel 1
  // CH_2 for channel 2
  // CH_3 for channel 3
  // CH_4 for channel 4
  // CH_5 for channel 5
  // CH_6 for channel 6
  // CH_7 for channel 7
  // CH_8 for channel 8
  Serial.println(QCM_Array.frequencyRead(CH_1), 2); // 2 decimal places
  delay(1000);
}