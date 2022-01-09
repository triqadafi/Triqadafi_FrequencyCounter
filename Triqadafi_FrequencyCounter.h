#include <Arduino.h>
#include <SPI.h>


#ifndef Triqadafi_FrequencyCounter_h
#define Triqadafi_FrequencyCounter_h

enum Triqadafi_Channels {
  CH_1,
  CH_2,
  CH_3,
  CH_4,
  CH_5,
  CH_6,
  CH_7,
  CH_8
};

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
     * @brief Fungsi untuk membaca nilai frekuensi pada channel
     * 
     * @param channel channel yang dibaca 0-7
     */
    double frequencyRead(uint8_t channel);
    double frequencyRead(int channel);
    double frequencyRead(Triqadafi_Channels channel);

    /**
     * @brief Inisialisasi
     * 
     */
    void begin();
    

  private:
    uint8_t _PIN_SS; /**< enum value TVal1. */  
    double _REFERENCE_FREQUENCY; /**< enum value TVal2. */  
    uint32_t readRegister(byte addr);
};
#endif