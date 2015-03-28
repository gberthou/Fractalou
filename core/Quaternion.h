#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <SFML/Network.hpp>

class Quaternion
{
	public:
		Quaternion();
		Quaternion(double x, double y, double z, double w);
		virtual ~Quaternion();
		
		double Length2(void);

		Quaternion operator+(const Quaternion &q) const;
		Quaternion operator-(const Quaternion &q) const;
		Quaternion operator*(const Quaternion &q) const;
		Quaternion operator*(double n) const;
		Quaternion operator=(Quaternion);

		friend sf::Packet& operator<<(sf::Packet& os, const Quaternion& obj);
		friend sf::Packet& operator>>(sf::Packet& is, Quaternion& obj);

	private:
		double x;
		double y;
		double z;
		double w;
};

#endif

