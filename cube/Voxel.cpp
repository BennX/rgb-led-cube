#include "Voxel.h"

// default constructor
Voxel::Voxel() : x(0), y(0), z(0), color(Color()) {} //Voxel

Voxel::Voxel(const uint8_t x, const uint8_t y, const uint8_t z, const Color &c) : color(c)
{
	this->x = x % 5;
	this->y = y % 5;
	this->z = z % 5;
}

Voxel::Voxel(const Voxel &other) : color(other.color)
{
	this->x = other.x % 5;
	this->y = other.y % 5;
	this->z = other.z % 5;
}

// default destructor
Voxel::~Voxel()
{
} //~Voxel
