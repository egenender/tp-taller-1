#include "ManejadorScroll.h"

ManejadorScroll::ManejadorScroll(ListaScrolleable* lista, int factor) {
	direccion = factor;
	scroll = lista;
}

ManejadorScroll::~ManejadorScroll() {

}

void ManejadorScroll::manejarClic(){
	if (direccion == ARRIBA){
		scroll->moverHaciaArriba();
	}else{
		scroll->moverHaciaAbajo();
	}
}
