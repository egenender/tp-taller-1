#include "PlataformaMovil.h"
#include "Hongo.h"
#include "Manual.h"
#include "Barril.h"
#include "../Tipos.h"

PlataformaMovil::PlataformaMovil(const char* nom, Area* sup, int vel, int dist):Plataforma(nom,sup) {
	velocidad = vel;
	if (velocidad <= 0)
		velocidad = VELOCIDAD_PLTMOVIL_STD;
	cuerposContacto = new std::vector<Cuerpo*>();

	desplazamiento = dist;
	if (desplazamiento <= 0)
		desplazamiento = DIST_PLTMOVIL_STD;

	actual = 0;
	esElevador = false;
}

PlataformaMovil::~PlataformaMovil() {
	delete(cuerposContacto);
}

void PlataformaMovil::chocarConManual(Manual* m){
	cuerposContacto->push_back(m);
}
void PlataformaMovil::chocarConBarril(Barril* b){
	if(! b->estaMuerto())
		cuerposContacto->push_back(b);
}
void PlataformaMovil::chocarConHongo(Hongo* h){
	if(! h->estaMuerto())
		cuerposContacto->push_back(h);
}
void PlataformaMovil::actualizar(float){
	if (!esElevador)
		trasladar(velocidad, 0, true);
	else
		trasladar(0,velocidad, true);

	for (unsigned int i = 0; i < cuerposContacto->size(); i++){
		try{
			if (!esElevador)
				cuerposContacto->at(i)->trasladar(velocidad,0,true);
			else
				cuerposContacto->at(i)->trasladar(0,velocidad,true);
		}catch(exception &e){

		}
	}


	int aux;
	if (velocidad < 0)
		aux = -velocidad;
	else
		aux = velocidad;
	actual += aux;

	if (actual >= desplazamiento){
		actual = 0;
		velocidad *= (-1);
	}
	cuerposContacto->clear();

	huboCambios();
	notificarObservadores();
}

void PlataformaMovil::chocarConPlataforma(Plataforma* p){
	Posicion* pos = p->obtenerArea()->obtenerPosicion();
	Posicion* posCmp = new Posicion(pos->obtenerX() + p->obtenerAncho(), pos->obtenerY());

	bool choque = false;
	if (posCmp->estaALaIzquierdaDe(posAnterior))
		choque = true;

	delete(posCmp);
	posCmp = new Posicion (posAnterior->obtenerX() + obtenerArea()->obtenerAncho(), posAnterior->obtenerY());

	if(posCmp->estaALaIzquierdaDe(pos))
		choque = true;

	delete(posCmp);

	if(choque){
	actual = 0;
	velocidad *= (-1);
	}
}

unsigned int PlataformaMovil::obtenerTipo(){
	if ( esElevador )
		return TIPO_ELEVADOR;
	return TIPO_PLATAFORMA_MOVIL;
}

void PlataformaMovil::setearElevador(){
	esElevador = true;
}
