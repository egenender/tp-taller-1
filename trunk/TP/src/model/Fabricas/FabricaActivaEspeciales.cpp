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

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY() - parametros->alto));
	ActivaEspecial* especial = new Stone ("activaEspecial", sup, parametros->velocidad);
	gestor->crearVista(especial, "activaEspecial");
}
