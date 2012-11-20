#include "ControladorCliente.h"
#include "../model/structures/structCliente.h"
#include "Cliente.h"
#include "ManejadorCliente.h"
#include "GestorConfiguraciones.h"
#include "ManejadorEstados.h"

ControladorCliente::ControladorCliente(unsigned int id, Dummy* tonto) {
	ID = id;
	ultimoEstado = QUIETO;
	quieto = derecha = izquierda = saltando = false;
	controlable = tonto;
	mantieneVivo = new Timer();
	mantieneVivo->comenzar();
}

ControladorCliente::~ControladorCliente() {
	delete (mantieneVivo);
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

	if (mantieneVivo->obtenerTiempo() >= (TIEMPO_ESPERA * 1000)){
		enviarStruct(VIVO);
	}

	if (!controlable->puedeMover())
		return ;
	if (controlable->estaMuerto())
			return ;


	if (keystates[SDLK_SPACE]) {
		if (controlable->obtenerEstado()!=SALTANDODER && controlable->obtenerEstado()!=SALTANDOIZQ && controlable->obtenerEstado()!=(EVOLUCION + SALTANDODER) && controlable->obtenerEstado()!=(EVOLUCION + SALTANDOIZQ))
			revisarCambio(SALTAR);
//		if (controlable->saltoAlto)
//			enviarStruct(SALTAR);
	}else if (controlable->saltoAlto){
		controlable->saltoAlto = false;
		enviarStruct(QUIETO);
	}
	if (controlable->saltoAlto && keystates[SDLK_SPACE])
		enviarStruct(SALTAR);


	if (keystates[SDLK_UP] && !keystates[SDLK_DOWN]) {
			revisarCambio(SUBIR);
			return;
	}

	if (!keystates[SDLK_UP] && keystates[SDLK_DOWN]) {
		revisarCambio(BAJAR);
		return;
	}

	if (keystates[SDLK_z] ) {
		revisarCambio(ESPECIAL);
		return;
	}

	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		revisarCambio(CAMINANDOIZQ);
		return;
	}

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		revisarCambio(CAMINANDODER);
		return;
	}

	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT]) && !(keystates[SDLK_UP] ^ keystates[SDLK_DOWN])) {
			if(controlable->obtenerEstado()!=SALTANDODER && controlable->obtenerEstado()!=SALTANDOIZQ)
				revisarCambio(QUIETO);
			//return;
	}

//	if (keystates[SDLK_UP]){
//		//if (!saltando){
//		if (controlable->obtenerEstado()!=SALTANDODER && controlable->obtenerEstado()!=SALTANDOIZQ){
//			saltando = true;
//			quieto = false;
//			//lo pongo en falso para que si se estaba ya movimiendo hacia algun lado,
//			//tambien se mande esa actualizacion
//			derecha = izquierda = false;
//			enviarStruct(SALTAR);
//		}
//	}else saltando = false;
//
//	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
//		if (!izquierda){
//			quieto = false;
//			derecha = false;
//			izquierda = true;
//			enviarStruct(CAMINANDOIZQ);
//		}
//	}else izquierda = false;
//
//	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
//		if (!derecha){
//			quieto = false;
//			izquierda = false;
//			derecha = true;
//			enviarStruct(CAMINANDODER);
//		}
//	}else derecha = false;
//
//	if (!derecha && !izquierda && !saltando && !quieto){
//		quieto = true;
//		enviarStruct(QUIETO);
//	}

}

void ControladorCliente::enviarStruct(int nuevoEstado){
	structCliente_t* estructura = structCliente_crear(ID, nuevoEstado);
	Cliente *cliente = Cliente::obtenerInstancia("", 0);
	cliente->encolar_cambio(estructura);
	mantieneVivo->detener();
	mantieneVivo->comenzar();
}

void ControladorCliente::revisarCambio(int cambio){
	if (ultimoEstado != cambio){
		enviarStruct(cambio);
		ultimoEstado = cambio;
	}
}
