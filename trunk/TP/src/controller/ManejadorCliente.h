/*
 * ManejadorCliente.h
 *
 *  Created on: Oct 17, 2012
 *      Author: genender
 */

#include "Cliente.h"
#include "EscrituraArchivo.h"
using namespace std;

class ManejadorCliente{

	private:

		Cliente* cliente;
		int elNivel;

	public:

		void recibirRecursos();
		char* recibirRuta(int);
		void recibirArchivo(EscrituraArchivo*,int);
		ManejadorCliente(Cliente*);
		void iniciarCarga();



};


