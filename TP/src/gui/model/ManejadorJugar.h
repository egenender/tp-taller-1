
#ifndef MANEJADORJUGAR_H_
#define MANEJADORJUGAR_H_

#include "ManejadorBoton.h"
#include "ListaScrolleable.h"
#include "BarraEstado.h"

class ManejadorJugar: public ManejadorBoton {
private:
	ListaScrolleable* scroll;
	BarraEstado* barra;
public:
	ManejadorJugar(ListaScrolleable*, BarraEstado*);
	virtual ~ManejadorJugar();
	void manejarClic();
};

#endif /* MANEJADORJUGAR_H_ */
