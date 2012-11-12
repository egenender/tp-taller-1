#ifndef FABRICAPOWERUPS_H_
#define FABRICAPOWERUPS_H_

#include "FabricaActualizable.h"
#include <vector>

class FabricaPowerUps: public FabricaActualizable {
private:
	std::vector<FabricaActualizable*>* fabricas;
public:
	FabricaPowerUps();
	virtual ~FabricaPowerUps();
	void fabricar(Posicion*, int);
private:
	int eleccionFabrica();
	float tirarRandom();
};

#endif /* FABRICAPOWERUPS_H_ */
