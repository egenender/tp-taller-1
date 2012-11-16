#include "FabricaBarriles.h"
#include "../Area.h"
#include "../../controller/GestorConfiguraciones.h"

FabricaBarriles::FabricaBarriles() {

}

FabricaBarriles::~FabricaBarriles() {

}

void FabricaBarriles::fabricar(Posicion* inicial, int valorInicial){

	parametrosPersonaje* parametros = GestorConfiguraciones::getInstance()->obtenerParametrosPersonaje("barril");

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY() - parametros->alto-1));
	Barril* barril = new Barril ("barril", sup, parametros->velocidad, valorInicial);

	terminarCreacion(barril);
}

void FabricaBarriles::terminarCreacion(Barril* b){
	GestorConfiguraciones::getInstance()->crearVistaElemento(b, "barril");
}
