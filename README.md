# Welcome!
`Triqadafi Frequency Counter`  
Handcrafted 8 channel frequency counter


## Compatible Hardware
### `UBFC-08RS` (SPARTAN 6 L9)
![Current Device](https://github.com/triqadafi/Triqadafi_FrequencyCounter/blob/master/images/device_1.jpg?raw=true)
Spesifikasi:
- Total Channel: 8
- Channel Input: 3.3 volt square wave (recommended)
- FPGA: Spartan 6
- Clock Source: OCXO 100 MHz
- Input: 5V
- Communication Interface: SPI
- Flash Memory: W25Q 16Mbit
- Other: PLL Frequency (300 MHz Reference, 100 MHz Time Gate)

### `UBFC 08TS` (SPARTAN 6 L16)
- Coming soon!


# Download & Install

The library can be installed using the [standard Arduino library install procedure](http://arduino.cc/en/Guide/Libraries)

**OR** here some simple direction

- Save the .zip file to your desktop,
- Open Arduino IDE
- Go to Menu > `Sketch > Include Library > Add .ZIP library...`
- Run [example file](https://github.com/triqadafi/Triqadafi_FrequencyCounter/tree/master/examples) if you wish.


# Constructor

```c++
Triqadafi_FrequencyCounter QCM_Array(uint8_t PIN_SS, long reference_frequency);
```
**PIN_SS** merupakan pin Slave Select yang digunakan 
misal: 
- Arduino Nano => `D10`, 
- STM32 Bluepill => `PA4`,
- atau pin lainnya.

**reference_frequency** merupakan nilai frekuensi referensi
- default: `300000000` (berati 300,000,000 Hz = 300 MHz)
- nilai ini perlu dikalibrasi (tidak tepat di 300 MHz, tetapi di sekitar nilai tersebut)

Example:
```c++
Triqadafi_FrequencyCounter QCM_Array(10, 300000000);
```
Initialize the device, using pin D10 as SS pin, and reference frequency 300 MHz.


## Methods
-----------------------
### Begin
```c++
QCM_Array.begin();
```
Jangan lupa untuk dipanggil pada `setup()`

### Read Frequency (format data `double`)
```c++
QCM_Array.frequencyRead(channel);
```
Parameter **channel** 
- berisi nama channel yang ingin dibaca `CH_1` hingga `CH_8`
- atai dapat menggunakan integer `0-7` (mewakili channel 1-8)
```diff
- !! WARNING !!
Dikarenakan proses perhitungan memerlukan `double`, pastikan menggunakan mikrokontroler dengan arsitektur 32 bit atau mikrokontroler yang mendukung operasi double precission floating point. Hal sangat disarankan untuk sehingga nantinya menjadi sangat mudah.

Menggunakan `double` pada mikrokontroler 8 bit akan sama dengan menggunakan `float`. Hal ini berarti menggunakan single precission sehingga akan kehilangan resolusi. Hal ini sebenarnya dapat diatasi dengan menggunakan ekstensi contohnya https://fp64lib.org/. Perlu dipahami dulu boss ~
```


# Example
Read single channel every second
```c++
#include <Triqadafi_FrequencyCounter.h>

Triqadafi_FrequencyCounter QCM_Array(PB0, 300000000); // SS_N, Reference Frequency 300MHz

void setup() {
  QCM_Array.begin();
  Serial.begin(115200);
}

void loop() {
  double freq = QCM_Array.frequencyRead(CH_1);
  Serial.println(freq, 2);
  delay(1000);
}
```
----------
Read All Channel every second
```c++
#include <Triqadafi_FrequencyCounter.h>

Triqadafi_FrequencyCounter QCM_Array(PB0, 300000000); // SS_N, Reference Frequency 300MHz

void setup() {
  QCM_Array.begin();
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 8; i++)
  {
    double freq = QCM_Array.frequencyRead(i);
    Serial.print(freq, 2); 
    Serial.print(";");
  }
  Serial.println();
}
```


# Other Things
- My Instagram: [@triqadafi](http://instagram.com/triqadafi)
- My Website: [triqada.fi](http://triqada.fi)