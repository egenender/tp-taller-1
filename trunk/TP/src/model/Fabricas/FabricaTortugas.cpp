#include "FabricaTortugas.h"
#include "../Personajes/Tortuga.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../Area.h"

FabricaTortugas::FabricaTortugas() {

}

FabricaTortugas::~FabricaTortugas() {

}

void FabricaTortugas::fabricar(Posicion* inicial,int sentido){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("tortuga");

	int x = inicial->obtenerX();
	int y = inicial->obtenerY();

	definirXY(&x, &y, inicial, sentido, parametros->ancho, parametros->alto);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(x,y));
	Tortuga* tortuga = new Tortuga ("tortuga", sup, parametros->velocidad);
	gestor->crearVistaElemento(tortuga, "tortuga");
}
