# This is the code a 5x5x5 RGB LED Cube

## Hardware

- ATMega1285p-PU @22.1184MHz
- 10 74HC595 - 8 Bit Shift-Register
- 10 UDN2981 - 8 Channel Source Driver
- 1 74HC238 - Demuliplexer
- 5 IRL 1004 MOSFET
- FT232 RL for USB (Not using a bootloader - using an AVRISP mkii)

## Rough explanation on how it work

The Cube Class has a large Byte Array containing 5x32x10 Bytes which represent the colors states of the Cube. 

The representation is the following:

```
[level][color-map][byte state for the shift register] 
```

The current implementation can have up to 32 color steps for each color of the RGP spectrum which results in roughly 32768 different colors. So here is how the routine works.

Every 12khz an interup is executing the render method of the cube which renders the color-map of the current level by shifting the 10 bytes to the shift register and flipping the register into the new state. After shifting all 32 x 10byte values of one level, the level is incremented by one and it starts from the beginning again. 

Setting one color is done by setting the bit's on the level according to the given rgb value.

Simplified for an 8 value RGB on one stage the array for a single level looks like this:

```
[RGBRGBRG][BRGBRGBR]...
0. [00100000][00000000]...
1. [00100000][00000000]...
2. [01100000][00000000]...
3. [01100000][00000000]...
4. [11100000][00000000]...
5. [11100000][00000000]...
6. [11100000][00000000]...
7. [11100000][00000000]...
```

Which would mean, that the first LED has the state `(4,6,8)` resulting in 50% Red, 75% Green, and 100% Blue.

As the cube is capable of 32 color values, and frankly even more but it's hard to notice any difference, it has 32 array of it. 

This is multiplexed on the levels to prevent from having 5x5x5x3 single signales to PWM on. It is still reqired to have 5x5x3 channels for the PWM of the LED's and the last free 5 bit are used to set the mosfets for the levels resulting in the used 80bit.

One state of the 10byte shift register looks like this

```
[{5bit for the level}RGB][RGBRGBRG][BRGBRGBR][GBRGBRGB]...
```

Hilariously I added a demultiplexer for the levels, thus, it only requries 3 bit to drive activate/deactivate the 5 levels. That is not necessary. 

## Display

```
EA DOGM163S-A	1
EA LED55X31-W	1
```
- Controler: Controller ST7036


## Stückliste
```
AS 500APC	2
GS 18P	10
AT AVR ISP	1
AWG 28-40F 3M	1
DS 18B20	1
ATMEGA 1284P-PU	1
RAD FC 330/6,3	12
RAD FC 1.000/10	1
UDN 2981	11
74HC 595	12
74HC 238	1
USB BW	1
WSL 40G	2
PFL 40	2
WSL 20G	2
PFL 20	2
HEBW 21	1
FT 232 RL	1
KERKO 18P	2
BEL 200X150-2	1
IRL 1004	5
BEL 75X100-2	1
BS 170	1
METALL 10,0K	10
MPE 115-1-036	1
PS 25/5G WS	1
IRF 5305	1
EA DOGM163S-A	1
EA LED55X31-W	1
STEC11B03	1
GS-KO 16P	11
22,1184-HC18	1
DA 25MM	8
DI 8MM	8
TASTER 9302	1
SLK 3MM GN	5
METALL 100	10
METALL 1,00	30
METALL 3,30	30
METALL 39,0	30
L-MICC 10?	1
TL 36 P0	4
```