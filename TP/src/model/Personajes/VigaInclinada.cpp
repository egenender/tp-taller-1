#include "VigaInclinada.h"
#include <math.h>

VigaInclinada::VigaInclinada(const char* nom, Area* sup, float alfa):Cuerpo(nom,sup) {
	angulo = 0;
	if (alfa < 90 && alfa > -90)
		angulo = alfa;

	if (angulo < 0){
		creceHacia = CRECE_DERECHA;
		angulo = -angulo;
	}else if (angulo > 0)
		creceHacia = CRECE_IZQUIERDA;
	else
		creceHacia = NINGUNO;

	plataformas = new vector<Plataforma*>();
	crearPlataformas();
}


void VigaInclinada::crearPlataformas(){

	if (angulo == 0){
		Posicion* pos = new Posicion(superficieOcupada->obtenerPosicion()->obtenerX(),superficieOcupada->obtenerPosicion()->obtenerY());
		Area* lugar = new Area(superficieOcupada->obtenerAncho(), superficieOcupada->obtenerAlto(), pos);
		Plataforma* unica = new Plataforma (" ", lugar);
		plataformas->push_back(unica);
		unica->setearDireccion(NINGUNO); //ya se hace por default, pero por si acaso :P
		return;
	}
	float PI = 3.14159265358979;
	float angulito = (angulo * PI)/180;

	float altoP = superficieOcupada->obtenerAlto();
	float cant = CANT_PLATAFORMAS;
	float anchoP;

	float anchoEst = superficieOcupada->obtenerAncho() * cos(angulito);
	if (cant > anchoEst)
		cant = anchoEst;
	cant+=2;
	float separacionX = 0;

	anchoP = superficieOcupada->obtenerAncho() * cos(angulito) / cant;
	if ((anchoP*cant) < (superficieOcupada->obtenerAncho() * cos(angulito)/2))
		separacionX = 1;


	float difAltura = superficieOcupada->obtenerAncho() * sin(angulito) / cant;

	float separacionY = 0;
	if ((difAltura*cant) < (superficieOcupada->obtenerAncho() * sin(angulito)/2))
		separacionY = 1;

	Posicion* pos;
	Area* sup;
	int x = superficieOcupada->obtenerPosicion()->obtenerX();
	int y = superficieOcupada->obtenerPosicion()->obtenerY();
	if (creceHacia == CRECE_IZQUIERDA)
		for (int i = 0; i < cant; i++){

			pos = new Posicion(x + anchoP*i + separacionX, y + (creceHacia)* (difAltura*i +separacionY));
			sup = new Area(anchoP, altoP, pos);
			Plataforma* plataforma = new Plataforma(" ", sup);
			plataformas->push_back(plataforma);
			plataforma->setearDireccion(CRECE_IZQUIERDA);
			if (i!= cant-1)
				plataforma->setearComoVigaPorDerecha();

		}
	else
		for (int i = cant-1; i >=0; i--){
			pos = new Posicion(x + anchoP*i + separacionX, y + (creceHacia)* (difAltura*i +separacionY));
			sup = new Area(anchoP, altoP, pos);
			Plataforma* plataforma = new Plataforma(" ", sup);
			plataformas->push_back(plataforma);
			plataforma->setearDireccion(CRECE_DERECHA);
			if (i != 0)
				plataforma->setearComoVigaPorIzquierda();
		}
	//si crece hacia la derecha, tengo que tener los elementos desde el de mas arriba hacia el de mas abajo
	//entonces tengo que darlos vuelta en el vector:
//	if (creceHacia == DERECHA){
//		vector<Plataforma*>* aux = new vector<Plataforma*>();
//
//		for (unsigned int j = (plataformas->size()-1); j >=0; j--){
//			aux->push_back(plataformas->at(j));
//		}
//		free(plataformas);
//		plataformas = aux;
//	}
}

void VigaInclinada::guardarSubPlataformas(vector<Actualizable*>* vector){
	for (unsigned int i = 0; i < plataformas->size(); i++){
		vector->push_back(plataformas->at(i));
	}
}

VigaInclinada::~VigaInclinada() {
	delete(plataformas);
}

void VigaInclinada::chocarCon(Actualizable*){}

void VigaInclinada::actualizar(float){}

int VigaInclinada::obtenerEstado(){
	return 0;
}
