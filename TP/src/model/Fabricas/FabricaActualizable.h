#ifndef FABRICAACTUALIZABLE_H_
#define FABRICAACTUALIZABLE_H_
#include "../Posicion.h"

class FabricaActualizable {
public:
	FabricaActualizable();
	virtual ~FabricaActualizable();
	virtual void fabricar(Posicion*,int)=0;
};

#endif /* FABRICAACTUALIZABLE_H_ */
