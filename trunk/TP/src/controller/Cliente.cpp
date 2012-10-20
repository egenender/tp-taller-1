/*
 * Cliente.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */


#include "Cliente.h"
#include <pthread.h>



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
	conectar();


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
	conectar();

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
		//fprintf (stderr, "Unknown host %s.\n", nombre_host); osea mensaje de log
		return false;

	}
	direccion_host->sin_addr = *(struct in_addr *) info_host->h_addr;
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

	close (sock);

}

bool Cliente::crear_socket(){

	/* Crear el socket.   */
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0){

		//perror ("socket (client)"); osea mensaje de log
		return false;

	}

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
		//perror ("connect (client)"); osea mensaje de log
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

	while (true){
		void* dato = malloc (tamanio);
		int bytes;

		if ((bytes=read(sock,dato, tamanio))<tamanio){
			free(dato);
			continue;
		}

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

	pthread_cancel(thread_escritura);


}
