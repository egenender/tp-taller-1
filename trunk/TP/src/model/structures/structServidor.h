#ifndef STRUCTSERVIDOR_H_
#define STRUCTSERVIDOR_H_

/* Este es el Struct que manda el Servidor, y recibe el Cliente */

typedef struct structServidor structServidor_t;

structServidor_t* structServidor_crear(unsigned int id, int x, int y, int estado);

unsigned int structServidor_obtener_id(structServidor_t*);

void structServidor_obtener_posicion(structServidor_t*, int*, int*);

int structServidor_obtener_estado(structServidor_t*);

void structServidor_destruir(structServidor_t*);

#endif /* STRUCTSERVIDOR_H_ */
