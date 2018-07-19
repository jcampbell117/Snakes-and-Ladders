#include "Tunnel.h"

Tunnel::Tunnel() {};

Tunnel::Tunnel(string name, int x_loc, int y_loc, int x_tar, int y_tar)
{
	m_name = name;
	m_xLocation = x_loc;
	m_yLocation = y_loc;
	m_xTarget = x_tar;
	m_yTarget = y_tar;
}

bool Tunnel::isTrapLocation(const int &x, const int &y)
{
	if (x == m_xLocation && y == m_yLocation)
		return true;

	return false;
}

string Tunnel::getName()
{
	return m_name;
}

void Tunnel::teleportPlayer(int &x, int &y)
{
	x = m_xTarget;
	y = m_yTarget;
}