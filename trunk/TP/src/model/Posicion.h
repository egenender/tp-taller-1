
#ifndef POSICION_H_
#define POSICION_H_
#include <stdbool.h>
#include <stddef.h>

class Posicion {
private:
	int x,y;
	static Posicion* maximo;
	static int piso;
public:
	//Constructores y Destructores
	Posicion();
	Posicion(int,int);
	virtual ~Posicion();

	//Otras funciones
	int obtenerX();
	int obtenerY();
	void setearY(int);
	void setearX(int);

	//Para verificar si una posicion esta a la X de otra
	bool estaALaDerechaDe(Posicion*);
	bool estaALaIzquierdaDe(Posicion*);
	bool estaArribaDe(Posicion*);
	bool estaAbajoDe(Posicion*);

	//Para mover la posicion

	void sumarlePosicion(Posicion*);

	//Funciones de clase que permiten indicar y obtener el maximo
	static void indicarMaximo(int x, int y);
	static Posicion* obtenerMaximo(){return maximo;}
	static void indicarPiso(int y);
	static int obtenerPiso();

	/*Posicion obtenerDerecha();
		Posicion obtenerArriba();
		Posicion obtenerAbajo();
		void moverHorizontalmente(int);
		void moverVerticalmente(int);
		Posicion obtenerIzquierda();*/

	static Posicion* restarPosiciones(Posicion*, Posicion*);

};

#endif /* POSICION_H_ */
