#ifndef ACTIVAESPECIAL_H_
#define ACTIVAESPECIAL_H_

#include "PowerUp.h"

class activaEspecial: public PowerUp {
public:
	activaEspecial(const char*, Area*, int);
	virtual ~activaEspecial();
	void chocarConManual(Manual*);
};

#endif /* ACTIVAESPECIAL_H_ */
