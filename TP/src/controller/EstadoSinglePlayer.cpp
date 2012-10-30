#include "EstadoSinglePlayer.h"
#include "GestorConfiguraciones.h"
#include "ManejadorEstados.h"
#include "../gui/model/ManejadorCambiaEstado.h"
#include "../gui/model/ManejadorScroll.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "../gui/model/ManejadorSinglePlayer.h"
#include "../view/TipoProtagonista.h"

EstadoSinglePlayer EstadoSinglePlayer::instancia;

EstadoSinglePlayer::EstadoSinglePlayer() {
	btnMenu = btnScrollNivelesArriba = btnScrollNivelesAbajo = btnScrollPersonajesArriba = btnScrollPersonajesAbajo = btnJugar = NULL;
	scrollNiveles = scrollPersonajes = NULL;
	lblNivel = lblPersonaje = lblNombre = lblSalto = lblVelocidad = NULL;
	vistaBtnJugar = vistaBtnMenu = vistaBtnScrollNivelesAbajo = vistaBtnScrollNivelesArriba = vistaBtnScrollPersonajesAbajo = vistaBtnScrollPersonajesArriba =NULL;
	vistaLblNivel = vistaLblNombre = vistaLblPersonaje = vistaLblSalto = vistaLblVelocidad = NULL;
	vistaScrollNiveles = vistaScrollPersonajes = NULL;
	fondo = fondo2 = NULL;
	animaciones = NULL;
}

EstadoSinglePlayer::~EstadoSinglePlayer() {
}

EstadoSinglePlayer* EstadoSinglePlayer::obtenerInstancia(){
	return &instancia;
}

void EstadoSinglePlayer::iniciar(){
	crearLbls();
	crearScroll();
	crearBtns();
	crearVistas();
}

void EstadoSinglePlayer::crearScroll(){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	gestor->setPosiblesNiveles();
	std::vector<string>* nombresNiveles= gestor->ObtenerPosiblesNiveles();

	scrollNiveles = new ListaScrolleable(100,200,200,120);
	for (unsigned int i = 0 ; i< nombresNiveles->size(); i++) {
		scrollNiveles->agregarElemento( nombresNiveles->at(i) );
	}

	scrollPersonajes = new ListaScrolleable(400,200, 200, 120);
	animaciones = new Muestra(lblNombre, lblVelocidad, lblSalto, 600, 400, 50,50);
	gestor->inicioCarga();
	gestor->setPosiblesTiposProtagonistas();
	vector<TipoProtagonista*>* personajes = gestor->ObtenerPosiblesTiposProtagonistas();
	vector<string>* nombres = gestor->obtenerNombresProtagonistas();
	for (unsigned int i = 0; i < personajes->size(); i++){
		string texto = nombres->at(i);
		scrollPersonajes->agregarElemento(texto);
		animaciones->agregarVista(personajes->at(i));
	}
}

void EstadoSinglePlayer::crearLbls(){
	lblNivel = new Label(150,150,100,50);
	lblNivel->setearMensaje("Seleccione Nivel:");
	lblPersonaje = new Label (450,150,100,50);
	lblPersonaje->setearMensaje("Seleccione Personaje:");
	lblNombre = new Label (380,350,100,50);
	lblNombre->setearMensaje("Nombre");
	lblVelocidad = new Label (380,390,100,50);
	lblVelocidad->setearMensaje("Velocidad");
	lblSalto = new Label (380,430,100,50);
	lblSalto->setearMensaje("Salto");
}

void EstadoSinglePlayer::crearBtns(){
	btnMenu = new Boton (120,470, 150,60, new ManejadorCambiaEstado(ESTADO_MENU));
	btnScrollNivelesArriba = new Boton(300,200,30,30, new ManejadorScroll(scrollNiveles,ARRIBA));
	btnScrollNivelesAbajo = new Boton(300,290,30,30, new ManejadorScroll(scrollNiveles,ABAJO));
	btnScrollPersonajesArriba = new Boton(600,200,30,30, new ManejadorScroll(scrollPersonajes,ARRIBA, animaciones));
	btnScrollPersonajesAbajo = new Boton(600,290,30,30, new ManejadorScroll(scrollPersonajes,ABAJO,animaciones));
	btnJugar = new Boton(145,400,100,50, new ManejadorSinglePlayer(scrollNiveles,scrollPersonajes));

	btnMenu->setearMensaje("Volver al Menu");
	btnJugar->setearMensaje("Jugar");
	btnScrollNivelesArriba->setearMensaje(" ");
	btnScrollNivelesAbajo->setearMensaje(" ");
	btnScrollPersonajesArriba->setearMensaje(" ");
	btnScrollPersonajesAbajo->setearMensaje(" ");
}

void EstadoSinglePlayer::crearVistas(){
	vistaBtnMenu = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnJugar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnScrollNivelesArriba = new VistaBoton("src/gui/resources/flechaArriba.jpg",
			"src/gui/resources/flechaArribaClic.jpg");
	vistaBtnScrollNivelesAbajo = new VistaBoton("src/gui/resources/flechaAbajo.jpg",
			"src/gui/resources/flechaAbajoClic.jpg");
	vistaBtnScrollPersonajesArriba = new VistaBoton("src/gui/resources/flechaArriba.jpg",
			"src/gui/resources/flechaArribaClic.jpg");
	vistaBtnScrollPersonajesAbajo = new VistaBoton("src/gui/resources/flechaAbajo.jpg",
			"src/gui/resources/flechaAbajoClic.jpg");

	vistaLblNivel = new VistaLabel();
	vistaLblPersonaje = new VistaLabel();
	vistaLblNombre = new VistaLabel();
	vistaLblVelocidad = new VistaLabel();
	vistaLblSalto = new VistaLabel();

	vistaScrollNiveles = new VistaLista(3);
	vistaScrollPersonajes = new VistaLista(4);

	fondo = new Superficie ("src/gui/resources/fondo.bmp");
	fondo2 = new Superficie ("src/gui/resources/fondoPestanias.bmp");
	fondo2->transparencia(255,0,255);

	btnMenu->agregarObservador(vistaBtnMenu);
	btnJugar->agregarObservador(vistaBtnJugar);
	btnScrollNivelesArriba->agregarObservador(vistaBtnScrollNivelesArriba);
	btnScrollNivelesAbajo->agregarObservador(vistaBtnScrollNivelesAbajo);
	btnScrollPersonajesArriba->agregarObservador(vistaBtnScrollPersonajesArriba);
	btnScrollPersonajesAbajo->agregarObservador(vistaBtnScrollPersonajesAbajo);

	lblNivel->agregarObservador(vistaLblNivel);
	lblPersonaje->agregarObservador(vistaLblPersonaje);
	lblNombre->agregarObservador(vistaLblNombre);
	lblVelocidad->agregarObservador(vistaLblVelocidad);
	lblSalto->agregarObservador(vistaLblSalto);

	scrollNiveles->agregarObservador(vistaScrollNiveles);
	scrollPersonajes->agregarObservador(vistaScrollPersonajes);

}

void EstadoSinglePlayer::terminar(){
	if (btnMenu){
		delete (btnMenu);
		btnMenu = NULL;
	}
	if (btnScrollNivelesArriba){
		delete (btnScrollNivelesArriba);
		btnScrollNivelesArriba = NULL;
	}
	if (btnScrollNivelesAbajo){
		delete (btnScrollNivelesAbajo);
		btnScrollNivelesAbajo = NULL;
	}
	if (btnScrollPersonajesArriba){
		delete (btnScrollPersonajesArriba);
		btnScrollPersonajesArriba = NULL;
	}
	if (btnScrollPersonajesAbajo){
		delete (btnScrollPersonajesAbajo);
		btnScrollPersonajesAbajo = NULL;
	}
	if (btnJugar){
		delete (btnJugar);
		btnJugar = NULL;
	}
	if (vistaBtnMenu){
		delete (vistaBtnMenu);
		vistaBtnMenu = NULL;
	}
	if (vistaBtnScrollNivelesArriba){
		delete (vistaBtnScrollNivelesArriba);
		vistaBtnScrollNivelesArriba = NULL;
	}
	if (vistaBtnScrollNivelesAbajo){
		delete (vistaBtnScrollNivelesAbajo);
		vistaBtnScrollNivelesAbajo = NULL;
	}
	if (vistaBtnScrollPersonajesArriba){
		delete (vistaBtnScrollPersonajesArriba);
		vistaBtnScrollPersonajesArriba = NULL;
	}
	if (vistaBtnScrollPersonajesAbajo){
		delete (vistaBtnScrollPersonajesAbajo);
		vistaBtnScrollPersonajesAbajo = NULL;
	}
	if (vistaBtnJugar){
		delete (vistaBtnJugar);
		vistaBtnJugar = NULL;
	}
	if (scrollNiveles){
		delete (scrollNiveles);
		scrollNiveles = NULL;
	}
	if (scrollPersonajes){
		delete (scrollPersonajes);
		scrollPersonajes = NULL;
	}
	if (vistaScrollNiveles){
		delete (vistaScrollNiveles);
		vistaScrollNiveles = NULL;
	}
	if (vistaScrollPersonajes){
		delete (vistaScrollPersonajes);
		vistaScrollPersonajes = NULL;
	}
	if (lblNivel){
		delete (lblNivel);
		lblNivel = NULL;
	}
	if (lblPersonaje){
		delete (lblPersonaje);
		lblPersonaje = NULL;
	}
	if(lblNombre){
		delete(lblNombre);
		lblNombre = NULL;
	}
	if(lblVelocidad){
		delete(lblVelocidad);
		lblVelocidad = NULL;
	}
	if(lblSalto){
		delete(lblSalto);
		lblSalto = NULL;
	}
	if (vistaLblNivel){
		delete (vistaLblNivel);
		vistaLblNivel = NULL;
	}
	if (vistaLblPersonaje){
		delete (vistaLblPersonaje);
		vistaLblPersonaje = NULL;
	}
	if (vistaLblNombre){
		delete (vistaLblNombre);
		vistaLblNombre = NULL;
	}
	if (vistaLblVelocidad){
		delete (vistaLblVelocidad);
		vistaLblVelocidad = NULL;
	}
	if (vistaLblSalto){
		delete (vistaLblSalto);
		vistaLblSalto = NULL;
	}
	if(fondo){
		delete(fondo);
		fondo = NULL;
	}
	if(animaciones){
		delete(animaciones);
		animaciones = NULL;
	}

}

void EstadoSinglePlayer::manejarEvento(SDL_Event* evento){
	btnScrollNivelesArriba->manejarEvento(evento);
	btnScrollNivelesAbajo->manejarEvento(evento);
	btnScrollPersonajesArriba->manejarEvento(evento);
	btnScrollPersonajesAbajo->manejarEvento(evento);
	if (ManejadorEstados::obtenerEstadoActual() == obtenerInstancia())
		btnMenu->manejarEvento(evento);
	if (ManejadorEstados::obtenerEstadoActual() == obtenerInstancia())
		btnJugar->manejarEvento(evento);
}

void EstadoSinglePlayer::actualizar(float delta){
	btnMenu->actualizar();
	btnJugar->actualizar();
	btnScrollNivelesArriba->actualizar();
	btnScrollNivelesAbajo->actualizar();
	btnScrollPersonajesArriba->actualizar();
	btnScrollPersonajesAbajo->actualizar();

	scrollNiveles->actualizar();
	scrollPersonajes->actualizar();

	lblNivel->actualizar();
	lblPersonaje->actualizar();
	lblNombre->actualizar();
	lblSalto->actualizar();
	lblVelocidad->actualizar();

	animaciones->actualizar();
}

void EstadoSinglePlayer::dibujar(SDL_Surface* display){
	fondo->dibujar(display,0,0);
	fondo2->dibujar(display,80,80);
	vistaBtnMenu->dibujar(display);
	vistaBtnScrollNivelesArriba->dibujar(display);
	vistaBtnScrollNivelesAbajo->dibujar(display);
	vistaBtnScrollPersonajesArriba->dibujar(display);
	vistaBtnScrollPersonajesAbajo->dibujar(display);
	vistaBtnJugar->dibujar(display);

	vistaScrollNiveles->dibujar(display);
	vistaScrollPersonajes->dibujar(display);

	vistaLblNivel->dibujar(display);
	vistaLblPersonaje->dibujar(display);
	vistaLblNombre->dibujar(display);
	vistaLblVelocidad->dibujar(display);
	vistaLblSalto->dibujar(display);

	animaciones->dibujar(display);
}
