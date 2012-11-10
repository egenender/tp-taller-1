#ifndef FABRICASTONES_H_
#define FABRICASTONES_H_

#include "FabricaActualizable.h"

class FabricaStones: public FabricaActualizable {
public:
	FabricaStones();
	virtual ~FabricaStones();
	void fabricar(Posicion*, int);
};

#endif /* FABRICASTONES_H_ */
