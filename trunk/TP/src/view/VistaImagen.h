#ifndef VISTAIMAGEN_H_
#define VISTAIMAGEN_H_

#include "VistaCuerpo.h"
#include "Superficie.h"
#include "../model/Observable.h"

#include <string>
using namespace std;

class VistaImagen : public VistaCuerpo {
protected:
	Superficie* imagen;

public:
	VistaImagen();
	VistaImagen(string ID);
	~VistaImagen();
	VistaImagen(Superficie* imagen, int angulo = 0);
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display, int xCamara, int yCamara, bool debug);

	//void cambiarImagen(string ID);
	void cambiarImagen(Superficie* imagenNueva);
};



#endif /* VISTAIMAGEN_H_ */
