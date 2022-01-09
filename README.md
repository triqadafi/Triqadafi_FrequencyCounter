# Welcome to the Family!
`Frequency Counter`  

## Device `(SPARTAN 6)`
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



## Inisialisasi
```c++
Triqadafi_FrequencyCounter QCM_Array(uint8_t PIN_SS, long reference_frequency);
```
**PIN_SS** merupakan pin Slave Select yang digunakan 
misal: 
- Arduino Nano => `D10`, 
- STM32 Bluepill => `PA4`,
- atau pin digital lainnya.

**reference_frequency** nilai ini digunakan untuk kalibrasi
- default: `300000000` (frekuensi referensi yang digunakan)

## Setup
```c++
QCM_Array.begin();
```
Jangan lupa untuk dipanggil pada `setup()`

## Pembacaan
```c++
QCM_Array.frequencyRead(channel);
```
Format data `double`

**channel** 
- merupakan nama channel yang ingin dibaca `CH_1` hingga `CH_8`
- dapat menggunakan integer `0-7`