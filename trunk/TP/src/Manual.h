#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 5
#include "Area.h"
#include "Cuerpo.h"

class Manual:public Cuerpo {
private:
	int velocidad;
public:
	Manual(Area*);
	Manual(Area*, int);
	virtual ~Manual();
	void moverALaIzquierda();
	void moverALaDerecha();
	//Estos 3 por ahora no van a hacer nada
	void saltar();
	void atacar();
	void especial();

private:
	void trasladar(int);
};

#endif /* MANUAL_H_ */
