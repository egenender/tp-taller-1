#include "FabricaVidasExtra.h"
#include "../Personajes/PowerUps/VidaExtra.h"
#include "../Area.h"
#include "../../controller/GestorConfiguraciones.h"
FabricaVidasExtra::FabricaVidasExtra() {

}

FabricaVidasExtra::~FabricaVidasExtra() {

}

void FabricaVidasExtra::fabricar(Posicion* inicial, int valor){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("vidaExtra");

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY() - parametros->alto));
	VidaExtra* vida = new VidaExtra ("vidaExtra", sup, parametros->velocidad);
	gestor->crearVista(vida, "vidaExtra");
}

