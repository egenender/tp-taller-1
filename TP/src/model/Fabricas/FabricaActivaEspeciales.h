#ifndef FABRICAACTIVAESPECIALES_H_
#define FABRICAACTIVAESPECIALES_H_

#include "FabricaActualizable.h"

class FabricaActivaEspeciales: public FabricaActualizable {
public:
	FabricaActivaEspeciales();
	virtual ~FabricaActivaEspeciales();
	void fabricar(Posicion*, int);
};

#endif /* FABRICAACTIVAESPECIALES_H_ */
