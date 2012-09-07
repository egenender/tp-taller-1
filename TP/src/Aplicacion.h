/*
 * Aplicacion.h
 *
 *  Created on: 07/09/2012
 *      Author: martin
 */

#ifndef APLICACION_H_
#define APLICACION_H_



class Aplicacion {
private:
	Aplicacion* ap;
private:
	Aplicacion();
public:
	virtual ~Aplicacion();
	Aplicacion* crearAplicacion();
};


#endif /* APLICACION_H_ */
