#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "../controller/Observador.h"
#include <stdbool.h>
#include <vector>
using namespace std;

class Observable {
	private:
		vector<Observador*>* observadores;
		bool cambios;
	public:
		Observable();
		virtual ~Observable();
		void agregarObservador(Observador* observador);
		void eliminarObservador(Observador* observador);
		void notificarObservadores();
		virtual int obtenerEstado()=0;
		bool cambio();
		int cantidadObservadores();
	protected:
		void huboCambios();
		void limpiarCambio();

};

#endif
