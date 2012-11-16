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

	int x = inicial->obtenerX();
	int y = inicial->obtenerY();

	definirXY(&x, &y, inicial, valor, parametros->ancho, parametros->alto);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(x,y));
	Stone* piedra = new Stone ("piedraEvolucion", sup, parametros->velocidad);
	gestor->crearVistaElemento(piedra, "piedraEvolucion");
}
