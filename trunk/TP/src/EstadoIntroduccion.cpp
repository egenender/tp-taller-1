#include "EstadoIntroduccion.h"
#include "HojaSprites.h"
#include "ManejadorEstados.h"

EstadoIntroduccion EstadoIntroduccion::instancia;

// Introduccion del juego
EstadoIntroduccion::EstadoIntroduccion() {

	// constructor... inicializar las cosas a un estado valido inicial

	camara = NULL;
	fondo = NULL;
	yoshiNormal = NULL;
	yoshiGigante = NULL;
	espejada = NULL;
	original = NULL;
	x = y = dx = dy =0;
}

/** Inicializa el estado **/
void EstadoIntroduccion::iniciar() {

	// Aca se inicializa lo referente al estado, es decir, crear los cuerpos, vistas, etc.

	// iniciamos la camara:
	camara = new Camara(x,y);

	// cargamos el fondo:
	fondo = new Superficie("src/fondoGrande.png");

	// cargamos los cuerpos:
	HojaSprites* normal = new HojaSprites("src/yoshi.bmp", 64, 64);
	// color transparente: rosa
	normal->transparencia(255, 0, 255);

	HojaSprites* gigante = new HojaSprites("src/yoshi.bmp", 64, 64);
	gigante->escala(2);
	gigante->transparencia(255, 0, 255);

	// TODO: hacer que funcione esta linea:
//	gigante = gigante->voltear(HORIZONTALMENTE);

	// Yoshi del tamanio del original de la imagen:
	yoshiNormal = new Animacion(normal);

	// Yoshi del doble del tamanio
	yoshiGigante = new Animacion(gigante);

	// Simplemente se carga la hoja de sprites:
	original = new Superficie("src/yoshi.bmp");
	original->transparencia(255, 0, 255);

	// Aca espejamos horizontalmente la anterior hoja:
	espejada = original->voltear(HORIZONTALMENTE);
}

/** Termina el estado **/
void EstadoIntroduccion::terminar() {

	// Aca tenemos que eliminar lo que reservamos para este estado

	delete (yoshiNormal);
	yoshiNormal = NULL;

	delete (yoshiGigante);
	yoshiGigante = NULL;

	delete (espejada);
	espejada = NULL;

	delete (original);
	original = NULL;

	delete (fondo);
	fondo = NULL;
}

/** Actualiza el estado **/
void EstadoIntroduccion::actualizar() {

	// Se actualizan todos los cuerpos
	// Se actualizan las vistas (o no, depende como sea implementado el patron observador - observable!)
	// Se verifican colisiones
	// Se elimina lo que se tenga que eliminar




	// Actualizamos la posicion de los cuerpos:
	x += dx;
	y += dy;

	// Actualizamos la posicion de la camara:
	camara->actualizar(x,y,64,64);

	// Hacemos actuar a las vistas: (si, no son vistas aun, pero esto harían las vistas)
	yoshiNormal->animar();
	yoshiGigante->animar();


	// Aca se deberia cambiar a otro estado cuando se cumpla una determinada condicion
	// Por ejemplo, cuando termino el nivel, o lo que sea...
}

/** Dibuja el estado **/
void EstadoIntroduccion::dibujar(SDL_Surface* display) {

	// Obtenemos el "area" que esta mostrando la camara:
	SDL_Rect* dimensiones = camara->obtenerDimensiones();

	// Dibujamos el fondo, mostrando solo la parte que dibuja la camara:
	fondo->dibujar(display, 0, 0, dimensiones);



	/* Aca se llamaria al dibujar de todas las vistas.
	* Guarda, tener en cuenta que se dibujan por orden, o sea,
	* se van a solapar en el orden en que son llamados:
	*/


	/* Tener en cuenta que su posicion es respecto a la camara!! */
	yoshiNormal->dibujar(display, 0 - dimensiones->x, 0 - dimensiones->y);
	yoshiNormal->dibujar(display, 24 - dimensiones->x, 0 - dimensiones->y);
	yoshiGigante->dibujar(display, x - dimensiones->x, y - dimensiones->y);
	original->dibujar(display, 200 - dimensiones->x, 0 - dimensiones->y);
	espejada->dibujar(display, 300 - dimensiones->x, 0 - dimensiones->y);
}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion* EstadoIntroduccion::obtenerInstancia() {
	return &instancia;
}


/** Maneja eventos que vienen del teclado **/
void EstadoIntroduccion::manejarEvento(SDL_Event* evento) {

	// Aca se verifican las teclas que utilice el usuario, y se hace actuar al cuerpo respecto a ello.

	// Otras acciones tambien se podrían verificar aca, como ser botones o menues o esas mierdas (?)

	// Las de cerrar la aplicacion, maximixar, etc, eso se verifica antes, en la clase Evento! Aca no.



	// Si, ya se que aca no utilizo evento, pero bueno. Shit happens (?)

	// Actualizamos la posicion de yoshi, tomando desde teclado:
	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Podria ser mejor :P Movimiento medio choto este:
	if (keystates[SDLK_UP])
		dy-=1;
	if (keystates[SDLK_DOWN])
		dy+=1;
	if (keystates[SDLK_LEFT])
		dx-=1;
	if (keystates[SDLK_RIGHT])
		dx+=1;
	if (!keystates[SDLK_UP] && !keystates[SDLK_DOWN] && !keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT])
		dx = dy = 0;
}