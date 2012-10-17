#ifndef MANEJADORCONECTAR_H_
#define MANEJADORCONECTAR_H_
#include "ManejadorBoton.h"
#include "CuadroTexto.h"
#include "BarraEstado.h"
#include "ManejadorSolapa.h"
#include "../../model/lista.h"

class ManejadorConectar : public ManejadorBoton{
private:
	CuadroTexto *txtIP, *txtPuerto;
	BarraEstado* barra;
	ManejadorSolapa* manejador;
public:
	ManejadorConectar(CuadroTexto*, CuadroTexto*, BarraEstado*, lista_t*, lista_t*);
	virtual ~ManejadorConectar();
	void manejarClic();
};

#endif /* MANEJADORCONECTAR_H_ */
