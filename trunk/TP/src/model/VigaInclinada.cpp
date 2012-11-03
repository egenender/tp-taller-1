#include "VigaInclinada.h"
#include <math.h>

//FIXME: quitar esto:
#include "../controller/GestorConfiguraciones.h"
#include "../view/Superficie.h"
#include "../view/VistaImagen.h"
#include "../view/VistaCuerpo.h"

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
		return;
	}
	float PI = 3.14159;
	float angulito = (angulo * PI)/180;

	int altoP = superficieOcupada->obtenerAlto();
	int cant = CANT_PLATAFORMAS;
	int anchoP;

	int anchoEst = superficieOcupada->obtenerAncho() * cos(angulito);
	if (cant > anchoEst)
		cant = anchoEst;

	int separacionX = 0;

	anchoP = superficieOcupada->obtenerAncho() * cos(angulito) / cant;
	if ((anchoP*cant) < (superficieOcupada->obtenerAncho() * cos(angulito)/2))
		separacionX = 1;


	int difAltura = superficieOcupada->obtenerAncho() * sin(angulito) / cant;

	int separacionY = 0;
	if ((difAltura*cant) < (superficieOcupada->obtenerAncho() * sin(angulito)/2))
		separacionY = 0;

	Posicion* pos;
	Area* sup;
	printf("cantidad %d\n",cant);
	int x = superficieOcupada->obtenerPosicion()->obtenerX();
	int y = superficieOcupada->obtenerPosicion()->obtenerY();
	if (creceHacia == CRECE_IZQUIERDA)
		for (int i = 0; i < cant; i++){

			pos = new Posicion(x + anchoP*i + separacionX, y + (creceHacia)* (difAltura*i +separacionY));
			sup = new Area(anchoP, altoP, pos);
			Plataforma* plataforma = new Plataforma(" ", sup);
			plataformas->push_back(plataforma);
			if (i!= cant-1)
				plataforma->setearComoVigaPorDerecha();

		}
	else
		for (int i = cant-1; i >=0; i--){
			pos = new Posicion(x + anchoP*i + separacionX, y + (creceHacia)* (difAltura*i +separacionY));
			sup = new Area(anchoP, altoP, pos);
			Plataforma* plataforma = new Plataforma(" ", sup);
			plataformas->push_back(plataforma);
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

	//FIXME: BORRAR ESTO, hardcode para ver que ande!
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();

	std::vector<VistaCuerpo*>* vistas = gestor->ObtenerVistas();
	Superficie* superf;
	VistaImagen* img;
	for (unsigned int j = 0; j < plataformas->size(); j++){
		superf = new Superficie("src/resources/viga2.jpg");
		superf->escala(plataformas->at(j)->obtenerAncho(), plataformas->at(j)->obtenerAlto());
		img = new VistaImagen(superf);
		plataformas->at(j)->agregarObservador(img);
		vistas->push_back(img);
	}

	//BORRAR HASTA ACA
}

VigaInclinada::~VigaInclinada() {
	delete(plataformas);
}


void VigaInclinada::chocarCon(Actualizable*){}
void VigaInclinada::chocarConEscalera(Escalera*){}
void VigaInclinada::chocarConPlataforma(Plataforma*){}
void VigaInclinada::chocarConManual(Manual*){}

void VigaInclinada::actualizar(float){}

int VigaInclinada::obtenerEstado(){
	return 0;
}
