#ifndef FABRICABARRILES_H_
#define FABRICABARRILES_H_
#include "FabricaActualizable.h"
#include "../Posicion.h"
#include "../Personajes/Barril.h"

class FabricaBarriles : public FabricaActualizable{
public:
	FabricaBarriles();
	virtual ~FabricaBarriles();
	void fabricar (Posicion*, int);
private:
	void terminarCreacion(Barril*);
};

#endif /* FABRICABARRILES_H_ */
