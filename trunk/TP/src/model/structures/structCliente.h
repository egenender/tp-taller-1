#ifndef STRUCTCLIENTE_H_
#define STRUCTCLIENTE_H_

/* Este es el Struct que manda el Cliente, y recibe el Servidor */

typedef struct structCliente structCliente_t;

structCliente_t* structCliente_crear(unsigned int id, int estado);

unsigned int structCliente_obtener_id(structCliente_t*);

int structCliente_obtener_estado(structCliente_t*);

void structCliente_destruir(structCliente_t*);

#endif /* STRUCTCLIENTE_H_ */
