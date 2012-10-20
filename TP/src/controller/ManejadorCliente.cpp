/*
 * ManejadorCliente.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: genender
 */

#include "ManejadorCliente.h"
#include "GestorConfiguraciones.h"


ManejadorCliente* ManejadorCliente::instancia=NULL;

ManejadorCliente* ManejadorCliente::obtenerInstancia(Cliente *client) {
   if( instancia == NULL){
	   instancia = new ManejadorCliente(client);
   }
   return instancia;
}

ManejadorCliente::ManejadorCliente(Cliente* clienteNuevo){

	cliente=clienteNuevo;
	elNivel = -1;
	tiposProt = NULL;
	IDprot = -1;

}

void ManejadorCliente::recibirRecursos(){
	char* ruta = (char*) malloc (90*sizeof(char));
	sprintf(ruta,"%s %s","mkdir","Temp");
	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src");
	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources");
	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/config");
	//llama al sistema, con el comando ingresado, espacio, la ruta del M3U
	system(ruta);
	free(ruta);


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

	elNivel = cliente->escuchar_un_entero();

	recibirDisponibles();

}

void ManejadorCliente::seleccionarProt(string nombre){
	int ID = darID(nombre);
	cliente->escribir_al_server(&ID,sizeof(int));

	int dato = cliente->escuchar_un_entero();

	if (dato == 1)
		IDprot = ID;
	else
		IDprot = -1;

	printf("id def: %i\n",IDprot);

}


bool ManejadorCliente::personajeAceptado(){
	return (IDprot != -1);
}


int ManejadorCliente::darID(string nombre){
	bool encontrado = false;
	unsigned int i = 0;
	while ( !encontrado && i< tiposProt->size() ){
		encontrado = ( strcmp ( tiposProt->at(i)->nombre , nombre.c_str() ) == 0 );
		i++;
	}
	i--;
	if (! encontrado)
		return -1;
	return i;
}

void ManejadorCliente::recibirDisponibles(){
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();
	gestor->setPosiblesTiposProtagonistas();
	tiposProt = gestor->ObtenerPosiblesTiposProtagonistas();
	int dato = cliente->escuchar_un_entero();
	unsigned int i = 0;
	while(dato != -1){
		if (dato == 0)
			tiposProt->at(i)->disponible = false;
		i++;
		dato = cliente->escuchar_un_entero();
	}

}

void ManejadorCliente::iniciarCarga(){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	gestor->inicioCarga();
	gestor->setNivelElegido(elNivel);
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




