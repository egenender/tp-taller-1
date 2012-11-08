#ifndef FABRICAHONGOS_H_
#define FABRICAHONGOS_H_
#include "FabricaActualizable.h"
#include "../Posicion.h"

class FabricaHongos : public FabricaActualizable {
public:
	FabricaHongos();
	virtual ~FabricaHongos();
	void fabricar (Posicion*, int);
};

#endif /* FABRICAHONGOS_H_ */
