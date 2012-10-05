#ifndef STRUCTPOSICION_H_
#define STRUCTPOSICION_H_

typedef struct structPosicion structPosicion_t;

//Hay que evaluar si hay que crear aca punteros o la estructura queda en el stack!

structPosicion_t* structPosicion_crear(int newX, int newY);

void structPosicion_obtenerXY(structPosicion* estructura, int* x, int* y);

void structPosicion_destruir(structPosicion* estructura);

#endif /* STRUCTPOSICION_H_ */
