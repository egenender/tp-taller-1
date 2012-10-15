#ifndef MANEJADORSCROLL_H_
#define MANEJADORSCROLL_H_
#include "ManejadorBoton.h"
#include "ListaScrolleable.h"
#include "Muestra.h"

#define ARRIBA 0
#define ABAJO 1

class ManejadorScroll: public ManejadorBoton {
private:
	ListaScrolleable* scroll;
	int direccion;
	Muestra* anim;
public:
	ManejadorScroll(ListaScrolleable*,int);
	ManejadorScroll(ListaScrolleable*,int, Muestra*);
	virtual ~ManejadorScroll();
	void manejarClic();
};

#endif /* MANEJADORSCROLL_H_ */
