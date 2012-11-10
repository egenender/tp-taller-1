#ifndef FABRICAVIDASEXTRA_H_
#define FABRICAVIDASEXTRA_H_

#include "FabricaActualizable.h"

class FabricaVidasExtra: public FabricaActualizable {
public:
	FabricaVidasExtra();
	virtual ~FabricaVidasExtra();
	void fabricar(Posicion*,int);
};

#endif /* FABRICAVIDASEXTRA_H_ */
