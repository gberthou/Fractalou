#ifndef QS_JULIA_H
#define QS_JULIA_H

#include "../QuaternionSuite.h"

class QS_Julia : public QuaternionSuite
{
	public:
		QS_Julia(sf::Uint32 id, const Quaternion &z0, const Quaternion &c, sf::Uint32 iterationsMax, double limit);
		virtual ~QS_Julia();

		friend std::ostream& operator<<(std::ostream& os, const QS_Julia& obj);
		friend std::istream& operator>>(std::istream& is, QS_Julia& obj);

	protected:
		virtual Quaternion compute(const Quaternion &z) const;

		Quaternion c;
};

#endif

