#include "ManejadorCooperativo.h"
#include "../../model/Personajes/Manual.h"
#include "../../model/Personajes/BolaDeFuego.h"

ManejadorCooperativo::ManejadorCooperativo() {
	check = NULL;
}

ManejadorCooperativo::~ManejadorCooperativo() {
}

void ManejadorCooperativo::manejarClic(){
	if (!check) return;
	Manual::setearCooperatividad(check->esCheckeado());
	BolaDeFuego::setearCooperatividad(check->esCheckeado());
}

void ManejadorCooperativo::setearCheckbox(Checkbox* c){
	check = c;
}

