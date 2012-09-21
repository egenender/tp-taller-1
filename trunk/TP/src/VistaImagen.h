#ifndef VISTAIMAGEN_H_
#define VISTAIMAGEN_H_

#include "VistaCuerpo.h"
#include "Superficie.h"

#include <string>
using namespace std;

class VistaImagen : public VistaCuerpo {
protected:
	Superficie* imagen;

public:
	VistaImagen();
	VistaImagen(string ID);
	~VistaImagen();
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display);

	//void cambiarImagen(string ID);
	void cambiarImagen(Superficie* imagenNueva);
};



#endif /* VISTAIMAGEN_H_ */