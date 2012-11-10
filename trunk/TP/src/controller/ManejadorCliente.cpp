/*
 * ManejadorCliente.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: genender
 */

#include "ManejadorCliente.h"
#include "GestorConfiguraciones.h"
#include "../model/structures/structCliente.h"
#include "ManejadorEstados.h"
#include "Nivel.h"


ManejadorCliente* ManejadorCliente::instancia=NULL;

ManejadorCliente* ManejadorCliente::reiniciarInstancia(Cliente *client) {
   instancia = new ManejadorCliente(client);

   return instancia;
}


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

void ManejadorCliente::destruirCliente(){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	cliente->detener_escuchar();
	cliente->detener_escribir();
	cliente->detener();
	GestorConfiguraciones::getInstance()->acabarGestor();
	//ManejadorEstados::setearEstadoActual(ESTADO_GUI);
	Nivel::obtenerInstancia()->morir();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

bool ManejadorCliente::recibirRecursos(){
	struct timeval intervaloTiempo;

	intervaloTiempo.tv_sec=10;
	intervaloTiempo.tv_usec=0;

	fd_set set= fd_set();

	FD_SET(cliente->sock,&set);


	if(select(FD_SETSIZE,&set,NULL,NULL,&intervaloTiempo)==0){
		Log::getInstance()->writeToLogFile("ERROR","El juego en el servidor esta completo");
		return false;
	}

	char* ruta = (char*) malloc (90*sizeof(char));
	sprintf(ruta,"%s %s","mkdir","Temp");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/config");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/sounds");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/estados");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/items");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/niveles");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Charmander");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Charmeleon");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Croconaw");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Gengar");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/GokuMono");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Pikachu");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Primeape");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Raichu");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Squirtle");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Totodile");
	system(ruta);
	sprintf(ruta,"%s %s","mkdir","Temp/src/resources/cuerpos/Yoshi");
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
	return true;
}

void ManejadorCliente::seleccionarProt(string nombre){
	int ID = darID(nombre);
	cliente->escribir_al_server(&ID,sizeof(int));
	Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Se envia protagonista a usar.");

	int dato = cliente->escuchar_un_entero_out(1000);

	if (dato == 1)
		IDprot = ID;
	if (dato == -1)
			IDprot = -1;
	if (dato == -2)
			IDprot = -2;

	Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Esta dada la respuesta.");
}


bool ManejadorCliente::personajeAceptado(){
	return (IDprot != -1);
}

bool ManejadorCliente::serverCaido(){
	return (IDprot == -2);
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
	gestor->setEsCliente();
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
	free(algo);

}


void ManejadorCliente::detener(){
	structCliente* mori = structCliente_crear(IDprot,MUERTO);
	cliente->encolar_cambio(mori);
}
