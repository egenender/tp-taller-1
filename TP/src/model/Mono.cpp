
#include "Mono.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Mono::Mono(const char* nom, Area* sup, float m): Cuerpo(nom,sup) {
	/*MEDIA DEBE ESTAR EN SEGUNDOS!*/
	estado = QUIETO;
	media = m;
	srand ( time(NULL) );
	tiempoEspera = calcularTiempo();

	timer = new Timer();
	timer->comenzar();

}

Mono::~Mono() {
	// TODO Auto-generated destructor stub
}

int Mono::obtenerEstado(){
	return estado;
}

void Mono::chocarCon(Actualizable*){

}


void Mono::actualizar(float){
	if (timer->obtenerTiempo() >= (tiempoEspera * 1000)){
		tirarBarril();
		timer->detener();
		tiempoEspera = calcularTiempo();
		timer->comenzar();
		estado = LANZANDO;
		return;
	}

	if (timer->obtenerTiempo() >= TIEMPO_LANZAMIENTO)
		estado = QUIETO;

}

float Mono::calcularTiempo(){
	/*Si supongo que el lanzamiento de un Barril corresponde a una Variable Aleatoria de tipo Exponencial, la inversa generalizada
	 *para obtener el tiempo a partir de un valor aleatorio u entre 0 y 1 es: T = - ln(1-u) * media, con media el valor esperado de ese tiempo*/

	//Esto de aca lo hago porque el Random de C++ es una garcha atroz.
	float u;
	do{
		u =(rand() % 1000) + 1;
		float w;
		do{
			w =(rand() % 1000);
		}while (w >= u);
		u = w / u;
	}while(u == 1);


	float rta = (-media) * log (1-u);
	printf("%f ",rta);
	return rta;
}

void Mono::tirarBarril(){
	printf("Tire Barril\n");
}
