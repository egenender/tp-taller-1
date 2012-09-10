/*
 * Punto.h
 *
 *  Created on: 10/09/2012
 *      Author: nicolas
 */

#ifndef PUNTO_H_
#define PUNTO_H_

#include <stdlib.h>
#include <math.h>

class Punto {
	private:
		int x,y;
	public:
		// Constructor:
		Punto(int x, int y) {
			this->x = x;
			this->y = y;
		}

		// Comportamiento:
		int obtenerX() {return x;}
		int obtenerY() {return y;}
		void setearX(int x) {this->x = x;}
		void setearY(int y) {this->y = y;}

		bool operator==(Punto* otroPunto);

		double distancia(Punto* otroPunto);
		double distancia2(Punto* otroPunto);
	//	double angulo(Punto* otroPunto);
		Punto* sumar(Punto* otroPunto);
		Punto* sumar(int x, int y);
};

#endif /* PUNTO_H_ */
