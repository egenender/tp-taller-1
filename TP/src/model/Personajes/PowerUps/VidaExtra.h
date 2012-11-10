#ifndef VIDAEXTRA_H_
#define VIDAEXTRA_H_
#include "PowerUp.h"
#include "../Manual.h"

class VidaExtra : public PowerUp{
public:
	VidaExtra(const char*, Area*, int);
	virtual ~VidaExtra();

	void chocarConManual(Manual*);
};

#endif /* VIDAEXTRA_H_ */
