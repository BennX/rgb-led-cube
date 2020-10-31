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

