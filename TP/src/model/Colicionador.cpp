#include "Colisionador.h"
#include <stdbool.h>
using namespace std;

bool colisionan(Actualizable*, Actualizable*);
void colisionar(Actualizable*, Actualizable*);

void generarColisiones (vector<Actualizable*>* actualizables){
	Actualizable *primero, *segundo;

	for (unsigned int i = 0; i < actualizables->size(); i++){
		primero = actualizables->at(i);
		for (unsigned int j = 0; j < actualizables->size(); j++){
			if (j != i){
				segundo = actualizables->at(j);
				if (colisionan(primero, segundo))
					colisionar(primero,segundo);
			}
		}
	}

}


bool colisionan(Actualizable* primero, Actualizable* segundo){
	Area *area1 = primero->obtenerArea();
	Area *area2 = segundo->obtenerArea();

	bool huboColision = (area1->colisionaConOtra(area2) || area2->colisionaConOtra(area2));
	return huboColision;
}

void colisionar(Actualizable* primero, Actualizable* segundo){
	//TODO
	//Para este commmit no hago nada
}
