
#ifndef VISTALISTA_H_
#define VISTALISTA_H_
#include "../model/ListaScrolleable.h"
#include <vector>
#include <string>
#include "../../view/Superficie.h"
#include "SDL/SDL_ttf.h"
#include "../../common/Observador.h"
using namespace std;
#define ANCHOLETRA 10

class VistaLista : public Observador{
	unsigned int mostrables, seleccionadoAnterior, seleccionadoActual, topeSuperior, topeInferior;
	int x,y,alto,ancho;
	vector<SDL_Surface*>* mensajeAMostrar;

	Superficie* cuadro;
	Superficie* seleccionado;
	bool visible, primeraVez, sinCarga;
public:
	VistaLista(unsigned int);

	virtual ~VistaLista();
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display);
private:
	void llenarVector(ListaScrolleable*);
	string acortarMensaje(string);
};

#endif /* VISTALISTA_H_ */
