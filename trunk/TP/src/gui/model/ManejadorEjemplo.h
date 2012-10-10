#ifndef MANEJADOREJEMPLO_H_
#define MANEJADOREJEMPLO_H_
#include "ManejadorBoton.h"

class ManejadorEjemplo : public ManejadorBoton{
public:
	ManejadorEjemplo();
	virtual ~ManejadorEjemplo();
	void manejarClic();
};

#endif /* MANEJADOREJEMPLO_H_ */
