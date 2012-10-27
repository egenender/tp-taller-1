/*
 * Cliente.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */


#include "Cliente.h"
#include <pthread.h>
#include "GestorConfiguraciones.h"
#include "ManejadorEstados.h"
#include "Nivel.h"
#include "ManejadorCliente.h"
#include "../log/Log.h"
#include "../model/structures/structCliente.h"

#include <linux/ethtool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/sockios.h>
#include <linux/if.h>
#include <linux/ethtool.h>
#include <string.h>
#include <stdlib.h>



Cliente* Cliente::instancia=NULL;

Cliente::Cliente(){

	conectado=false;
	sock=0;
	serverhost=SERVERHOST;
	puerto=PORT;
	thread_escuchar=0;
	cola_entrantes = Cola();
	cola_salientes = Cola();

	crear_socket();
	ok = conectar();


}

Cliente::Cliente(const char * dir_host,unsigned short int port){

	conectado=false;
	sock=0;
	serverhost=dir_host;
	puerto=port;
	thread_escuchar=0;
	cola_entrantes = Cola();
	cola_salientes = Cola();

	crear_socket();
	ok = conectar();

}

Cliente* Cliente::reiniciarInstancia(const char * dir_host,unsigned short int port) {
    instancia = new Cliente(dir_host,port);

   return instancia;
}

Cliente* Cliente::obtenerInstancia(const char * dir_host,unsigned short int port) {
   if( instancia == NULL){
	   instancia = new Cliente(dir_host,port);
   }
   return instancia;
}

Cliente::~Cliente(){}

bool Cliente::inicializar_address (struct sockaddr_in *direccion_host, const char *nombre_host, unsigned short int puerto) {

	struct hostent *info_host;

	direccion_host->sin_family = AF_INET;
	direccion_host->sin_port = htons (puerto);
	info_host = gethostbyname (nombre_host);
	if (info_host == NULL)
	{
		Log::getInstance()->writeToLogFile("ERROR","SOCK: No se pudo establecer cliente");
		return false;

	}
	direccion_host->sin_addr = *(struct in_addr *) info_host->h_addr;
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se inicializo direccion de cliente");
	return true;

}

bool Cliente::escribir_al_server (void* datos,size_t tamanio) {

	if (!conectado) return false;

	int nbytes;
	
	nbytes = write (sock ,datos, tamanio);
	if (nbytes < 0){
		//perror ("write"); osea mensaje de log
		return false;
	}
	return true;
}

int Cliente::escuchar_un_entero_out (int t) {
	int* dato = (int*) malloc (sizeof(int));
	int bytes;
	bool escuchado = false;
	int i = 0;
	while (!escuchado && i<t){
		if (( ( bytes=read(sock,dato, sizeof(int))) ) ==sizeof(int) ){
			escuchado = true;
		}
		i++;
		Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "El server se ha desconectado.");
	}
	if(!escuchado){
		return -2;
	}

	int valor = *dato;
	free(dato);

	return valor;
}

int Cliente::escuchar_un_entero () {
	int* dato = (int*) malloc (sizeof(int));
	int bytes;
	bool escuchado = false;
	while (!escuchado){
		if (( ( bytes=read(sock,dato, sizeof(int))) ) ==sizeof(int) ){
			escuchado = true;
		}
	}

	int valor = *dato;
	free(dato);

	return valor;
}

int* Cliente::escuchar_N_enteros (int n) {
	int* dato = (int*) malloc (n*sizeof(int));
	int j = 0;

	while (j < n){
		dato[j] = escuchar_un_entero();
		j++;
	}

	return dato;
}

char* Cliente::escuchar_N_char (int n) {
	char* dato = (char*) malloc (n*sizeof(char));
	int j = 0;

	while (j < n){
		dato[j] = (char) escuchar_un_entero();
		j++;
	}

	return dato;
}

void* Cliente::escuchar_al_server (size_t tamanio) {
	void* dato = malloc (tamanio);
	unsigned int bytes;
	if ((bytes=read(sock,dato, tamanio))<tamanio){
		free(dato);
		return NULL;
	}

	return dato;
}


void Cliente::marcar_conectado(){

	conectado=true;

}


void Cliente::detener(){
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se detuvo el socket de conexion del cliente");
	close (sock);
	instancia = NULL;

}

bool Cliente::crear_socket(){

	/* Crear el socket.   */
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		Log::getInstance()->writeToLogFile("ERROR","SOCK: No se pudo crear socket cliente");
		return false;
	}
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se creo socket cliente");

	return true;
}

bool Cliente::conectar(){

	struct sockaddr_in direccion_server;

	inicializar_address (&direccion_server, serverhost, puerto);


	bool conecta=false;
	int maxIntentos=MAX_INTENTOS;
	int intento=1;
	while (intento!=maxIntentos && !conecta){

		if (connect (sock,(struct sockaddr *) &direccion_server, sizeof (direccion_server))>=0) conecta=true;

		intento++;
	}

	if (!conecta) {
		Log::getInstance()->writeToLogFile("ERROR","No se consiguio conexion con el servidor");
		return false;
	}

	Log::getInstance()->writeToLogFile("INFO","Se conecto el cliente al server");

	marcar_conectado();

	return true;

}
void* privEscuchar(void* param){

	parametrosCliente_t* parametros= (parametrosCliente_t*) param;
	Cola* cola_entrantes= parametros->entrantes;
	int tamanio=parametros->tamanio;
	int sock=parametros->sock;
	Log::getInstance()->writeToLogFile("INFO","El cliente inicia escucha");

	struct timeval intervaloTiempo;

	while (true){

		void* dato = malloc (tamanio);
		int bytes;
		intervaloTiempo.tv_sec=10;
		intervaloTiempo.tv_usec=0;

		fd_set set= fd_set();

		FD_SET(sock,&set);


		if(select(FD_SETSIZE,&set,NULL,NULL,&intervaloTiempo)==0){
			Log::getInstance()->writeToLogFile("INFO","Time Out conexion con el servidor");
			//ManejadorCliente::obtenerInstancia(NULL)->destruirCliente();
			Nivel::obtenerInstancia()->morir();

			pthread_exit(NULL);
		}

		if ((bytes=read(sock,dato, tamanio))<tamanio){
			free(dato);
			Log::getInstance()->writeToLogFile("INFO","Se perdio conexion con el servidor");
			ManejadorCliente::obtenerInstancia(NULL)->destruirCliente();
			Nivel::obtenerInstancia()->morir();

			pthread_exit(NULL);
		}

//		if (dato == NULL){
//			Cliente::obtenerInstancia("",0)->detener_escuchar();
//			Cliente::obtenerInstancia("",0)->detener_escribir();
//			Cliente::obtenerInstancia("",0)->detener();
//			GestorConfiguraciones::getInstance()->acabarGestor();
//			ManejadorEstados::setearEstadoActual(ESTADO_GUI);
//			return NULL;
//		}

		if (bytes==tamanio){
			pthread_mutex_t mutex;
			pthread_mutex_init (&mutex , NULL);
			pthread_mutex_lock(&mutex);
			cola_entrantes->push(dato);
			pthread_mutex_unlock(&mutex);
			pthread_mutex_destroy(&mutex);
		}

	}
	return NULL;
}


void* privEscribir(void* param){

	parametrosCliente_t* parametros= (parametrosCliente_t*) param;
	Cola* cola_salientes= parametros->salientes;
	int tamanio=parametros->tamanio;
	int sock=parametros->sock;
	Log::getInstance()->writeToLogFile("INFO","El cliente inicia escritura");

	while (true){
		pthread_mutex_t mutex;
		pthread_mutex_init (&mutex , NULL);
		pthread_mutex_lock(&mutex);
		if (!cola_salientes->empty()){
			void* saliente = cola_salientes->front();
			cola_salientes->pop();
			int bytes;
			if ((bytes=write(sock,saliente, tamanio))<tamanio){

				//Manejo  lo que sea
				continue;
			}
		}
		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);

	}
	return NULL;
}

parametrosCliente_t* Cliente::inicializar_parametros(size_t tamanio){

	parametrosCliente_t *parametros = (parametrosCliente_t*) malloc (sizeof(parametrosCliente_t));

	parametros->entrantes=&cola_entrantes;
	parametros->salientes=&cola_salientes;
	parametros->tamanio=tamanio;
	parametros->sock=sock;

	return parametros;
}

void Cliente::escuchar(size_t tamanio){

	parametrosCliente_t *param= inicializar_parametros(tamanio);
	pthread_t thread;
	thread_escuchar=thread;

	if (pthread_create(&thread,NULL,&privEscuchar,(void*)param)!=0) return;

}

void Cliente::encolar_cambio(void* cambio){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	cola_salientes.push(cambio);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

void Cliente::escritura(size_t tamanio){

	parametrosCliente_t *param= inicializar_parametros(tamanio);
	pthread_t thread;
	thread_escritura=thread;

	if (pthread_create(&thread,NULL,&privEscribir,(void*)param)!=0) return;

}

void* Cliente::desencolar_cambio(){

	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	void* cambio=cola_entrantes.front();

	cola_entrantes.pop();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	return cambio;
}

bool Cliente::hay_cambios(){

	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	return !cola_entrantes.empty();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

void Cliente::detener_escuchar(){

	pthread_cancel(thread_escuchar);


}

void Cliente::detener_escribir(){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
//	while (!cola_salientes.empty()){
//		void* saliente = cola_salientes.front();
//		cola_salientes.pop();
//		int tamanio = structCliente_obtener_tamanio();
//		write(sock,saliente, tamanio);
//		printf("estado enviado: %d\n", structCliente_obtener_estado((structCliente_t*)saliente));
//	}
	pthread_cancel(thread_escritura);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy (&mutex);
}
