#ifndef VISTAANIMADA_H_
#define VISTAANIMADA_H_

#include "Animacion.h"
#include "VistaCuerpo.h"
#include <map>
using namespace std;

class VistaAnimada : public VistaCuerpo {
protected:
	map<int,Animacion*>* animaciones;
	Animacion* animacionActual;
	bool pararDeDibujar;
public:
	VistaAnimada();
	~VistaAnimada();
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display, int xCamara, int yCamara, bool debug);
	virtual void reiniciar()=0;
};


#endif /* VISTAANIMADA_H_ */
