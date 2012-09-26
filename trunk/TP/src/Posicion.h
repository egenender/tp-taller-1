
#ifndef POSICION_H_
#define POSICION_H_
#include <stdbool.h>
#include <stddef.h>

class Posicion {
private:
	float x,y;
	static Posicion* maximo;
public:
	//Constructores y Destructores
	Posicion();
	Posicion(float,float);
	virtual ~Posicion();

	//Otras funciones
	float obtenerX();
	float obtenerY();
	void setearX(float);
	void setearY(float);

	//Para verificar si una posicion esta a la X de otra
	bool estaALaDerechaDe(Posicion);
	bool estaALaIzquierdaDe(Posicion);
	bool estaArribaDe(Posicion);
	bool estaAbajoDe(Posicion);

	//Para mover la posicion

	void sumarlePosicion(Posicion*);

	//Funciones de clase que permiten indicar y obtener el maximo
	static void indicarMaximo(float x, float y);
	static Posicion* obtenerMaximo(){return maximo;}

	/*Posicion obtenerDerecha();
		Posicion obtenerArriba();
		Posicion obtenerAbajo();
		void moverHorizontalmente(int);
		void moverVerticalmente(int);
		Posicion obtenerIzquierda();*/

};

#endif /* POSICION_H_ */
