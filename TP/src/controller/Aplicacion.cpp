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

#include "../model/Manual.h"
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
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	// Iniciamos SDL:
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    	Log::getInstance()->writeToLogFile(Log::ERROR, "Imposible iniciar SDL.");
    	return false;
    }

    Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "SDL iniciada correctamente.");

    // Creamos la ventana:
    //if((display = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)

    if((ventana=gestor->CrearPantalla())==NULL)
    	return false;

    /*if ((ventana = new Ventana()) == NULL)
    	return false;*/

    Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Ventana creada correctamente.");

	// Para algo servia:
	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	if (!Fuente::obtenerInstancia()->inicializar())
		return false;

    // Seteamos el primer estado al entrar al juego:
    ManejadorEstados::setearEstadoActual(ESTADO_GUI);

    return true;
}

/** Manejar eventos (teclado, mouse, etc) **/
void Aplicacion::manejarEvento(SDL_Event* evento) {
	ventana->manejarEvento(evento);
	ManejadorEstados::manejarEvento(evento);
}

/** Actualizar **/
void Aplicacion::actualizar(float delta) {
	ManejadorEstados::actualizar(delta);
}

/** Dibujar **/
void Aplicacion::dibujar() {

	// Primero limpiamos la pantalla:
	ventana->limpiarPantalla();

    // Mostramos los FPS:
    if (FPS_ON) {
    	stringstream out;
    	out << "FPS: " << FPS::ControlFPS.obtenerFPS() << " - Delta: " << FPS::ControlFPS.obtenerDelta();
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

//	Server servidor;
//
//	servidor.escribir(sizeof(int));
//	servidor.escuchar(sizeof(int));
//
//	SDL_Delay(1000);
//
//	Cliente client;
//
//	client.escuchar(sizeof(int));

/*	//Superficie* prueba = new Superficie ( "resources/cruzCuadroError4.png" );
	SDL_Surface* sdlPrueba = NULL;
	sdlPrueba = IMG_Load( "src/resources/cruzCuadroError4.png" );

	size_t lala = sizeof(*sdlPrueba);

	SDL_Surface* lolo = (SDL_Surface*) malloc (lala);
	*lolo = *sdlPrueba;

	cout << sdlPrueba << endl;*/


//	char* ruta = (char*) malloc (90*sizeof(char));
//	sprintf(ruta,"%s %s","mkdir","Temp");
//	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
//	system(ruta);
//	sprintf(ruta,"%s %s","mkdir","Temp/src");
//	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
//	system(ruta);
//	sprintf(ruta,"%s %s","mkdir","Temp/src/resources");
//	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
//	system(ruta);
//	free(ruta);


	Server servidor;

	servidor.escuchar(sizeof(int));

	Cliente client;
	int largo;
	//leo largo de ruta
	largo = client.escuchar_un_entero();
	while (largo>0) {
		//leo ruta
		int* intNombre = client.escuchar_N_enteros(largo);
		char *nombre = (char*) malloc((largo)*sizeof(char));
		int i=0;
		while(i < largo){
			nombre[i] = (char) intNombre[i];
			i++;
		}
		free(intNombre);

		EscrituraArchivo* e = new EscrituraArchivo(nombre);
		free(nombre);

		//leo largo de todo
		largo = client.escuchar_un_entero();
		int j = 0;
		void* algo;

		//de a uno leo todo y lo escribo
		while(j<largo){
			algo = client.escuchar_al_server(sizeof(int));
			if (algo != NULL){
				e->EscribirUno(  *(int*) algo , largo);
				j++;
			}
		}

		e->CerrarArchivo();

		//leo largo de ruta
		largo = client.escuchar_un_entero();
	}


	//	VistaProtagonista* lili =
//	new VistaProtagonista(new Manual("r" , new Area (50,50,new Posicion(50,50))),
//			new Animacion(new HojaSprites(sdlPrueba,50,50)) ,
//								new Animacion(new HojaSprites(sdlPrueba,50,50)) );
//
//	lili->Observador();
//
//	int ent=9;
//	int* entero = (int*) malloc (sizeof (int));
//	*entero=ent;
//
//	servidor.encolar_cambio(entero);
//	servidor.encolar_cambio(entero);
//	servidor.encolar_cambio(entero);
//	servidor.encolar_cambio(entero);
//	servidor.encolar_cambio(entero);
//	servidor.encolar_cambio(entero);
//
//	int i = 0;
//	while (true){
//		if (client.hay_cambios()){
//			void* cambio=client.desencolar_cambio();
//			cout<< "cambio:" << *(int *) cambio << endl;
//			i++;
//		}
//		if (i== 6)
//			break;
//	}


//	client.escuchar(sizeof(int));
//
//	while (true){
//		if (  (client.hay_cambios() ) ){
//			void* cambio=client.desencolar_cambio();
//			cout << *(int*)cambio<< endl;
//		}
//	}
//	client.detener_escribir();

//	while(true){
//		//	while(true){
//
//		if(servidor.hay_cambios()){
//			void* cambio=servidor.desencolar_cambio();
//			cout<<"cambio:"<<*(int *) cambio << endl;
//		}
//	}

	//aplicacion.mostrarFPS(false);

	return aplicacion.ejecutar();
}
