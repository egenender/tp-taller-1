#include "PlataformaMovil.h"
#include "Hongo.h"
#include "Manual.h"
#include "Barril.h"

PlataformaMovil::PlataformaMovil(const char* nom, Area* sup, int vel, int dist):Plataforma(nom,sup) {
	velocidad = vel;
	if (velocidad <= 0)
		velocidad = VELOCIDAD_PLTMOVIL_STD;
	cuerposContacto = new std::vector<Cuerpo*>();

	desplazamiento = dist;
	if (desplazamiento <= 0)
		desplazamiento = DIST_PLTMOVIL_STD;

}

PlataformaMovil::~PlataformaMovil() {
	delete(cuerposContacto);
}

void PlataformaMovil::chocarConManual(Manual* m){
	cuerposContacto->push_back(m);
}
void PlataformaMovil::chocarConBarril(Barril* b){
	cuerposContacto->push_back(b);
}
void PlataformaMovil::chocarConHongo(Hongo* h){
	cuerposContacto->push_back(h);
}
void PlataformaMovil::actualizar(float){
	trasladar(velocidad, 0, true);

	for (unsigned int i = 0; i < cuerposContacto->size(); i++){
		cuerposContacto->at(i)->trasladar(velocidad,0,true);
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
}
