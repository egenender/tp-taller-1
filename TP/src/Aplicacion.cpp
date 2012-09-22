#include "Aplicacion.h"
#include "ManejadorEstados.h"
#include "GestorConfiguraciones.h"
#include "Log.h"
#include "FPS.h"

#include <sstream>
using namespace std;

/** Constructor **/
Aplicacion::Aplicacion() {
	FPS_ON = true;
	display = NULL;
	corriendo = true;
	Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Aplicacion creada correctamente.");
}

/** Iniciar las cosas: **/
bool Aplicacion::iniciar() {
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	// Iniciamos SDL:
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    	Log::getInstance()->writeToLogFile(Log::ERROR, "Imposible iniciar SDL.");
    	return false;
    }

    Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "SDL iniciada correctamente.");

    // Creamos la ventana:
    //if((display = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)

    if((display=gestor->CrearPantalla())==NULL)
    	return false;

    Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Ventana creada correctamente.");

	// Para algo servia:
	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    // Seteamos el primer estado al entrar al juego:
    ManejadorEstados::setearEstadoActual(ESTADO_INTRO);

    return true;
}

/** Manejar eventos (teclado, mouse, etc) **/
void Aplicacion::manejarEvento(SDL_Event* evento) {

	Evento::manejarEvento(evento);
	ManejadorEstados::manejarEvento(evento);
}

/** Actualizar **/
void Aplicacion::actualizar() {
	ManejadorEstados::actualizar();
}

/** Dibujar **/
void Aplicacion::dibujar() {

	// Primero limpiamos la pantalla:
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0));

    // Mostramos los FPS:
    if (FPS_ON) {
    	stringstream out;
    	out << "FPS: " << FPS::ControlFPS.obtenerFPS() << " - Delta: " << FPS::ControlFPS.obtenerDelta();
    	SDL_WM_SetCaption(out.str().c_str(), NULL);
    }

	// Ahora dibujamos las cosas:
    ManejadorEstados::dibujar(display);

    // Y actualizamos:
    SDL_Flip(display);
}

/** Liberar toda la memoria **/
void Aplicacion::limpiar() {
    ManejadorEstados::setearEstadoActual(ESTADO_NINGUNO);

    SDL_FreeSurface(display);
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
			manejarEvento(&evento);
		}

		actualizar();
		dibujar();
		SDL_Delay(35);
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

	//aplicacion.mostrarFPS(false);

	return aplicacion.ejecutar();
}
