/* 
* Proxy.h
*
* Created: 31.10.2020 19:02:08
* Author: benni
*/

#ifndef __PROXY_H__
#define __PROXY_H__

#include "Color.h"

class Proxy
{
private:
	uint8_t m_x, m_y, m_z;

	//functions
public:
	inline Color operator=(const Color &rgb);
	inline Proxy &set(uint8_t x, uint8_t y, uint8_t z);

}; //Proxy

#endif //__PROXY_H__
