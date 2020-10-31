#include "Color.h"

const uint8_t Color::MAX_COLOR_RGB = 32;

Color::Color() : r(0), g(0), b(0)
{
}
// default constructor
Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = r % MAX_COLOR_RGB;
	this->g = g % MAX_COLOR_RGB;
	this->b = b % MAX_COLOR_RGB;
} //Color

Color::Color(const uint32_t &hex)
{
	this->b = (hex & 0xFF);
	b %= MAX_COLOR_RGB;
	this->g = ((hex >> 8) & 0xFF);
	g %= MAX_COLOR_RGB;
	this->r = ((hex >> 16) & 0xFF);
	r %= MAX_COLOR_RGB;
} //Color

bool Color::operator==(const Color &other) const
{
	return (r == other.r && g == other.g && b == other.b);
}

Color Color::operator+(const Color &other) const
{
	return Color(*this) += other; //return new
}

Color &Color::operator+=(const Color &other)
{
	r += other.r;
	if (r > MAX_COLOR_RGB)
		r = MAX_COLOR_RGB;

	g += other.g;
	if (g > MAX_COLOR_RGB)
		g = MAX_COLOR_RGB;

	b += other.b;
	if (b > MAX_COLOR_RGB)
		b = MAX_COLOR_RGB;
	return *this;
}

Color Color::operator-(const Color &other) const
{
	return Color(*this) -= other; //new
}

Color &Color::operator-=(const Color &other)
{
	if (r < other.r)
		r = 0;
	else
		r -= other.r;

	if (g < other.g)
		g = 0;
	else
		g -= other.g;

	if (b < other.b)
		b = 0;
	else
		b -= other.b;

	return *this;
}

Color Color::operator*(const Color &other) const
{
	return Color(*this) *= other; //new
}

Color &Color::operator*=(const Color &other)
{
	r = (r * other.r) % MAX_COLOR_RGB;
	g = (g * other.g) % MAX_COLOR_RGB;
	b = (b * other.b) % MAX_COLOR_RGB;
	//per convention return "yourself"
	return *this;
}

Color Color::operator/(const Color &other) const
{
	return Color(*this) /= other;
}

Color &Color::operator/=(const Color &other)
{
	r = (r / other.r) % MAX_COLOR_RGB;
	g = (g / other.g) % MAX_COLOR_RGB;
	b = (b / other.b) % MAX_COLOR_RGB;
	//per convention return "yourself"
	return *this;
}

Color Color::operator+(uint8_t i) const
{
	return Color(*this) += i; //ret new
}

Color &Color::operator+=(uint8_t i)
{
	return *this += Color(i, i, i);
}

Color Color::operator-(uint8_t i) const
{
	return Color(*this) -= i;
}

Color &Color::operator-=(uint8_t i)
{
	return *this -= Color(i, i, i);
}

Color Color::operator*(uint8_t i) const
{
	return Color(*this) *= i; //new
}

Color &Color::operator*=(uint8_t i)
{
	r = (r * i) % MAX_COLOR_RGB;
	g = (g * i) % MAX_COLOR_RGB;
	b = (b * i) % MAX_COLOR_RGB;
	//per convention return "yourself"
	return *this;
}

Color &Color::operator*=(const float &f)
{
	r *= f;
	r %= MAX_COLOR_RGB;
	g *= f;
	g %= MAX_COLOR_RGB;
	b *= f;
	b %= MAX_COLOR_RGB;
	return *this;
}

Color Color::operator*(const float &f) const
{
	return Color(*this) *= f; //return a new one
}

Color Color::operator/(uint8_t i) const
{
	//per convention return "yourself"
	return Color(*this) /= i;
}

Color &Color::operator/=(uint8_t i)
{
	r /= i;
	r %= MAX_COLOR_RGB;
	g /= i;
	g %= MAX_COLOR_RGB;
	b /= i;
	b %= MAX_COLOR_RGB;
	//per convention return "yourself"
	return *this;
}

Color Color::operator/(const float &f) const
{
	return Color(*this) /= f;
}

Color &Color::operator/=(const float &f)
{
	r /= f;
	r %= MAX_COLOR_RGB;
	g /= f;
	g %= MAX_COLOR_RGB;
	b /= f;
	b %= MAX_COLOR_RGB;
	//per convention return "yourself"
	return *this;
}
