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

	int x = inicial->obtenerX();
	int y = inicial->obtenerY();

	definirXY(&x, &y, inicial, valor, parametros->ancho, parametros->alto);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(x,y));
	VidaExtra* vida = new VidaExtra ("vidaExtra", sup, parametros->velocidad);
	gestor->crearVista(vida, "vidaExtra");
}

