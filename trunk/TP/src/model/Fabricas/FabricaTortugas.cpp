#include "FabricaTortugas.h"
#include "../Personajes/Tortuga.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../Area.h"

FabricaTortugas::FabricaTortugas() {

}

FabricaTortugas::~FabricaTortugas() {

}

void FabricaTortugas::fabricar(Posicion* inicial,int valor){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("tortuga");

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY()));
	Tortuga* tortuga = new Tortuga ("tortuga", sup, parametros->velocidad);
	gestor->crearVista(tortuga, "tortuga");
}
