
#ifndef POSICION_H_
#define POSICION_H_
#include <stdbool.h>
#include <stddef.h>

class Posicion {
private:
	int x,y;
	static Posicion* maximo;
public:
	//Constructores y Destructores
	Posicion();
	Posicion(int,int);
	virtual ~Posicion();

	//Otras funciones
	Posicion obtenerDerecha();
	Posicion obtenerArriba();
	Posicion obtenerAbajo();
	Posicion obtenerIzquierda();
	int getX();
	int getY();
	void setX(int);
	void setY(int)

	//Para verificar si una posicion esta a la X de otra
	bool estaALaDerechaDe(Posicion);
	bool estaALaIzquierdaDe(Posicion);
	bool estaArribaDe(Posicion);
	bool estaAbajoDe(Posicion);

	//Para mover la posicion
	void moverHorizontalmente(int);
	void moverVerticalmente(int);
	void sumarlePosicion(Posicion*);

	//Funciones de clase que permiten indicar y obtener el maximo
	static void indicarMaximo(Posicion*);
	static Posicion* obtenerMaximo(){return maximo;}
};

#endif /* POSICION_H_ */
