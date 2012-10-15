/*
 * LectorArchivo.cpp
 *
 *  Created on: Oct 15, 2012
 *      Author: genender
 */

#include "LectorArchivo.h"
#define RUTA_DEF "src/resources/cruzCuadroError4.png"

LectorArchivo::LectorArchivo() {
	// TODO Auto-generated constructor stub

}

LectorArchivo::LectorArchivo(const char *ruta) {
	archivo=fopen(ruta,"r");
	if (!(archivo)){
		archivo=fopen(RUTA_DEF,"r");
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de archivo invalido, se carga una ruta por defecto");
	}
}

void LectorArchivo::AsignarArchivo(const char *ruta) {
	archivo=fopen(ruta,"r");
	if (!(archivo)){
		archivo=fopen(RUTA_DEF,"r");
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de archivo invalido, se carga una ruta por defecto");
	}
}

int* LectorArchivo::LeerArchivo(int* cant) {
	if (!(archivo)){
		archivo=fopen(RUTA_DEF,"r");
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de archivo invalido, se carga una ruta por defecto");
	}
	int c,tam,i;
	int* buffer;
	tam = 20;
	//aparta espacio para un archivo
	buffer = (int*) malloc(tam*sizeof(int));
	i=0;
	c = fgetc(archivo);

	while (!feof(archivo)){
		if (i+1 >= tam){
			tam *= 2;
			int* aux = (int*) realloc(buffer, 2* tam * sizeof(int));
			if (!aux) break;
			buffer = aux;
		}
		buffer[i] = c;

		i++;
		c = fgetc(archivo);
	}

	*cant = i;
	return buffer;
}

void LectorArchivo::CerrarArchivo() {
	if (archivo){
		fclose(archivo);
	}
}

LectorArchivo::~LectorArchivo() {
	// TODO Auto-generated destructor stub
}

