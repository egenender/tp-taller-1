#ifndef MANEJADORCOOPERATIVO_H_
#define MANEJADORCOOPERATIVO_H_
#include "ManejadorBoton.h"
#include "Checkbox.h"

class ManejadorCooperativo : public ManejadorBoton{
private:
	Checkbox* check;
public:
	ManejadorCooperativo();
	virtual ~ManejadorCooperativo();
	void manejarClic();
	void setearCheckbox(Checkbox*);
};

#endif /* MANEJADORCOOPERATIVO_H_ */
