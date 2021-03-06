#include "Aplicacion.h"
#include "../controller/ManejadorEstados.h"
#include "GestorConfiguraciones.h"
#include "../log/Log.h"
#include "../view/FPS.h"
#include "../common/Fuente.h"
#include "Cliente.h"
#include "Server.h"
#include "LectorArchivo.h"
#include "EscrituraArchivo.h"
#include "ManejadorCliente.h"
#include "SDL/SDL_mixer.h"

#include "../view/Superficie.h"
#include "../view/VistaProtagonista.h"

#include <sstream>
using namespace std;

/** Constructor **/
Aplicacion::Aplicacion() {
	FPS_ON = true;
	ventana = NULL;
	corriendo = true;
	Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Aplicacion creada correctamente.");
}

/** Iniciar las cosas: **/
bool Aplicacion::iniciar() {
	// Iniciamos SDL:
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    	Log::getInstance()->writeToLogFile(Log::ERROR, "Imposible iniciar SDL.");
    	return false;
    }

    Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "SDL iniciada correctamente.");

    // Creamos la ventana:
    //if((display = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)

    if((ventana=new Ventana(ANCHO_ESTANDARD,ALTO_ESTANDARD))==NULL)
    	return false;

    /*if ((ventana = new Ventana()) == NULL)
    	return false;*/

    Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Ventana creada correctamente.");

	// Para algo servia:
	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	if (!Fuente::obtenerInstancia()->inicializar())
		return false;

	 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
		 Log::getInstance()->writeToLogFile(Log::ERROR, "No se pudo incializar el Mixer, no se reproducirá ningun sonido");
	 }

    // Seteamos el primer estado al entrar al juego:
    ManejadorEstados::setearEstadoActual(ESTADO_MENU);

    SDL_initFramerate(&frames);
    if (SDL_setFramerate(&frames, 24) == -1)
       	Log::getInstance()->writeToLogFile(Log::ADVERTENCIA, "No se pudo incializar a 24 fps");

    return true;
}

/** Manejar eventos (teclado, mouse, etc) **/
void Aplicacion::manejarEvento(SDL_Event* evento) {
	if (!ventana)
		return;

	ventana->manejarEvento(evento);
	ManejadorEstados::manejarEvento(evento);
}

/** Actualizar **/
void Aplicacion::actualizar(float delta) {
	ManejadorEstados::actualizar(delta);
}

/** Dibujar **/
void Aplicacion::dibujar() {

	if (!ventana)
		return;

	// Primero limpiamos la pantalla:
	ventana->limpiarPantalla();

    // Mostramos los FPS:
    if (FPS_ON) {
    	stringstream out;
    	out << "DonkeyMon!" <<" - FPS: " << SDL_getFramerate(&frames) << " - FPS_old: " << FPS::ControlFPS.obtenerFPS() << " - Delta: " << FPS::ControlFPS.obtenerDelta();
    	ventana->setearTitulo(out.str());
    }

	// Ahora dibujamos las cosas:
    ManejadorEstados::dibujar(ventana->obtenerSuperficieDibujable()->obtenerSurface());

    // Y actualizamos:
    ventana->dibujar();
}

/** Liberar toda la memoria **/
void Aplicacion::limpiar() {
    ManejadorEstados::setearEstadoActual(ESTADO_NINGUNO);

    Fuente::obtenerInstancia()->terminar();

    if(ventana) {
    	delete(ventana);
    	ventana = NULL;
    }

    Mix_CloseAudio();
    SDL_Quit();
}

/** Al salir de la aplicacion **/
void Aplicacion::salir() {
	corriendo = false;
	Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Fin de aplicacion.");
}

/** Gameloop */
int Aplicacion::ejecutar() {
	if (iniciar() == false)
		return -1;

	SDL_Event evento;
	while (corriendo) {

		FPS::ControlFPS.actualizar();

		while (SDL_PollEvent(&evento)) {
			Evento::manejarEvento(&evento);
		}

		SDL_PumpEvents();
		manejarEvento(&evento);

		actualizar(FPS::ControlFPS.obtenerDelta());
		dibujar();

		ManejadorEstados::cambiarEstado();
		GestorConfiguraciones::getInstance()->destruirGestor();
		SDL_Delay(30);
		SDL_framerateDelay(&frames);
	}
	limpiar();
	return 0;
}

/** Setea si se muestran por pantalla los Frames Por Segundo o no **/
void Aplicacion::mostrarFPS(bool mostrar) {
	FPS_ON = mostrar;
}

/** Se ejecuta el programa **/
int main(int argc, char* argv[]) {
	Aplicacion aplicacion;
	srand ( time(NULL) );
	return aplicacion.ejecutar();
}
