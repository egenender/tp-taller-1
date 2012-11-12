#include "ManejadorSinglePlayer.h"
#include "../../controller/Nivel.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../../model/Personajes/BolaDeFuego.h"
#include "../../model/Personajes/Manual.h"

ManejadorSinglePlayer::ManejadorSinglePlayer(ListaScrolleable *n, ListaScrolleable *p) {
	personaje = p;
	nivel = n;
	manejador = new ManejadorCambiaEstado(ESTADO_JUEGO);
}

ManejadorSinglePlayer::~ManejadorSinglePlayer() {
	delete (manejador);
}

void ManejadorSinglePlayer::manejarClic(){
	string nombrePer = personaje->obtenerSeleccionado();
	int indexNivel = nivel->indiceSeleccionado();

	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	gestor->setNivelElegido(indexNivel);
	gestor->CargaRestante();
	gestor->setProtagonista(nombrePer);

	Nivel::obtenerInstancia()->setEstado(SINGLE);

	BolaDeFuego::setearCooperatividad(true);
	Manual::setearCooperatividad(true);

	manejador->manejarClic();
}
