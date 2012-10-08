#ifndef MANEJADORBOTON_H_
#define MANEJADORBOTON_H_

class ManejadorBoton {
public:
	ManejadorBoton();
	virtual ~ManejadorBoton();
	virtual void manejarClic()=0;
};

#endif /* MANEJADORBOTON_H_ */
