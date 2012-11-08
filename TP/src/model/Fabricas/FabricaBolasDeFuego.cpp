#include "FabricaBolasDeFuego.h"
#include "../Area.h"
#include "../../controller/GestorConfiguraciones.h"

FabricaBolasDeFuego::FabricaBolasDeFuego(std::string nom) {
	nombre = nom;
	bola = NULL;
}

FabricaBolasDeFuego::~FabricaBolasDeFuego() {

}

void FabricaBolasDeFuego::fabricar(Posicion* inicial,int valor){
	//Si al bola de fuego anterior que cree, sigue viva, no puedo crear otra
	if (bola!= NULL){
		if (!bola->estaMuerto())
			return;
	}
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	std::string aux = "bola";
	aux += nombre;

	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje(aux);

	Area* sup = new Area(parametros->ancho, parametros->alto, new Posicion(inicial->obtenerX(), inicial->obtenerY()));
	//REVISAR de agregarle el salto!
	bola = new BolaDeFuego (aux.c_str(), sup, parametros->velocidad, parametros->velocidad, valor);
	gestor->crearVista(bola, aux);
}

