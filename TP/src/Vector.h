/*
 * Vector.h
 *
 *  Created on: 10/09/2012
 *      Author: nicolas
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

class Vector {
	private:
		float x,y;

	public:
		// Constructor:
		Vector(float x, float y) {
			this->x = x;
			this->y = y;
		}

		// Getters & Setters:
		float obtenerX() {	return this->x;}
		float obtenerY() {	return this->y;}
		void setear(float x, float y);
		void setear(Vector* vector);

		// Matematicas:
		Vector* invertir();
		Vector* normalizar();
		Vector* rotar(float angulo);
		bool operator==(Vector* vector);
		float productoEscalar(Vector* vector);
		float norma();
		float norma2();
		float angulo(Vector* vector);
		Vector* sumar(float constante);
		Vector* sumar(float x, float y);
		Vector* sumar(Vector* vector);
		Vector* restar(float constante);
		Vector* restar(float x, float y);
		Vector* restar(Vector* vector);
		Vector* multiplicar(float constante);
		Vector* dividir(float constante);
};


#endif /* VECTOR_H_ */
