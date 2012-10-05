#include "structPosicion.h"
#include <stddef.h>
#include <stdlib.h>

struct structPosicion{
	int x;
	int y;
};

structPosicion_t* structPosicion_crear(int newX, int newY){
	structPosicion_t* estructura = (structPosicion_t*) malloc (sizeof(structPosicion_t));
	if(!estructura) return NULL;

	estructura->x = newX;
	estructura->y = newY;
	return estructura;
}

void structPosicion_obtenerXY(structPosicion* estructura, int* x, int* y){
	*x = estructura->x;
	*y = estructura->y;
}

void structPosicion_destruir(structPosicion* estructura){
	free(estructura);
}


