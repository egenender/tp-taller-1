#ifndef ESTADOSINGLEPLAYER_H_
#define ESTADOSINGLEPLAYER_H_
#include "Estado.h"
#include "../gui/model/Boton.h"
#include "../gui/model/ListaScrolleable.h"
#include "../gui/view/VistaBoton.h"
#include "../gui/view/VistaLista.h"
#include "../gui/model/Label.h"
#include "../gui/view/VistaLabel.h"
#include "../gui/model/Muestra.h"
#include "SDL/SDL_mixer.h"

class EstadoSinglePlayer : public Estado{
private:
	static EstadoSinglePlayer instancia;

	Boton *btnMenu, *btnScrollNivelesArriba, *btnScrollNivelesAbajo, *btnScrollPersonajesArriba, *btnScrollPersonajesAbajo, *btnJugar;
	VistaBoton *vistaBtnMenu, *vistaBtnScrollNivelesArriba, *vistaBtnScrollNivelesAbajo, *vistaBtnScrollPersonajesArriba, *vistaBtnScrollPersonajesAbajo, *vistaBtnJugar;

	ListaScrolleable *scrollNiveles, *scrollPersonajes;
	VistaLista *vistaScrollNiveles, *vistaScrollPersonajes;

	Label *lblNivel, *lblPersonaje, *lblNombre ,*lblVelocidad, *lblSalto;
	VistaLabel *vistaLblNivel, *vistaLblPersonaje, *vistaLblNombre, *vistaLblVelocidad, *vistaLblSalto;

	Superficie *fondo, *fondo2;
	Muestra* animaciones;
	Mix_Music* musica;
private:
	EstadoSinglePlayer();
	void crearBtns();
	void crearLbls();
	void crearScroll();
	void crearVistas();
public:
	virtual ~EstadoSinglePlayer();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar(float delta);
	void dibujar(SDL_Surface* display);
	static EstadoSinglePlayer* obtenerInstancia();
};

#endif /* ESTADOSINGLEPLAYER_H_ */
