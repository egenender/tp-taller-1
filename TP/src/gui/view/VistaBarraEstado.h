#ifndef VISTABARRAESTADO_H_
#define VISTABARRAESTADO_H_


#include "../../view/Superficie.h"
#include "SDL/SDL_ttf.h"
#include "../../view/VistaCuerpo.h"
#include <string>
using namespace std;

class VistaBarraEstado : public VistaCuerpo {
private:
	int x, y, ancho, alto;
	string mensajeActual, mensajeAnterior;
	SDL_Surface* mensajeAMostrar;
	Superficie* barraEstado;
	bool visible;

private:
	void inicializar();

public:
	VistaBarraEstado();
	~VistaBarraEstado();
	virtual void actualizar(Observable* observable);
	virtual bool dibujar(SDL_Surface* display);
	bool dibujar(SDL_Surface*, int, int, bool);
};


#endif /* VISTABOTON_H_ */
