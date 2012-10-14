#ifndef VISTALABEL_H_
#define VISTALABEL_H_

#include "../../view/Superficie.h"
#include "SDL/SDL_ttf.h"
#include "../../common/Observador.h"
#include "../model/Label.h"
#include <string>
using namespace std;


class VistaLabel: public Observador {
private:
	int x, y, ancho, alto;
	string mensajeActual, mensajeAnterior;
	SDL_Surface* mensajeAMostrar;
	bool visible;

private:
	void inicializar();

public:
	VistaLabel();
	virtual ~VistaLabel();
	virtual void actualizar(Observable* observable);
	virtual bool dibujar(SDL_Surface* display);
};

#endif /* VISTALABEL_H_ */
