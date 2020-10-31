/* 
* Cube.h
*
* Created: 31.10.2020 17:12:21
* Author: benni
*/

#ifndef __CUBE_H__
#define __CUBE_H__

#include <avr/io.h>
#include "Proxy.h"
#include "Color.h"
#include "Voxel.h"
#include "../util/spi.h"

#define MAX_COLOR 31

#define TO_STORAGE_PORT PORTC
#define TO_STORAGE_DDR DDRC
#define TO_STORAGE_PIN PORTC6

#define DISABLE_PORT PORTC
#define DISABLE_DDR DDRC
#define DISABLE_PIN PORTC7

class Cube
{
	// member
public:
protected:
	uint8_t m_colors[5][MAX_COLOR][10];
	Color m_cur_colors[5][5][5];
	//for SPI!
	uint8_t level;
	uint8_t cur_color_counter;

private:
	static Cube m_instance;
	Proxy m_proxy;

	//methods
public:
	static Cube &instance() { return m_instance; }
	// Returns the old color of the set voxel
	inline void render();
	inline void off();

	Color set(const Voxel &v);
	Proxy &operator()(uint8_t x, uint8_t y, uint8_t z);
	Color operator<<(Voxel v);

protected:
private:
	Cube();
	~Cube();
	Cube(const Cube &c);
	Cube &operator=(const Cube &c);
}; //Cube

void Cube::render()
{
	// DISABLE_LINE_PORT |= (1 << DISABLE_LINE_PIN); //set high to disable the register
	//*m_disable_port |= (1 << m_disable_pin_no);
	//reverse shift out
	for (int8_t i = 9; i >= 0; i--)
	{
		SPI::transmit(m_colors[level][cur_color_counter][i]);
	}

	cur_color_counter++;
	if (cur_color_counter >= MAX_COLOR)
	{
		cur_color_counter = 0;
		level++;
		if (level > 4)
		{
			level = 0;
		}
	}

	TO_STORAGE_PORT |= (1 << TO_STORAGE_PIN);
	TO_STORAGE_PORT &= ~(1 << TO_STORAGE_PIN);

	//*m_disable_port &= ~(1 << m_disable_pin_no); //set low to enable the register
}

#endif //__CUBE_H__
