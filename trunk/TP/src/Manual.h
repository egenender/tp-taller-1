#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 5
#include "Area.h"
#include "Cuerpo.h"

class Manual:public Cuerpo {
private:
	int velocidad;
public:
	Manual(const char*, Area*);
	Manual(const char*, Area*, int);
	virtual ~Manual();
	void moverALaIzquierda();
	void moverALaDerecha();
	//Estos 3 por ahora no van a hacer nada
	void saltar();
	void atacar();
	void especial();
	void actualizar();
private:
	void trasladar(int);
};

#endif /* MANUAL_H_ */
