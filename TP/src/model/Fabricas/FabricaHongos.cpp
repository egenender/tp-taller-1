#include "FabricaHongos.h"
#include "../Area.h"
#include "../Personajes/Hongo.h"
#include "../../controller/GestorConfiguraciones.h"

FabricaHongos::FabricaHongos() {

}

FabricaHongos::~FabricaHongos() {

}

void FabricaHongos::fabricar(Posicion* inicial, int valor){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("hongo");

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY() - parametros->alto));
	Hongo* hongo = new Hongo ("hongo", sup, parametros->velocidad);
	gestor->crearVista(hongo, "hongo");
}
