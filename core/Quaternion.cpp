#include "Quaternion.h"

Quaternion::Quaternion():
	x(0.),
	y(0.),
	z(0.),
	w(0.)
{
}

Quaternion::Quaternion(double ax, double ay, double az, double aw):
	x(ax),
	y(ay),
	z(az),
	w(aw)
{
}

Quaternion::~Quaternion()
{
}

double Quaternion::Length2(void)
{
	return x*x + y*y + z*z + w*w;
}

Quaternion Quaternion::operator+(const Quaternion &q) const
{
	return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion &q) const
{
	return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::operator*(const Quaternion &q) const
{
	return Quaternion(x*q.x - y*q.y - z*q.z - w*q.w,
					  x*q.y + y*q.x + z*q.w - w*q.z,
					  x*q.z - y*q.w + z*q.x + w*q.y,
					  x*q.w + y*q.z - z*q.y + w*q.w);
}

Quaternion Quaternion::operator*(double n) const
{
	return Quaternion(x*n, y*n, z*n, w*n);
}

Quaternion Quaternion::operator=(Quaternion q)
{
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
	this->w = q.w;
	return *this;
}

double Quaternion::GetX(void) const
{
	return x;
}

double Quaternion::GetY(void) const
{
	return y;
}

double Quaternion::GetZ(void) const
{
	return z;
}

double Quaternion::GetW(void) const
{
	return w;
}

sf::Packet& operator<<(sf::Packet& os, const Quaternion& obj)
{
	os << obj.x << obj.y << obj.z << obj.w;	
	return os;
}

sf::Packet& operator>>(sf::Packet& is, Quaternion& obj)
{
	is >> obj.x >> obj.y >> obj.z >> obj.w;
	return is;
}
