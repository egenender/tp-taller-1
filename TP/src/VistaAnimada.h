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

public:
	VistaAnimada();
	~VistaAnimada();
	bool dibujar(SDL_Surface* display);
};


#endif /* VISTAANIMADA_H_ */
