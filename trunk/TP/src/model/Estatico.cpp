#include "Estatico.h"

Estatico::Estatico(const char* nombre, Area* sup): Cuerpo(nombre, sup) {
	// TODO Auto-generated constructor stub

}

Estatico::~Estatico() {
	// TODO Auto-generated destructor stub
}

int Estatico::obtenerEstado(){
	//Estatico tiene el estado estatico
	return 0;
}

void Estatico::actualizar(float delta){
	//No hace nada
}
