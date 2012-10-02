/*
 * Punto.cpp
 *
 *  Created on: 10/09/2012
 *      Author: nicolas
 */

#include "Punto.h"

/** Compara si dos puntos son iguales **/
bool Punto::operator ==(Punto* otroPunto) {
	// Compara por punteros: ?
	if (this == otroPunto)
		return true;

	if (otroPunto == NULL)
		return false;

	if (otroPunto->obtenerX() != x)
		return false;

	if (otroPunto->obtenerY() != y)
		return false;

	return true;
}

/** Calcula la distancia al cuadrado de un punto a otro **/
double Punto::distancia2(Punto* otroPunto) {
	if (otroPunto == NULL)
		return 0;

	double otroX = otroPunto->obtenerX();
	double otroY = otroPunto->obtenerY();

	return (pow((x-otroX),2))+(pow((y-otroY),2));
}

/** Calcula la distancia de un punto a otro **/
double Punto::distancia(Punto* otroPunto) {
	return sqrt(distancia2(otroPunto));
}

Punto* Punto::sumar(int x, int y) {
	Punto* punto = new Punto(this->x + x, this->y + y);
	delete(this); // hmmmmmmmm TODO: Revisar esto!
	return punto;
}

Punto* Punto::sumar(Punto* otroPunto) {
	if (otroPunto == NULL)
		return this;

	return sumar(otroPunto->obtenerX(), otroPunto->obtenerY());
}
