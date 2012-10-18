/*
 * ManejadorCliente.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: genender
 */

#include "ManejadorCliente.h"

ManejadorCliente::ManejadorCliente(Cliente* clienteNuevo){

	cliente=clienteNuevo;


}

void ManejadorCliente::recibirRecursos(){


	int largo;
	//leo largo de ruta
	largo = cliente->escuchar_un_entero();

	while (largo>0) {
		//leo ruta

		char* nombre= recibirRuta(largo);

		EscrituraArchivo* e = new EscrituraArchivo(nombre);
		free(nombre);

		//leo largo de todo
		largo = cliente->escuchar_un_entero();


		//de a uno leo todo y lo escribo

		recibirArchivo(e,largo);

		e->CerrarArchivo();

		//leo largo de ruta
		largo = cliente->escuchar_un_entero();
	}
}
char* ManejadorCliente::recibirRuta(int largo){


	int* intNombre = cliente->escuchar_N_enteros(largo);
	char *nombre = (char*) malloc((largo)*sizeof(char));
	int i=0;
	while(i < largo){
		nombre[i] = intNombre[i];
		i++;
	}
	free(intNombre);
	nombre[i] = '\0';

	return nombre;


}

void ManejadorCliente::recibirArchivo(EscrituraArchivo* escritor,int largo){

	int j = 0;
	void* algo;

	while(j<largo){
		algo = cliente->escuchar_al_server(sizeof(int));
		// NO VA 0, VA NULL pero no me acuerdo de donde se hace include
		if (algo != 0){
			escritor->EscribirUno(  *(int*) algo , largo);
			j++;
		}
	}

}



