#include "FabricaActualizable.h"

FabricaActualizable::FabricaActualizable() {
	// TODO Auto-generated constructor stub

}

FabricaActualizable::~FabricaActualizable() {
	// TODO Auto-generated destructor stub
}

void FabricaActualizable::definirXY(int* x, int* y, Posicion* pos, int sentido,int ancho, int alto){

	if (sentido == DERECHA_FABR){
		*x = pos->obtenerX();
		*y = pos->obtenerY() - alto;

	}

	if (sentido == IZQUIERDA_FABR){
		*x = pos->obtenerX() - ancho;
		*y = pos->obtenerY() - alto;
	}

	if (sentido == ARRIBA_FABR){
		*x = pos->obtenerX() - (ancho/2);
		*y = pos->obtenerY() - alto;
	}

	if (sentido == ABAJO_FABR){
		*x = pos->obtenerX() - (ancho/2);
		*y = pos->obtenerY();
	}
}
