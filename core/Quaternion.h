#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>

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
		Quaternion operator=(Quaternion);

		friend std::ostream& operator<<(std::ostream& os, const Quaternion& obj);
		friend std::istream& operator>>(std::istream& is, Quaternion& obj);

	private:
		double x;
		double y;
		double z;
		double w;
};

#endif

