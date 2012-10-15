#include "ManejadorScroll.h"

ManejadorScroll::ManejadorScroll(ListaScrolleable* lista, int factor) {
	direccion = factor;
	scroll = lista;
	anim = NULL;
}

ManejadorScroll::ManejadorScroll(ListaScrolleable* lista, int factor,Muestra* lamuestra) {
	direccion = factor;
	scroll = lista;
	anim = lamuestra;
}

ManejadorScroll::~ManejadorScroll() {

}

void ManejadorScroll::manejarClic(){
	if (direccion == ARRIBA){
		scroll->moverHaciaArriba();
		if (anim)
			anim->anterior();
	}else{
		scroll->moverHaciaAbajo();
		if (anim)
			anim->siguiente();
	}
}
