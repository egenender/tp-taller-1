#ifndef DUMMY_H_
#define DUMMY_H_
#include <stdbool.h>
#include <stddef.h>
#include "Observable.h"
#include "Area.h"


class Dummy : public Observable{
private:
	int estado;
	unsigned int ID;
	Posicion* pos;
	int ancho, alto;
	bool invencible;
	bool matador;
	unsigned int vidas;

public:
	Dummy(unsigned int,Posicion*, int ancho, int alto);

	virtual ~Dummy();
	void setXY(int,int);
	void setEstado(int, int);
	int obtenerEstado();
	Posicion* obtenerPosicion();
	bool esMio(unsigned int);
	void notificar();
	unsigned int obtenerID();
	int obtenerAncho();
	int obtenerAlto();
	int obtenerVidas();
	void setearVidas(unsigned int);

	bool estaInvencible();
	bool mataAlContacto();
	bool puedeMover();
	bool estaMuerto();
};

#endif /* DUMMY_H_ */
