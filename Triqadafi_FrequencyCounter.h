#include <Arduino.h>
#include <SPI.h>


#ifndef Triqadafi_FrequencyCounter_h
#define Triqadafi_FrequencyCounter_h

/**
 * @brief test coba coba tentang brief
 * 
 * dibawahnya ini harusnya comment
 * 
 */
class Triqadafi_FrequencyCounter
{
  public:
    /**
     * @brief Construct a new Triqadafi_FrequencyCounter object
     * 
     * @param PIN_SS PIN Slave Select yang digunakan
     * @param reference_frequency Frekuensi Referen sistem Frequency Counter
     */
    Triqadafi_FrequencyCounter(uint8_t PIN_SS, long reference_frequency);

    /**
     * @brief Fungsi untuk mengatur sinyal input ke TEC berupa sinyal PWM
     * 
     * @param channel channel yang dibaca 0-7
     */
    double frequencyRead(uint8_t channel);

    /**
     * @brief Inisialisasi pin dan konfigurasi pin PWM mikrokontroler
     * 
     */
    void begin();
    

  private:
    uint8_t _PIN_SS; /**< enum value TVal1. */  
    double _REFERENCE_FREQUENCY; /**< enum value TVal2. */  
    uint32_t readRegister(byte addr);
};
#endif