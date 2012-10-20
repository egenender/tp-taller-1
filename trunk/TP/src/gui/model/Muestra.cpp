#include "Muestra.h"

Muestra::Muestra(Label* lbln, Label* lblv, Label* lbls, int x, int y, int ancho, int alto): ObjetoGUI(x,y,ancho,alto) {
	personajes = new vector<TipoProtagonista*>();
	seleccion = 0;
	nombre = lbln;
	velocidad = lblv;
	salto = lbls;
}

Muestra::~Muestra() {
	delete (personajes);
	//no lo que esta adentro
}
void Muestra::agregarVista (TipoProtagonista* newElem){
	newElem->animacionPasivaProt->transparencia(255,0,255);
	personajes->push_back(newElem);
	huboCambios();
}
void Muestra::eliminarVista (unsigned int elim){
	if (elim >= personajes->size())return;

	unsigned int final = personajes->size();
	unsigned int i;
	for (i = 0;i < final; i++){
		TipoProtagonista* elem = personajes->at(0);
		personajes->pop_back();
		if (i!=elim)
			personajes->push_back(elem);
		huboCambios();
	}
}

void Muestra::siguiente(){
	if (seleccion + 1  < personajes->size()){
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


bool Muestra::dibujar(SDL_Surface* display){
	if (personajes->size() == 0) return true;

	nombre->setearMensaje(personajes->at(seleccion)->nombre);

//	string vel = " "+(personajes->at(seleccion)->velocidad);
//	velocidad->setearMensaje(vel);
//	//salto->setearMensaje(""+personajes->at(seleccion)->salto);

	personajes->at(seleccion)->animacionPasivaProt->animar();
	return personajes->at(seleccion)->animacionPasivaProt->dibujar(display,obtenerX(),obtenerY());
}
