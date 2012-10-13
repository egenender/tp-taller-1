#include "Boton.h"
#include <exception>

void Boton::inicializar() {
	clickeado = false;
	presionado = false;
	estaEncima = false;
	manejador = NULL;
	mensaje = "";
}

Boton::Boton(int x, int y, int ancho, int alto, ManejadorBoton* m) : ObjetoGUI::ObjetoGUI(x,y,ancho,alto){
	inicializar();
	manejador = m;
}

Boton::~Boton() {
	try{
		delete(manejador);
	}catch(exception& e){
		//Ya lo eliminaron, no hago nada
	}
}

void Boton::manejarEvento(SDL_Event* evento) {
	if (obtenerEstado() == INACTIVO)
		return;

	//TODO: Esto aca o en donde lo deje comentado?
	clickeado = false;

	if (evento->type == SDL_MOUSEMOTION) {
		estaEncima = mouseEncima(evento->motion.x, evento->motion.y);
	}

	if (evento->type == SDL_MOUSEBUTTONDOWN && estaEncima) {
		if (evento->button.button == SDL_BUTTON_LEFT) {
			setearPresionado(true);
			// clickeado = false;
		}
	}

	if (evento->type == SDL_MOUSEBUTTONUP) {
		if (evento->button.button == SDL_BUTTON_LEFT && esPresionado()) {
			setearPresionado(false);
			clickeado = true;
			manejador->manejarClic();
		}
	}

	huboCambios();
}

bool Boton::mouseEstaEncima() {
	return estaEncima;
}

bool Boton::esClickeado() {
	return clickeado;
}

bool Boton::esPresionado() {
	return presionado;
}

string Boton::obtenerMensaje() {
	return mensaje;
}

void Boton::setearMensaje(string texto) {
	mensaje = texto;
}

void Boton::setearPresionado(bool flag) {
	presionado = flag;
}
