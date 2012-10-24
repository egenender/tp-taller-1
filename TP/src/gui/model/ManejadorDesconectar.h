#ifndef MANEJADORDESCONECTAR_H_
#define MANEJADORDESCONECTAR_H_

#include "ManejadorBoton.h"

class ManejadorDesconectar: public ManejadorBoton {

public:
	ManejadorDesconectar();
	virtual ~ManejadorDesconectar();
	void manejarClic();
};

#endif /* MANEJADORDESCONECTAR_H_ */
