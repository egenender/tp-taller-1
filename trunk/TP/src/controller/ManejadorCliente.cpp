/*
 * ManejadorCliente.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: genender
 */

#include "ManejadorCliente.h"
#include "GestorConfiguraciones.h"

ManejadorCliente::ManejadorCliente(Cliente* clienteNuevo){

	cliente=clienteNuevo;

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

void ManejadorCliente::seleccionarProt(int ID){
	int* entero;
	*entero = ID;
	cliente->escribir_al_server(entero,sizeof(int));
	int dato = cliente->escuchar_un_entero();

	if (dato == 1)
		IDprot = ID;
	else
		IDprot = -1;

}

void ManejadorCliente::recibirDisponibles(){
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();
	gestor->setPosiblesTiposProtagonistas();
	tiposProt = gestor->ObtenerPosiblesTiposProtagonistas();
	int dato = cliente->escuchar_un_entero();
	int i = 0;
	while(dato != -1){
		if (dato == 0)
				tiposProt->at(i)->disponible;
		i++;
		dato = cliente->escuchar_un_entero();
	}

	for (i=0;i<tiposProt->size();i++){
		cout << tiposProt->at(i)->nombre << endl;
		cout << tiposProt->at(i)->disponible << endl;
	}

	seleccionarProt(0);
}

void ManejadorCliente::iniciarCarga(){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	gestor->inicioCarga();
	gestor->setNivelElegido(elNivel);
	gestor->CargaRestante();
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




