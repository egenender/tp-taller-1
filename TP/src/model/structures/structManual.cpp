#include "structManual.h"
#include <stddef.h>
#include <stdlib.h>

struct structManual{
	int x, y, estado, velocidadY, identificador;
};

//Precondicion: los valores son correctos. Lo asumo porque lo voy a llamar desde el mismo Manual.
structManual_t* structManual_crear(int posX, int posY, int estado, int vel /*, float deltaNico*/, int ID){
	structManual_t* estructura = (structManual_t*) malloc (sizeof(structManual_t));
	if (!estructura) return NULL;

	estructura->x = posX;
	estructura->y = posY;
	estructura->estado = estado;
	estructura->identificador = ID;
	estructura->velocidadY = vel;
	return estructura;
}

void structManual_obtener_posicion(structManual_t* estructura, int* x, int* y){
	*x = estructura->x;
	*y = estructura->y;
}

int structManual_obtener_velocidadY(structManual_t* estructura){
	return estructura->velocidadY;
}

int structManual_obtener_estado(structManual_t* estructura){
	return estructura->estado;
}

bool structManual_es_mio(structManual_t* estructura, int ID){
	return (estructura->identificador == ID);
}

void structManual_destruir(structManual_t* estructura){
	free(estructura);
}
