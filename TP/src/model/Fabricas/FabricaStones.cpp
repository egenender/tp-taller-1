#include "FabricaStones.h"
#include "../Personajes/PowerUps/Stone.h"
#include "../Area.h"
#include "../../controller/GestorConfiguraciones.h"

FabricaStones::FabricaStones() {
}

FabricaStones::~FabricaStones() {

}

void FabricaStones::fabricar(Posicion* inicial, int valor){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("piedraEvolucion");

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY() - parametros->alto));
	Stone* piedra = new Stone ("piedraEvolucion", sup, parametros->velocidad);
	gestor->crearVista(piedra, "piedraEvolucion");
}
