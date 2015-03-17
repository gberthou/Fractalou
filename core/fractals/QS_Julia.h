#ifndef QS_JULIA_H
#define QS_JULIA_H

#include "QuaternionSuite.h"

class QS_Julia : public QuaternionSuite
{
	public:
		QS_Julia(sf::Uint32 id, const Quaternion &z0, const Quaternion &c);
		virtual ~QS_Julia();

	protected:
		virtual Quaternion compute(const Quaternion &z);
		
		Quaternion c;
};

#endif
