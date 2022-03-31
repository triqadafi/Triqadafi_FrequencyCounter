#include <Triqadafi_FrequencyCounter.h>

// #define RASPBERRY_PICO_SSN 5
// #define STM32F103_SSN PA4
#define ARDUINO_NANO_SSN 10

#define MCU_PIN_SSN ARDUINO_NANO_SSN
#define MCU_PIN_INT 2

#define CHANNEL_MAX 8
Triqadafi_FrequencyCounter QCM_Array(MCU_PIN_SSN, 300000000);

volatile bool interrupt_flag;
void mcu_ISR() {
  interrupt_flag = true;
}

void setup() {
  QCM_Array.begin();

  Serial.begin(115200);
  Serial.println("QCM_Array - @triqadafi");

  // configure interrupt
  pinMode(MCU_PIN_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MCU_PIN_INT), mcu_ISR, RISING);
}

void loop() {
  if(interrupt_flag == true){
    interrupt_flag = false; // reset interrupt flag
    Serial.print("FI#0=");
    Serial.print("INDEX");
    Serial.print(";");
    for (int i = 0; i < CHANNEL_MAX; i++){
      double frequency = QCM_Array.frequencyRead(i);
      Serial.print(frequency, 3); 
      Serial.print(";");
    }
    Serial.println();
  }
}