#include "ControladorCliente.h"
#include "../model/structures/structCliente.h"
#include "Cliente.h"
#include "ManejadorCliente.h"
#include "GestorConfiguraciones.h"
#include "ManejadorEstados.h"

ControladorCliente::ControladorCliente(unsigned int id, Dummy* tonto) {
	ID = id;
	//ultimoEstado = QUIETO;
	quieto = derecha = izquierda = saltando = false;
	controlable = tonto;
}

ControladorCliente::~ControladorCliente() {

}

void ControladorCliente::manejarEvento(SDL_Event* evento){
	Uint8 *keystates = SDL_GetKeyState(NULL);

	if (keystates[SDLK_ESCAPE]) {
		Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Se volvera al Estado de seleccion.");
		ManejadorCliente::obtenerInstancia(NULL)->detener();
		SDL_Delay(300);
		Cliente::obtenerInstancia("",0)->detener_escuchar();
		Cliente::obtenerInstancia("",0)->detener_escribir();
		Cliente::obtenerInstancia("",0)->detener();
		GestorConfiguraciones::getInstance()->acabarGestor();
		ManejadorEstados::setearEstadoActual(ESTADO_GUI);
		return;
	}

//	if (keystates[SDLK_UP]) {
//		revisarCambio(SALTAR);
//		//return;
//	}
//
//	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
//		revisarCambio(CAMINANDOIZQ);
//		return;
//	}
//
//	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
//		revisarCambio(CAMINANDODER);
//		return;
//	}
//
//	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT]) && !keystates[SDLK_UP]) {
//		revisarCambio(QUIETO);
//		return;
//	}

	if (keystates[SDLK_UP]){

		if (!saltando){
			saltando = true;
			quieto = false;
			//lo pongo en falso para que si se estaba ya movimiendo hacia algun lado,
			//tambien se mande esa actualizacion
			derecha = izquierda = false;
			enviarStruct(SALTAR);
		}
		if (controlable->obtenerEstado()!=SALTANDODER && controlable->obtenerEstado()!=SALTANDOIZQ){
			saltando = false;
		}

	}else saltando = false;

	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		if (!izquierda){
			quieto = false;
			derecha = false;
			izquierda = true;
			enviarStruct(CAMINANDOIZQ);
		}
	}else izquierda = false;

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		if (!derecha){
			quieto = false;
			izquierda = false;
			derecha = true;
			enviarStruct(CAMINANDODER);
		}
	}else derecha = false;

	if (!derecha && !izquierda && !saltando && !quieto){
		quieto = true;
		enviarStruct(QUIETO);
	}

}

void ControladorCliente::enviarStruct(int nuevoEstado){
	structCliente_t* estructura = structCliente_crear(ID, nuevoEstado);
	Cliente *cliente = Cliente::obtenerInstancia("", 0);
	cliente->encolar_cambio(estructura);
}

//void ControladorCliente::revisarCambio(int cambio){
//	if (ultimoEstado != cambio){
//		enviarStruct(cambio);
//		ultimoEstado = cambio;
//	}
//}
