#ifndef __VOXEL_H__
#define __VOXEL_H__
#include "Vector.h"
#include "Color.h"

// A Voxel of the cube contains a color and one of the valid positions
class Voxel
{
	//variables
public:
	uint8_t x, y, z;
	Color color;

	//functions
public:
	// all zero Voxel
	Voxel();
	Voxel(const Voxel &c);
	// this method %5 all input to have it in safe range for the cube
	Voxel(const uint8_t x, const uint8_t y, const uint8_t z, const Color &);
	~Voxel();

protected:
private:
	Voxel &operator=(const Voxel &c);

}; //Voxel

#endif //__VOXEL_H__
