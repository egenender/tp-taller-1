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
	int vel , dir;

	if (valor < 0){
		vel = -valor;
		dir = -1;
	}else{
		vel = valor;
		dir = 1;
	}

	bola = new BolaDeFuego (aux.c_str(), sup, vel, parametros->velocidad, dir);
	gestor->crearVista(bola, aux);
}

