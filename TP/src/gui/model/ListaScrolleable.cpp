/*
 * ListaScrolleable.cpp
 *
 *  Created on: 14/10/2012
 *      Author: martin
 */

#include "ListaScrolleable.h"

ListaScrolleable::ListaScrolleable(int x, int y, int ancho, int alto):ObjetoGUI(x,y,ancho,alto) {
	seleccionado = 0;
	vectorcito = new vector<string>();
}

ListaScrolleable::~ListaScrolleable() {
	delete (vectorcito);
}

void ListaScrolleable::moverHaciaArriba(){
	if (seleccionado > 0){
		seleccionado--;
		huboCambios();
	}

}
void ListaScrolleable::moverHaciaAbajo(){
	if (seleccionado < vectorcito->size()-1){
		seleccionado++;
		huboCambios();
	}
}

void ListaScrolleable::agregarElemento(string newElem){
	vectorcito->push_back(newElem);
	huboCambios();
}

void ListaScrolleable::eliminarElemento(unsigned int eliminar){
	if (eliminar >= vectorcito->size())return;

	unsigned int final = vectorcito->size();
	unsigned int i;
	for (i = 0;i < final; i++){
		string elem = vectorcito->at(0);
		vectorcito->pop_back();
		if (i!=eliminar)
			vectorcito->push_back(elem);
		huboCambios();
	}

}

string ListaScrolleable::obtenerSeleccionado(){
	return vectorcito->at(seleccionado);
}
unsigned int ListaScrolleable::indiceSeleccionado(){
	return seleccionado;
}

string ListaScrolleable::obtenerElemento(unsigned int elem){
	return vectorcito->at(elem);
}

unsigned int ListaScrolleable::cantidad(){
	return vectorcito->size();
}
