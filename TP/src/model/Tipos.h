#ifndef TIPOS_H_
#define TIPOS_H_

#include <string>

#define TIPO_MANUAL 0
#define TIPO_HONGO 1
#define TIPO_TORTUGA 2
#define TIPO_BOLA_FUEGO 50
#define TIPO_PLATAFORMA_MOVIL 4
#define TIPO_CAMA_ELASTICA 5
#define TIPO_BARRIL 6
#define TIPO_CAJA 7
#define TIPO_MONO 8
#define TIPO_PRINCESA 9
#define TIPO_PU_INVENCIBILIDAD 10
#define TIPO_PU_PIEDRA 11
#define TIPO_PU_VIDA 12
#define TIPO_PU_BOLA 13
#define TIPO_TUB_ARRIBA 14
#define TIPO_TUB_ABAJO 15
#define TIPO_TUB_DERECHA 16
#define TIPO_TUB_IZQUIERDA 17
#define INVENCIBLE 18
#define MATADOR 19
#define ELEVADOR 20


std::string decodificarTipo(unsigned int);



#endif /* TIPOS_H_ */
