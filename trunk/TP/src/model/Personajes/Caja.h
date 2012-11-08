#ifndef CAJA_H_
#define CAJA_H_
#include "../Fabricas/FabricaActualizable.h"

#include "Plataforma.h"
#include "Manual.h"

class Caja: public Plataforma {
	FabricaActualizable* fabrica;
public:
	Caja(const char*, Area*, FabricaActualizable*);
	virtual ~Caja();
	void chocarConManual(Manual*);
private:
	void fabricar();
};

#endif /* CAJA_H_ */
