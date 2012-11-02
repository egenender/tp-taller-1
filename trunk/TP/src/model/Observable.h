#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "../common/Observador.h"
#include <stdbool.h>
#include <vector>
#include "Posicion.h"
using namespace std;

//Defino constantes para conocer mi estado
#define QUIETO 0
#define CAMINANDOIZQ 1
#define CAMINANDODER 2
#define QUIETODER 3
#define QUIETOIZQ 4
#define SALTANDODER 5
#define SALTANDOIZQ 6
#define SALTAR 7
#define MUERTO 8
#define VIVO 9
#define SUBIENDOQUIETO 10
#define SUBIENDOMOVIMIENTO 11
#define LANZANDO 12

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
		virtual int obtenerAncho()=0;
		virtual int obtenerAlto() = 0;
		bool cambio();
		int cantidadObservadores();
		virtual Posicion* obtenerPosicion()=0;
	protected:
		void huboCambios();
		void limpiarCambio();

};

#endif
