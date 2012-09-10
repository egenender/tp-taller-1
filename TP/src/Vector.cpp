/*
 * Vector.cpp
 *
 *  Created on: 10/09/2012
 *      Author: nicolas
 */

#include "Vector.h"

/* TODO: revisar si esta bien hacer "return this;" o si es mejor devolver una copia de this
 * (Esto es por si el usuario se encarga luego de liberar la memoria... si devolvemos this y
 * libera memoria, bueno, se cagarían las cosas (?)
 */


float gradosARadianes(float grados) {
	float radianes = 0;
	radianes = grados * (PI / 180);
	return radianes;
}

void Vector::setear(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector::setear(Vector* vector) {
	if (vector == NULL)
		return;

	setear(vector->x, vector->y);
}

/** Rota el vector en un angulo dado en grados **/
Vector* Vector::rotar(float angulo) {
	if (angulo < 0)
		return this;

	float alfa = 0;

	if (angulo >= 360)
		alfa = angulo - 360;
	else
		alfa = angulo;

	float r = gradosARadianes(alfa);
	float nuevoX = x * cos(r) + y * sin(r);
	float nuevoY = y * cos(r) - x * sin(r);

	return new Vector(nuevoX, nuevoY);
}

bool Vector::operator==(Vector* vector) {
	if (vector == NULL)
		return false;
	return (x == vector->x && y == vector->y);
}

float Vector::productoEscalar(Vector* vector) {
	if (vector == NULL)
		return 0;

	return x * vector->x + y * vector->y;
}

float Vector::angulo(Vector* vector) {
	if (vector == NULL)
		return 0;
	// TODO: revisar caso vector = (0,0);

	return gradosARadianes(acos(productoEscalar(vector) / (norma() * vector->norma())));
}

Vector* Vector::sumar(float constante) {
	return new Vector(x + constante, y + constante);
}

Vector* Vector::sumar(float x, float y) {
	return new Vector(this->x + x, this->y + y);
}

Vector* Vector::sumar(Vector* vector) {
	if (vector == NULL)
		return this;

	return new Vector(this->x + vector->x, this->y + vector->y);
}

Vector* Vector::restar(float constante) {
	return sumar(-constante);
}

Vector* Vector::restar(float x, float y) {
	return sumar(-x,-y);
}

Vector* Vector::restar(Vector* vector) {
	if (vector == NULL)
		return this;

	return new Vector(x - vector->x, y - vector->y);
}

Vector* Vector::multiplicar(float constante) {
	return new Vector(x * constante, y * constante);
}

Vector* Vector::dividir(float constante) {
	if (constante == 0)
		return this;
	return new Vector(x / constante, y / constante);
}

Vector* Vector::invertir() {
	return multiplicar(-1);
}

float Vector::norma() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector::norma2() {
	return pow(x, 2) + pow(y, 2);
}


Vector* Vector::normalizar() {
	Vector* zero = new Vector(0, 0);

	if (this == zero)
		return zero;

	delete (zero);

	return dividir(norma());
}
