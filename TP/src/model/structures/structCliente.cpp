#include "structCliente.h"
#include <stddef.h>
#include <stdlib.h>

struct structCliente{
	unsigned int id;
	int estado;
};


structCliente_t* structCliente_crear(unsigned int id, int estado){
	structCliente_t* estructura = (structCliente_t*) malloc (sizeof(structCliente_t));
	if (!estructura) return NULL;
	estructura->estado = estado;
	estructura->id = id;
	return estructura;
}

unsigned int structCliente_obtener_id(structCliente_t* estructura){
	return estructura->id;
}

int structCliente_obtener_estado(structCliente_t* estructura){
	return estructura->estado;
}

void structCliente_destruir(structCliente_t* estructura){
	free(estructura);
}
size_t structCliente_obtener_tamanio(){
	return sizeof(structCliente_t);
}
