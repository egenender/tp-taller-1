#include "structServidor.h"
#include <stddef.h>
#include <stdlib.h>

struct structServidor{
	unsigned int id;
	int estado;
	int x;
	int y;
};


structServidor_t* structServidor_crear(unsigned int id, int x, int y ,int estado){
	structServidor_t* estructura = (structServidor_t*) malloc (sizeof(structServidor_t));
	if (!estructura) return NULL;
	estructura->estado = estado;
	estructura->id = id;
	estructura->x = x;
	estructura->y = y;
	return estructura;
}

unsigned int structServidor_obtener_id(structServidor_t* estructura){
	return estructura->id;
}

int structServidor_obtener_estado(structServidor_t* estructura){
	return estructura->estado;
}

void structServidor_obtener_posicion(structServidor_t* estructura, int* x, int *y){
	*x = estructura->x;
	*y = estructura->y;
}

void structServidor_destruir(structServidor_t* estructura){
	free(estructura);
}
