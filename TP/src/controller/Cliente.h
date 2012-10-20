/*
 * Cliente.h
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../log/Log.h"
#include <queue>
#include <pthread.h>
using namespace std;

#ifndef CLIENTE_H
#define CLIENTE_H

#define PORT		5556
#define SERVERHOST 	"127.0.0.1"
#define MAX_INTENTOS 8

typedef queue <void*> Cola ;


typedef struct parametrosCliente{

	Cola* entrantes;
	Cola* salientes;
	size_t tamanio;
	int sock;

} parametrosCliente_t;

class Cliente {

	// CUESTION: thread para mandar tambien? respuesta: si
	// CUESTION: tema del head, que es lo que manda al principio para especificar el tamanio.
	// eso habria que manejarlo desde el modelo?

	private:

		// Atributos viejos
		//Thread thread_envio;

		static Cliente* instancia;

		// Esta conectado o no
		bool conectado;

		// El file descriptor del sock suyo
		int sock;

		// Direccion del servidor
		const char* serverhost;

		// Puerto del servidor
		unsigned short int puerto;

		// Cola de cambios entrantes
		Cola cola_entrantes;

		// Cola de cambios salientes
		Cola cola_salientes;

		pthread_t thread_escuchar;
		pthread_t thread_escritura;


	public:
		// Metodos viejos
		//bool iniciar ();
		static Cliente* obtenerInstancia(const char *,unsigned short int);

		// Crea un Cliente asi noma (todo local)
		Cliente();

		// Crea un Cliente con la direccion del host y el puerto al cual acceder (esto es lo que especifica el usuario por la GUI)
		Cliente(const char *,unsigned short int);

		// Destructor: warap chabon
		~Cliente();

		// Crea un socket a partir de los datos ya inicializados
		bool crear_socket();


		// Se conecta al server
		bool conectar();
		// Esto deberia crear un thread que empiece a escuchar a su socket por si viene algo,
		// aceptar lo que le viene y encolar sus cambios entrantes
		void escuchar(size_t);

		void escritura(size_t);

		parametrosCliente_t* inicializar_parametros(size_t tamanio);
		// Burocracias para incializar un struct de atributos que se le pasan al connect
		bool inicializar_address (struct sockaddr_in *, const char *, unsigned short int);

		// Escribir al server que ya tendriamos inicializado todo liso
		// si no conecta al server, deberia intentar conectar hasta hacer un timeout
		bool escribir_al_server (void*,size_t);

		void* escuchar_al_server (size_t);

		int escuchar_un_entero ();
		int* escuchar_N_enteros (int );
		char* escuchar_N_char (int );

		void* desencolar_cambio();

		void encolar_cambio(void*);

		bool hay_cambios();

		// Marca al cliente como conectado a un server (no se para que todavia pero suena bien)
		void marcar_conectado();

		// Detiene el thread que esta escuchando al server
		void detener_escuchar();

		void detener_escribir();

		void detener();

};

#endif
