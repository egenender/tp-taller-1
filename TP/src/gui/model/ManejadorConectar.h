#ifndef MANEJADORCONECTAR_H_
#define MANEJADORCONECTAR_H_
#include "ManejadorBoton.h"
#include "CuadroTexto.h"
#include "BarraEstado.h"
#include "ManejadorSolapa.h"
#include "ListaScrolleable.h"
#include "Muestra.h"
#include "../../model/lista.h"

class ManejadorConectar : public ManejadorBoton{
private:
	CuadroTexto *txtIP, *txtPuerto;
	BarraEstado* barra;
	ManejadorSolapa* manejador;
	Muestra* muestra;
	ListaScrolleable* scroll;
public:
	ManejadorConectar(CuadroTexto*, CuadroTexto*, BarraEstado*, lista_t*, lista_t*, ListaScrolleable*, Muestra*);
	virtual ~ManejadorConectar();
	void manejarClic();
};

#endif /* MANEJADORCONECTAR_H_ */
