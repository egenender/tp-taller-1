#include <stdlib.h>
#include "cola.h"


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/ 

/* Definimos el tipo nodo */
typedef struct nodo{
	void* dato;
	struct nodo* proximo;
}nodo_t;

/* Definimos las funciones que tienen los nodos */

nodo_t* crear_nodo_cola(void* valor){
	nodo_t* nodo = (nodo_t*)malloc(sizeof(nodo_t));
	if (nodo==NULL)
		return NULL;
	nodo->proximo=NULL;
	nodo->dato=valor;
	return nodo;
}

/* Definimos el tipo de dato COLA */
struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(){
	cola_t *nueva_cola = (cola_t*)malloc(sizeof(cola_t));
	if (!nueva_cola)
		return NULL;
	nueva_cola->ultimo=NULL;
	nueva_cola->primero=NULL;
	return nueva_cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	nodo_t *aux;
	while (!cola_esta_vacia(cola)){
		aux=(nodo_t*)cola_desencolar(cola);
		if (destruir_dato)
			destruir_dato(aux);
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return (cola->primero==NULL && cola->ultimo==NULL);
}

bool cola_encolar(cola_t *cola, void* valor){
	if (cola==NULL)
		return false;
	nodo_t *nuevo_nodo=crear_nodo_cola(valor);
	if (!nuevo_nodo)
		return false;

	if (!cola_esta_vacia(cola)){
		(cola->ultimo)->proximo=nuevo_nodo;
		cola->ultimo=nuevo_nodo;
	}else{
		cola->primero=nuevo_nodo;
		cola->ultimo=nuevo_nodo;
	}
	return true;
}

void* cola_ver_primero(const cola_t* cola){
	if (cola->primero==NULL)
		return NULL;
	return (cola->primero)->dato;
}

void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola))
		return NULL;
	nodo_t *aux=cola->primero;
	if (cola->primero==cola->ultimo){
		cola->primero=NULL;
		cola->ultimo=NULL;
	}else{
		cola->primero=aux->proximo;
	}
	void* valor=aux->dato;
	free(aux);
	return valor;
}
