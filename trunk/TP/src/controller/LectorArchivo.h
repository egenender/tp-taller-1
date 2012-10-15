/*
 * LectorArchivo.h
 *
 *  Created on: Oct 15, 2012
 *      Author: genender
 */

#ifndef LECTORARCHIVO_H_
#define LECTORARCHIVO_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../log/Log.h"

class LectorArchivo {
private:
	FILE* archivo;
public:
	LectorArchivo();
	LectorArchivo(const char*);
	void AsignarArchivo(const char*);
	int* LeerArchivo(int*);
	void CerrarArchivo();
	virtual ~LectorArchivo();
};

#endif /* LECTORARCHIVO_H_ */
