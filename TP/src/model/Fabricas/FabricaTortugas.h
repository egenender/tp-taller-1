#ifndef FABRICATORTUGAS_H_
#define FABRICATORTUGAS_H_

#include "FabricaActualizable.h"
#include "../Posicion.h"

class FabricaTortugas: public FabricaActualizable {
public:
	FabricaTortugas();
	virtual ~FabricaTortugas();
	void fabricar(Posicion*,int);
};

#endif /* FABRICATORTUGAS_H_ */
