#ifndef ACTIVAESPECIAL_H_
#define ACTIVAESPECIAL_H_

#include "PowerUp.h"

class ActivaEspecial: public PowerUp {
public:
	ActivaEspecial(const char*, Area*, int);
	virtual ~ActivaEspecial();
	void chocarConManual(Manual*);
};

#endif /* ACTIVAESPECIAL_H_ */
