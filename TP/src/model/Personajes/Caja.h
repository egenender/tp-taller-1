#ifndef CAJA_H_
#define CAJA_H_
#include "../Fabricas/FabricaActualizable.h"

#include "Plataforma.h"
#include "Manual.h"
#define TIEMPO_CAJA 10

class Caja: public Plataforma {
	FabricaActualizable* fabrica;
	Timer* timer;
public:
	Caja(const char*, Area*, FabricaActualizable*);
	virtual ~Caja();
	void chocarConManual(Manual*);
	void actualizar(float);
private:
	void fabricar();
};

#endif /* CAJA_H_ */
