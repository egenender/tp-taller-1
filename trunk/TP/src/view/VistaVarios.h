#ifndef VISTAVARIOS_H_
#define VISTAVARIOS_H_

#include "VistaAnimada.h"
#include "Animacion.h"

class VistaVarios: public VistaAnimada{
public:
	VistaVarios();
	virtual ~VistaVarios();
	void actualizar(Observable* observable);
	void reiniciar();

	void agregarEstadoSoportado(int, Animacion*);
	void agregarEstadoSoportadoEInverso(int,int, Animacion*);
};

#endif /* VISTAVARIOS_H_ */
