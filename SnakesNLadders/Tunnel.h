#pragma once
#include <string>
using namespace std;

class Tunnel
{
public:
	Tunnel();
	Tunnel(string name, int x_loc, int y_loc, int x_tar, int y_tar);
	bool isTrapLocation(const int &x, const int &y);
	void teleportPlayer(int &x, int &y);
	string getName();

private:
	string m_name;
	int m_xLocation, m_yLocation;
	int m_xTarget, m_yTarget;
};

