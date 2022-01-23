# Welcome!
`Triqadafi Frequency Counter` - Handcrafted high resolution 8 channels frequency counter


## Compatible Hardware
### `UBFC-08RS` (XC6SLX9)
![Current Device](https://github.com/triqadafi/Triqadafi_FrequencyCounter/blob/master/images/device_cap-100.jpg?raw=true)
Spesifikasi:
- Total Channel: 8 (SMA footprint)
- Channel Input: 3.3 volt, DC, square wave (recommended)
- FPGA: Spartan 6E XC6SLX9
- Clock Source: OCXO/TCXO
- Clock Frequency: 100 MHz
- Input: 5V DC
- Communication Interface: SPI (Arduino Compatible)
- Flash Memory: W25Q 16MB
- Other: PLL Frequency (300 MHz Reciprocal Reference, 100 MHz Time Gate)

### `UBFC 08TS` (XC6SLX16)
- Coming soon!


# Download & Install

The library can be installed using the [standard Arduino library install procedure](http://arduino.cc/en/Guide/Libraries)

**OR** here some simple direction


- Save the [.zip file](https://github.com/triqadafi/Triqadafi_FrequencyCounter/releases/download/v1.0/Triqadafi_FrequencyCounter-1.0.zip) to your desktop,
- Open Arduino IDE
- Go to Menu > `Sketch > Include Library > Add .ZIP library...`
- Run some [example files](https://github.com/triqadafi/Triqadafi_FrequencyCounter/tree/master/examples) if you wish.


# Constructor
## Initialization

```c++
Triqadafi_FrequencyCounter QCM_Array(uint8_t PIN_SS, long reference_frequency);
```
**PIN_SS** merupakan pin Slave Select yang digunakan 
misal: 
- Arduino Nano => `D10`, 
- STM32 Bluepill => `PA4`,
- atau pin kosong lainnya juga dapat digunakan.

**reference_frequency** merupakan nilai frekuensi referensi
- default: `300000000` (berati 300,000,000 Hz = 300 MHz)
- nilai ini perlu dikalibrasi (tidak tepat di 300 MHz, tetapi di sekitar nilai tersebut)

Example:
```c++
Triqadafi_FrequencyCounter QCM_Array(PA4, 300000000);
```
Initialize the device (STM32 Bluepill), using pin PA4 as SS pin, and reference frequency 300 MHz.


## Methods
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
- atau dapat menggunakan integer `0-7` (mewakili channel 1-8)


```diff
- !! WARNING !!
```
Dikarenakan proses perhitungan memerlukan `double`, pastikan menggunakan mikrokontroler dengan arsitektur 32 bit atau mikrokontroler yang mendukung operasi double precission floating point. Hal sangat disarankan untuk sehingga nantinya menjadi sangat mudah.

Menggunakan `double` pada mikrokontroler 8 bit (Misal: Arduino Nano) akan sama dengan menggunakan `float`. Hal ini berarti menggunakan single precission sehingga akan kehilangan resolusi. Hal ini sebenarnya dapat diatasi dengan menggunakan ekstensi contohnya https://fp64lib.org/. Perlu dipahami dulu boss ~


# Example

## Pin Configuration
| Board Pin | Pin Function | Arduino (Common) | STM32 (Common) | | Raspberry Pico (Mbed Core)  | Raspberry Pico (Pico Core)
| ----------- | ----------- | ----------- | ----------- |
| 1 | SS_N | D10 | PA4 | 5 | 17 |
| 2 | MISO | D12 | PA6 | 4 | 16 |
| 3 | SCLK | D13 | PA5 | 2 | 18 |
| 4 | GND | GND | GND | GND | GND |
| 5 | MOSI | D11 | PA7 | 3 | 19 |
| 6 | INT | NC | NC | NC | NC |
| 7 | 5V | 5V | 5V | 5V | 5V |
**NB:** Pin INT (interrupt belum difungsikan untuk saat ini :wink:)

## Program

Read single channel every second (**STM32 Bluepill**)
```c++
#include <Triqadafi_FrequencyCounter.h>

Triqadafi_FrequencyCounter QCM_Array(PA4, 300000000); // SS_N, Reference Frequency 300MHz

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
Read All Channel every second (**STM32 Bluepill**)
```c++
#include <Triqadafi_FrequencyCounter.h>

Triqadafi_FrequencyCounter QCM_Array(PA4, 300000000); // SS_N, Reference Frequency 300MHz

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

# Troubleshooting :space_invader:
## Data tidak terbaca atau tidak berubah?
- pastikan LED kiri bawah berkedip dengan delay 1 detik.
- jika LED mati:
  - kemungkinan besar Board kekurangan daya.
  - gunakan power supply eksternal! 
- Salah satu kabel tidak terhubung!
- Salah koneksi pin!

# Other Things
- My Instagram: [@triqadafi](http://instagram.com/triqadafi)
- My Website: [triqada.fi](http://triqada.fi)

# SUWUN! :sparkling_heart:	
