#ifndef __COLOR_H__
#define __COLOR_H__
#include "avr/io.h"

class Color
{
public:
    // the values
    uint8_t r, g, b;

    //functions
public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);
    //constructor for hex values like
    // 0x000000
    // first 8 bit = r secon 8bit = g last 8bit = b
    explicit Color(const uint32_t &hex);

    //compare
    bool operator==(const Color &other) const;

    Color operator+(const Color &other) const;
    Color &operator+=(const Color &other);

    Color operator-(const Color &other) const;
    Color &operator-=(const Color &other);

    Color operator*(const Color &other) const;
    Color &operator*=(const Color &other);

    Color operator/(const Color &other) const;
    Color &operator/=(const Color &other);

    /**
     * Adds the value to all!
     */
    Color operator+(uint8_t i) const;
    Color &operator+=(uint8_t i);
    /**
    * subs the value to all!
    */
    Color operator-(uint8_t i) const;
    Color &operator-=(uint8_t i);

    /**
    * mult the value to all!
    */
    Color operator*(const float &f) const;
    Color &operator*=(const float &f);

    Color operator*(uint8_t i) const;
    Color &operator*=(uint8_t i);

    /**
    * div the value to all!
    */
    Color operator/(uint8_t i) const;
    Color &operator/=(uint8_t i);

    Color operator/(const float &f) const;
    Color &operator/=(const float &f);

private:
    static const uint8_t MAX_COLOR_RGB;

}; //Color

#endif //__COLOR_H__
