#ifndef __PROXY_H__
#define __PROXY_H__

#include "Color.h"


class Proxy
{
private:
	uint8_t m_x, m_y, m_z;

	//functions
public:
	Color operator=(const Color &rgb);
	Proxy &set(uint8_t x, uint8_t y, uint8_t z);

}; //Proxy

#endif //__PROXY_H__
