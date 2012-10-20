/*
 * ManejadorCliente.h
 *
 *  Created on: Oct 17, 2012
 *      Author: genender
 */

#include "Cliente.h"
#include "EscrituraArchivo.h"
#include "../view/TipoProtagonista.h"
using namespace std;

class ManejadorCliente{

	private:

		Cliente* cliente;
		int elNivel;
		std::vector<TipoProtagonista*>* tiposProt;
		int IDprot;

	public:

		void recibirRecursos();
		char* recibirRuta(int);
		void recibirArchivo(EscrituraArchivo*,int);
		ManejadorCliente(Cliente*);
		void iniciarCarga();
		void recibirDisponibles();
		void seleccionarProt(int);

};


