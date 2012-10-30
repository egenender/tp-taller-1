#include "Colisionador.h"
#include <stdbool.h>
#include <stdio.h>
#include "Cuerpo.h"
using namespace std;

bool colisionan(Actualizable*, Actualizable*);
void colisionar(Actualizable*, Actualizable*);

void generarColisiones (vector<Actualizable*>* actualizables){
	Actualizable *primero, *segundo;

	for (unsigned int i = 0; i < actualizables->size(); i++){
		primero = actualizables->at(i);
		for (unsigned int j = 0; j < actualizables->size(); j++){
			if (i == j) continue;
			segundo = actualizables->at(j);
			if (colisionan(primero, segundo))
				colisionar(primero,segundo);
		}
	}

}


bool colisionan(Actualizable* primero, Actualizable* segundo){
	Area *area1 = primero->obtenerArea();
	Area *area2 = segundo->obtenerArea();

	if (area1 == NULL) return false;
	if (area2 == NULL) return false;

	bool huboColision = (area1->colisionaConOtra(area2) || area2->colisionaConOtra(area1));
	return huboColision;
}

void colisionar(Actualizable* primero, Actualizable* segundo){
	//TODO
	//printf("HUBO COLISION\n");
	primero->chocarCon(segundo);
}
