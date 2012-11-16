#include "Tuberia.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Tuberia::Tuberia(const char* nom, Area* sup, float m, int dir, std::vector<int>* pb ,std::vector<FabricaActualizable*>* f ): Plataforma(nom, sup) {
	media = m;
	if (media <= 1)
		media = MEDIA_TUBERIA_STD;

	sentido = dir;
	estado = sentido;

	fabricas = f;

	int acum = 0;
	for (unsigned int i = 0; i < pb->size(); i++)
		acum += pb->at(i);

	if (acum!=100){
		probabilidades = new std::vector<int>();
		int equiprobable = 100 / pb->size();
		for (unsigned int i = 0; i < pb->size(); i++)
			probabilidades->push_back(equiprobable);
	}else{
		probabilidades = pb;
	}

	timer = new Timer();

	crearPosicion();
	tiempo_espera = calcularTiempo();
	timer->comenzar();
}

Tuberia::~Tuberia() {
	delete (probabilidades);
	delete (fabricas);
	delete(timer);
	delete(posCreacion);
}

void Tuberia::actualizar(float delta){

	if (timer->obtenerTiempo() >= (tiempo_espera * 1000)){
		unsigned int indice = calcularFabrica();
		fabricas->at(indice)->fabricar(posCreacion, sentido);
		timer->detener();
		tiempo_espera = calcularTiempo();
		timer->comenzar();
	}
}

float Tuberia::calcularTiempo(){
	float u = tirarRandom();

	float rta = (-media) * log (1-u);
	return rta;
}

float Tuberia::tirarRandom(){
	float u;
	do{
		u =(rand() % 1000) + 1;
		float w;
		do{
			w =(rand() % 1000);
		}while (w >= u);
		u = w / u;
	}while(u == 1);
	return u;
}

unsigned int Tuberia::calcularFabrica(){
	float rnd;
	do{
		rnd = tirarRandom();
	}while (rnd == 0 || rnd == 1);

	unsigned int i = 0;
	int acum = 0;

	while (acum < (rnd * 100)){
		acum += probabilidades->at(i);
		i++;
	}

	return (i-1);
}

void Tuberia::crearPosicion(){
	int x,y;
	x = obtenerArea()->obtenerPosicion()->obtenerX();
	y = obtenerArea()->obtenerPosicion()->obtenerY();

	if (sentido == ARRIBA_TB){
		x += (obtenerArea()->obtenerAncho()/2);
	}
	if (sentido == ABAJO_TB){
		y += obtenerArea()->obtenerAlto();
		x += (obtenerArea()->obtenerAncho()/2);
	}
	if (sentido == DERECHA_TB){

		y += obtenerArea()->obtenerAlto();
		x += obtenerArea()->obtenerAncho() + 1;
	}
	if (sentido == IZQUIERDA_TB){
		y += obtenerArea()->obtenerAlto();
	}

	posCreacion = new Posicion(x,y);
}
