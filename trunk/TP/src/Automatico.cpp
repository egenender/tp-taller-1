#include "Automatico.h"

Automatico::Automatico(const char* nombrecito, Area* sup): Cuerpo(nombrecito,sup) {
	estado = QUIETO;
}

Automatico::~Automatico() {
	//ya se destruyen las cosas en el cuerpo

	//si despues se hace algo que le agregue inteligencia artificial, se lo avisa
}

void Automatico::actualizar(){
	Automatico::notificarObservadores();

	//por el momento no hace nada, pero si hiciera:

	/*HacerCosas();
	 * lista_iter_t* iter = lista_iter_crear(lista_observadores);
	 * Observador* observer;
	 * while (!lista_iter_al_final(iter)){
	 * 		observer = (Observador*) lista_iter_ver_actual(iter);
	 * 		observer->avisarCambio();
	 * 		lista_iter_avanzar();
	 * }
	 * lista_iter_destruir(iter);
	 * */
}

int Automatico::obtenerEstado(){
	return estado;
}
