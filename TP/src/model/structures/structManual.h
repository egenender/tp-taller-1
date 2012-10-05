#ifndef STRUCTMANUAL_H_
#define STRUCTMANUAL_H_

typedef struct structManual structManual_t;

//Hay que evaluar si hay que crear aca punteros o la estructura queda en el stack!

structManual_t* structManual_crear(int posX, int posY, int estado, int vel /*, float deltaNico*/, int ID);

void structManual_obtener_posicion(structManual_t* estructura, int* x, int* y);

bool structManual_es_mio(structManual_t* estructura, int ID);

int structManual_obtener_velocidadY(structManual_t* estructura);

int structManual_obtener_estado(structManual_t* estructura);

void structManual_destruir(structManual_t* estructura);

#endif /* STRUCTMANUAL_H_ */
