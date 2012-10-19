#include "Muestra.h"

Muestra::Muestra(int x, int y, int ancho, int alto): ObjetoGUI(x,y,ancho,alto) {
	animaciones = new vector<Animacion*>();
	seleccion = 0;
}

Muestra::~Muestra() {
	delete (animaciones);
	//no lo que esta adentro
}
void Muestra::agregarVista (Animacion* newElem){
	animaciones->push_back(newElem);
	huboCambios();
}
void Muestra::eliminarVista (unsigned int elim){
	if (elim >= animaciones->size())return;

	unsigned int final = animaciones->size();
	unsigned int i;
	for (i = 0;i < final; i++){
		Animacion* elem = animaciones->at(0);
		animaciones->pop_back();
		if (i!=elim)
			animaciones->push_back(elem);
		huboCambios();
	}
}

void Muestra::siguiente(){
	if (seleccion + 1  < animaciones->size()){
		seleccion++;
		huboCambios();
	}
}

void Muestra::anterior(){
	if (seleccion > 0){
		seleccion--;
		huboCambios();
	}
}

Animacion* Muestra::obtenerActual(){
	if (animaciones->size() == 0) return NULL;
	if (seleccion >= animaciones->size()) return NULL;
	else return (animaciones->at(seleccion));
}
bool Muestra::dibujar(SDL_Surface* display){
	if (animaciones->size() == 0) return true;

	animaciones->at(seleccion)->animar();
	return animaciones->at(seleccion)->dibujar(display,obtenerX(),obtenerY());
}
