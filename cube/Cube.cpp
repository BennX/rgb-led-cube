#include "Cube.h"
#include <string.h>

Cube Cube::m_instance;

// default constructor
Cube::Cube() : level(0), cur_color_counter(0)
{
	SPI::init(); //init the spi
	off();

	//enabel output on ss and latch pins
	TO_STORAGE_DDR |= (1 << TO_STORAGE_PIN);
	DISABLE_DDR |= (1 << DISABLE_PIN);
	// pull the disable pin to low to enable the register
	DISABLE_PORT &= ~(1 << DISABLE_PIN);
} //Cube

// default destructor
Cube::~Cube() {} //~Cube

void Cube::off()
{
	memset(m_colors, 0, sizeof(m_colors));
	for (uint8_t i = 0; i < MAX_COLOR; i++)
	{
		//maybe reverse
		m_colors[0][i][0] = 0x04; //
		m_colors[1][i][0] = 0x03; //
		m_colors[2][i][0] = 0x02; //
		m_colors[3][i][0] = 0x01; //
		m_colors[4][i][0] = 0x00; //
	}
}

Color Cube::set(const Voxel &v)
{
	Color old = m_cur_colors[v.x][v.y][v.z];
	if (old == v.color) // if no new skip setting
		return old;

	// save new value
	m_cur_colors[v.x][v.y][v.z] = v.color;

	//update colors
	uint8_t pos = v.x * 3 + v.z * 15 + 5; // first bit are level bits

	//+0
	uint8_t rbyte = pos / 8;
	uint8_t rbit = pos % 8;
	//+1
	uint8_t gbyte = (pos + 1) / 8;
	uint8_t gbit = (pos + 1) % 8;
	//+2
	uint8_t bbyte = (pos + 2) / 8;
	uint8_t bbit = (pos + 2) % 8;

	for (uint8_t i = 0; i < MAX_COLOR; i++)
	{
		if (i < v.color.r)
		{
			m_colors[v.y][i][rbyte] |= 1 << rbit; //set all to 1 till r
		}
		else
		{
			//bitwise not = ~ ! (invert with &)
			m_colors[v.y][i][rbyte] &= ~(1 << rbit); //set all other to 0
		}
		if (i < v.color.g)
		{
			m_colors[v.y][i][gbyte] |= 1 << gbit; //set all to 1 till r
		}
		else
		{
			m_colors[v.y][i][gbyte] &= ~(1 << gbit); //set all other to 0
		}
		if (i < v.color.b)
		{
			m_colors[v.y][i][bbyte] |= 1 << bbit; //set all to 1 till r
		}
		else
		{
			m_colors[v.y][i][bbyte] &= ~(1 << bbit); //set all other to 0
		}
	}
	return old;
}

Proxy &Cube::operator()(uint8_t x, uint8_t y, uint8_t z)
{
	return m_proxy.set(x, y, z);
}

Color Cube::operator<<(Voxel v)
{
	return Cube::set(v);
}