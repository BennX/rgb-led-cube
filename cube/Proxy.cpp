#include "Proxy.h"
#include "Cube.h"
#include "Voxel.h"

/*
RGB CubeProxy::operator()()
{
	return Cube::getInstance().getRGB(m_x, m_y, m_z);
}
*/

Proxy &Proxy::set(uint8_t x, uint8_t y, uint8_t z)
{
	m_x = x,
	m_y = y;
	m_z = z;
	return *this;
}

Color Proxy::operator=(const Color &rgb)
{
	return Cube::instance().set(Voxel(m_x, m_y, m_z, rgb));
}

