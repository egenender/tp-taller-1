#include "Muestra.h"

Muestra::Muestra(int x, int y, int ancho, int alto): ObjetoGUI(x,y,ancho,alto) {
	vectorcito = new vector<VistaProtagonista*>();
	seleccion = 0;
}

Muestra::~Muestra() {
	delete (vectorcito);
	//no lo que esta adentro
}
void Muestra::agregarVista (VistaProtagonista* newElem){
	vectorcito->push_back(newElem);
	huboCambios();
}
void Muestra::eliminarVista (unsigned int elim){
	if (elim >= vectorcito->size())return;

	unsigned int final = vectorcito->size();
	unsigned int i;
	for (i = 0;i < final; i++){
		VistaProtagonista* elem = vectorcito->at(0);
		vectorcito->pop_back();
		if (i!=elim)
			vectorcito->push_back(elem);
		huboCambios();
	}
}

void Muestra::siguiente(){
	if (seleccion + 1  < vectorcito->size()){
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

VistaProtagonista* Muestra::obtenerActual(){
	if (vectorcito->size() == 0) return NULL;
	if (seleccion >= vectorcito->size()) return NULL;
	else return (vectorcito->at(seleccion));
}
