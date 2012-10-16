#ifndef MANEJADORCREAR_H_
#define MANEJADORCREAR_H_

#include "ManejadorBoton.h"
#include "BarraEstado.h"
#include <string>
#include "CuadroTexto.h"
#include "ListaScrolleable.h"

//TODO:
#include "../../controller/Server.h"

class ManejadorCrear : public ManejadorBoton{
private:
	CuadroTexto* txtPuerto;
	ListaScrolleable *scrollNivel;

	BarraEstado* barra;
public:
	ManejadorCrear(CuadroTexto*, ListaScrolleable*, BarraEstado*);
	virtual ~ManejadorCrear();
	void manejarClic();
};

#endif /* MANEJADORCREAR_H_ */
