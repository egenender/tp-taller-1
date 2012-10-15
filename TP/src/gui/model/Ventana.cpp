#include "Ventana.h"
#include "../../log/Log.h"

void Ventana::inicializar() {
	screen = NULL;
	superficieDibujable = NULL;
	ventanaOK = false;
	modoVentana = false;
	ancho = alto = 0;
	anchoOriginal = altoOriginal = 0;
}

Ventana::~Ventana() {
	if (screen) {
		SDL_FreeSurface(screen);
		screen = NULL;
	}

	if (superficieDibujable) {
		delete(superficieDibujable);
		superficieDibujable = NULL;
	}
}

Ventana::Ventana() {
	inicializar();
	screen = SDL_SetVideoMode(ANCHO_ESTANDARD, ALTO_ESTANDARD, 32,
			SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);

	if (screen == NULL) {
		ventanaOK = false;
		return;
	}

	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_ESTANDARD, ALTO_ESTANDARD, 32, 0, 0, 0, 0);

	if (temp == NULL) {
		ventanaOK = false;
		return;
	}

	superficieDibujable = new Superficie(temp);

	if (superficieDibujable == NULL) {
		SDL_FreeSurface(temp);
		ventanaOK = false;
		return;
	}

	ventanaOK = true;
	modoVentana = true;
	ancho = anchoOriginal = ANCHO_ESTANDARD;
	alto = altoOriginal = ALTO_ESTANDARD;

}

Ventana::Ventana(int ancho, int alto) {
	inicializar();
	if (ancho > 0 && alto > 0) {
		screen = SDL_SetVideoMode(ancho, alto, 32,
				SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
		this->ancho = anchoOriginal = ancho;
		this->alto = altoOriginal = alto;
	} else {
		screen = SDL_SetVideoMode(ANCHO_ESTANDARD, ALTO_ESTANDARD, 32,
				SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
		this->ancho = anchoOriginal = ANCHO_ESTANDARD;
		this->alto = altoOriginal = ALTO_ESTANDARD;
	}

	if (screen == NULL) {
		ventanaOK = false;
		return;
	}

	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, ANCHO_ESTANDARD, ALTO_ESTANDARD, 32, 0, 0, 0, 0);

	if (temp == NULL) {
		ventanaOK = false;
		return;
	}

	superficieDibujable = new Superficie(temp);

	if (superficieDibujable == NULL) {
		SDL_FreeSurface(temp);
		ventanaOK = false;
		return;
	}

	ventanaOK = true;
	modoVentana = true;
}

void Ventana::setearTitulo(string titulo) {
	if (ventanaOK)
		SDL_WM_SetCaption(titulo.c_str(), NULL);
}

void Ventana::redimencionar(int ancho, int alto) {
	if (ancho == this->ancho && alto == this->alto)
		return;

	if (modoVentana && ventanaOK) {
		if (ancho > 0 && alto > 0) {
			screen = SDL_SetVideoMode(ancho, alto, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);

			if (screen == NULL) {
				ventanaOK = false;
				return;
			}

			this->ancho = ancho;
			this->alto = alto;
		}
	}
}

void Ventana::pantallaCompleta() {
	//If the screen is windowed
	if (modoVentana) {
		//Set the screen to fullscreen
		screen = SDL_SetVideoMode(ancho, alto, 32,
				SDL_HWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
		//If there's an error
		if (screen == NULL) {
			ventanaOK = false;
			return;
		}
		//Set the window state flag
		modoVentana = false;
	}
	//If the screen is fullscreen
	else if (!modoVentana) {
		//Window the screen
		screen = SDL_SetVideoMode(ancho, alto, 32,
				SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
		//If there's an error
		if (screen == NULL) {
			ventanaOK = false;
			return;
		}
		//Set the window state flag
		modoVentana = true;
	}
}

void Ventana::manejarEvento(SDL_Event* evento) {
	//If there's something wrong with the window
	if (!ventanaOK)
		return;
	//If the window resized
	if (evento->type == SDL_VIDEORESIZE) {
		//Resize the screen
		screen = SDL_SetVideoMode(evento->resize.w, evento->resize.h, 32,	SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
		//If there's an error
		if (screen == NULL) {
			ventanaOK = false;
			return;
		}

		ancho = evento->resize.w;
		alto = evento->resize.h;

	//	superficieDibujable->escala(ancho,alto);
	}

	//If ESC was pressed
	else if( ( evento->type == SDL_KEYDOWN ) && ( evento->key.keysym.sym == SDLK_ESCAPE) ) {
		//Turn fullscreen on/off
		pantallaCompleta();
	}

	//If the window focus changed
/*	else if( evento->type == SDL_ACTIVEEVENT ) {
		//If the window was iconified or restored
		if( evento->active.state & SDL_APPACTIVE ) {
			//If the application is no longer active
			if( evento->active.gain == 0 ) {
				Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Ventana minimizada");
			}
			else {
				Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Ventana restaurada");
			}
		}
		 //If something happened to the keyboard focus
		else if( evento->active.state & SDL_APPINPUTFOCUS ) {
			//If the application lost keyboard focus
			if( evento->active.gain == 0 ) {
//				Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "El teclado perdio foco");
			}
			else {
//				Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "El teclado gano foco");
			}
		}
		//If something happened to the mouse focus
		else if( evento->active.state & SDL_APPMOUSEFOCUS ) {
			//If the application lost mouse focus
			if( evento->active.gain == 0 ) {
//				Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "El mouse perdio foco");
			}
			else {
//				Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "El mouse gano foco");
			}
		}
	}
	 //If the window's screen has been altered
	else if( evento->type == SDL_VIDEOEXPOSE ) {
		//Update the screen
		if( SDL_Flip( screen ) == -1 ) {
			//If there's an error
			ventanaOK = false;
			return;
		}
	}*/
}

bool Ventana::error() {
	return !ventanaOK;
}

Superficie* Ventana::obtenerSuperficieDibujable() {
	return superficieDibujable;
}

void Ventana::limpiarPantalla() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_FillRect(superficieDibujable->obtenerSurface(), NULL, SDL_MapRGB(superficieDibujable->obtenerSurface()->format, 0, 0, 0));
}

void Ventana::dibujar() {
//	superficieDibujable->escala(ancho,alto);
    superficieDibujable->dibujar(screen, 0, 0);
    SDL_Flip(superficieDibujable->obtenerSurface());
    SDL_Flip(screen);
}

void Ventana::volverALasDimensionesDeCreacion() {
	redimencionar(anchoOriginal, altoOriginal);
}
