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

	int x = inicial->obtenerX();
	int y = inicial->obtenerY();
	definirXY(&x, &y, inicial, valor, parametros->ancho, parametros->alto);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(x,y));
	Hongo* hongo = new Hongo ("hongo", sup, parametros->velocidad);
	gestor->crearVista(hongo, "hongo");
}
