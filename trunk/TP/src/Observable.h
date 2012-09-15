#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "Observador.h"
#include <stdbool.h>
#include <vector>
using namespace std;

class Observable {
	private:
		vector<Observador*> observadores;
		bool cambios;
	public:
		Observable();
		~Observable();
		void agregarObservador(Observador* observador);
		void eliminarObservador(Observador* observador);
		void notificarObservadores();
		void huboCambios();
};

#endif
