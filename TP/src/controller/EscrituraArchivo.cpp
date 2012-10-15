/*
 * EscrituraArchivo.cpp
 *
 *  Created on: Oct 15, 2012
 *      Author: genender
 */

#include "EscrituraArchivo.h"
#define RUTA_DEF "src/resources/cruzCuadroError4.png"

EscrituraArchivo::EscrituraArchivo() {
	// TODO Auto-generated constructor stub

}

EscrituraArchivo::EscrituraArchivo(char *ruta) {
	archivo=fopen(ruta,"w");
	if (!(archivo)){
		archivo=fopen(RUTA_DEF,"w");
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de archivo invalido, se carga una ruta por defecto");
	}
}

void EscrituraArchivo::AsignarArchivo(const char *ruta) {
	archivo=fopen(ruta,"w");
	if (!(archivo)){
		archivo=fopen(RUTA_DEF,"w");
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de archivo invalido, se carga una ruta por defecto");
	}
}

void EscrituraArchivo::EscribirArchivo(int* dato, int cant){
	int i;
	for (i=0;i<cant;i++){
		fprintf(archivo, "%c", dato[i] );
	}
}

void EscrituraArchivo::CerrarArchivo() {
	if (archivo){
		fclose(archivo);
	}
}

EscrituraArchivo::~EscrituraArchivo() {
	// TODO Auto-generated destructor stub
}

