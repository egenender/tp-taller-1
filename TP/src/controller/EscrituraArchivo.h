/*
 * EscrituraArchivo.h
 *
 *  Created on: Oct 15, 2012
 *      Author: genender
 */

#ifndef ESCRITURAARCHIVO_H_
#define ESCRITURAARCHIVO_H_

#include <stdio.h>
#include <iostream>
#include "../log/Log.h"

class EscrituraArchivo {
private:
	FILE* archivo;
public:
	EscrituraArchivo( );
	EscrituraArchivo(char* );
	void AsignarArchivo(const char*);
	void EscribirArchivo(int*, int);
	void CerrarArchivo();
	virtual ~EscrituraArchivo();
};

#endif /* ESCRITURAARCHIVO_H_ */
