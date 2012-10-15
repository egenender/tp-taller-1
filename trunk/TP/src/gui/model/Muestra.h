#ifndef MUESTRA_H_
#define MUESTRA_H_
#include "ObjetoGUI.h"
#include "../../view/VistaProtagonista.h"

class Muestra :public ObjetoGUI{
private:
	vector<VistaProtagonista*>* vectorcito;
	unsigned int seleccion;
public:
	Muestra(int,int,int,int);
	virtual ~Muestra();
	void agregarVista (VistaProtagonista*);
	void eliminarVista (unsigned int);
	void siguiente();
	void anterior();
	VistaProtagonista* obtenerActual();
};

#endif /* MUESTRA_H_ */
