#include "FabricaInvencibilidad.h"
#include "../Personajes/PowerUps/Invencibilidad.h"
#include "../Area.h"
#include "../../controller/GestorConfiguraciones.h"
FabricaInvencibilidad::FabricaInvencibilidad() {

}

FabricaInvencibilidad::~FabricaInvencibilidad() {

}

void FabricaInvencibilidad::fabricar(Posicion* inicial, int valor){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("invencibilidad");

	int x = inicial->obtenerX();
	int y = inicial->obtenerY();

	definirXY(&x, &y, inicial, valor, parametros->ancho, parametros->alto);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(x,y));
	Invencibilidad* inv = new Invencibilidad ("invencibilidad", sup, parametros->velocidad);
	gestor->crearVista(inv, "invencibilidad");
}

