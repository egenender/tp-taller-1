#ifndef DUMMY_H_
#define DUMMY_H_
#include <stdbool.h>
#include <stddef.h>
#include "Observable.h"


class Dummy : public Observable{
private:
	int estado;
	unsigned int ID;
	Posicion* pos;
public:
	Dummy(unsigned int);
	Dummy(unsigned int,Posicion*);
	virtual ~Dummy();
	void setXY(int,int);
	void setEstado(int);
	int obtenerEstado();
	Posicion* obtenerPosicion();
	bool esMio(unsigned int);
	void notificar();
};

#endif /* DUMMY_H_ */
