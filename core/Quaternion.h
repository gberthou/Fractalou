#ifndef QUATERNION_H
#define QUATERNION_H

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

	private:
		double x;
		double y;
		double z;
		double w;
};

#endif

