#include "FabricaActivaEspeciales.h"
#include "../Personajes/PowerUps/ActivaEspecial.h"
#include "../Area.h"
#include "../../controller/GestorConfiguraciones.h"


FabricaActivaEspeciales::FabricaActivaEspeciales() {

}

FabricaActivaEspeciales::~FabricaActivaEspeciales() {

}

void FabricaActivaEspeciales::fabricar(Posicion* inicial, int valor){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje("activaEspecial");

	int x = inicial->obtenerX();
	int y = inicial->obtenerY();

	definirXY(&x, &y, inicial, valor, parametros->ancho, parametros->alto);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(x,y));
	ActivaEspecial* especial = new ActivaEspecial ("activaEspecial", sup, parametros->velocidad);
	gestor->crearVista(especial, "activaEspecial");
}
