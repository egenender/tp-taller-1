#ifndef ESTADOMENUPRINCIPAL_H_
#define ESTADOMENUPRINCIPAL_H_
#include "Estado.h"
#include "../view/Superficie.h"
#include "../view/Animacion.h"
#include "../gui/model/Boton.h"
#include "../gui/view/VistaBoton.h"

class EstadoMenuPrincipal : public Estado {
private:
	static EstadoMenuPrincipal instancia;

	Superficie* fondo;
	Boton *btnMultiPlayer, *btnSinglePlayer;
	Animacion *animacion;
	VistaBoton *vistaBtnMulti, *vistaBtnSingle;
private:
	EstadoMenuPrincipal();
	void crearBtns();
	void crearVistas();

public:

	virtual ~EstadoMenuPrincipal();
	void manejarEvento(SDL_Event* evento);
	void actualizar(float delta);
	void dibujar(SDL_Surface* display);
	void iniciar();
	void terminar();
	static EstadoMenuPrincipal* obtenerInstancia();
};

#endif /* ESTADOMENUPRINCIPAL_H_ */
