#include "structServidor.h"
#include <stddef.h>
#include <stdlib.h>

struct structServidor{
	unsigned int id;
	unsigned int tipo;
	int estado;
	int x;
	int y;
};


structServidor_t* structServidor_crear(unsigned int id, int x, int y ,int estado, unsigned int tipo){
	structServidor_t* estructura = (structServidor_t*) malloc (sizeof(structServidor_t));
	if (!estructura) return NULL;
	estructura->estado = estado;
	estructura->id = id;
	estructura->x = x;
	estructura->y = y;
	estructura->tipo = tipo;
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

size_t structServidor_obtener_tamanio(){
	return sizeof(structServidor_t);
}

unsigned int structServidor_obtener_tipo(structServidor_t* estructura){
	return estructura->tipo;
}
