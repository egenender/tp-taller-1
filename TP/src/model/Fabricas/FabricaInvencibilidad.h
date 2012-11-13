#ifndef FABRICAINVENCIBILIDAD_H_
#define FABRICAINVENCIBILIDAD_H_
#include "FabricaActualizable.h"

class FabricaInvencibilidad : public FabricaActualizable{
public:
	FabricaInvencibilidad();
	virtual ~FabricaInvencibilidad();
	void fabricar(Posicion*, int);

};

#endif /* FABRICAINVENCIBILIDAD_H_ */
