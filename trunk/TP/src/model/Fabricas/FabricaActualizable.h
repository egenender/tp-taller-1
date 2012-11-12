#ifndef FABRICAACTUALIZABLE_H_
#define FABRICAACTUALIZABLE_H_
#include "../Posicion.h"
#define ARRIBA_FABR -2
#define ABAJO_FABR 2
#define DERECHA_FABR 1
#define IZQUIERDA_FABR -1

class FabricaActualizable {
public:
	FabricaActualizable();
	virtual ~FabricaActualizable();
	virtual void fabricar(Posicion*,int)=0;
protected:
	void definirXY(int*, int* , Posicion*, int , int, int);
};



#endif /* FABRICAACTUALIZABLE_H_ */
