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
		static ManejadorCliente* instancia;

		Cliente* cliente;
		int elNivel;
		std::vector<TipoProtagonista*>* tiposProt;
		int IDprot;

	public:
		static ManejadorCliente* obtenerInstancia(Cliente*);

		void recibirRecursos();
		char* recibirRuta(int);
		void recibirArchivo(EscrituraArchivo*,int);
		ManejadorCliente(Cliente*);
		void iniciarCarga();
		void recibirDisponibles();
		void seleccionarProt(string);
		int darID(string);

		bool personajeAceptado();

};


