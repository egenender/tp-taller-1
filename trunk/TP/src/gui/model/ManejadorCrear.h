#ifndef MANEJADORCREAR_H_
#define MANEJADORCREAR_H_

#include "ManejadorBoton.h"
#include "BarraEstado.h"
#include <string>
//TODO
//#include "CuadroTexto.h"
//#include "VentanaTexto.h"

class ManejadorCrear : public ManejadorBoton{
private:
	//TODO:
	/*
	 CuadroTexto* txtPuerto;
	 VentanaTexto txtPersonaje;
	 */
	BarraEstado* barra;
public:
	ManejadorCrear(/*CuadroTexto*, VentanaTexto*,*/ BarraEstado*);
	virtual ~ManejadorCrear();
	void manejarClic();
};

#endif /* MANEJADORCREAR_H_ */
