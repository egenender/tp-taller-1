#ifndef MANEJADORSINGLEPLAYER_H_
#define MANEJADORSINGLEPLAYER_H_

#include "ManejadorBoton.h"
#include "ManejadorCambiaEstado.h"
#include "ListaScrolleable.h"

class ManejadorSinglePlayer: public ManejadorBoton {
private:
	ListaScrolleable *personaje, *nivel;
	ManejadorCambiaEstado* manejador;
public:
	ManejadorSinglePlayer(ListaScrolleable*, ListaScrolleable*);
	virtual ~ManejadorSinglePlayer();
	void manejarClic();
};

#endif /* MANEJADORSINGLEPLAYER_H_ */
