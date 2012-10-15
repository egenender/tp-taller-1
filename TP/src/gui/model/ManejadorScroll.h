#ifndef MANEJADORSCROLL_H_
#define MANEJADORSCROLL_H_
#include "ManejadorBoton.h"
#include "ListaScrolleable.h"

enum{
	ARRIBA = 0,
	ABAJO
};

class ManejadorScroll: public ManejadorBoton {
private:
	ListaScrolleable* scroll;
	int direccion;
public:
	ManejadorScroll(ListaScrolleable*,int);
	virtual ~ManejadorScroll();
	void manejarClic();
};

#endif /* MANEJADORSCROLL_H_ */
