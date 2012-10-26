#ifndef MANEJADORCAMBIAESTADO_H_
#define MANEJADORCAMBIAESTADO_H_
#include "ManejadorBoton.h"

class ManejadorCambiaEstado : public ManejadorBoton{
private:
	int estadoCambio;
public:
	ManejadorCambiaEstado(int);
	virtual ~ManejadorCambiaEstado();
	void manejarClic();
};

#endif /* MANEJADORCAMBIAESTADO_H_ */
