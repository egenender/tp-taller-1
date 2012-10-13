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

using namespace std;

#define PORT		5555
#define SERVERHOST 	"127.0.0.1"

typedef queue <void*> Cola ;

class Cliente {

	// CUESTION: thread para mandar tambien?

	private:

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

	public:

		// Metodos viejos
		//bool iniciar ();


		// Crea un Cliente asi noma (todo local)
		Cliente();

		// Crea un Cliente con la direccion del host y el puerto al cual acceder (esto es lo que especifica el usuario por la GUI)
		Cliente(const char *,unsigned short int);

		// Destructor: warap chabon
		~Cliente();

		// Burocracias para incializar un struct de atributos que se le pasan al connect
		bool inicializar_address (struct sockaddr_in *, const char *, unsigned short int);

		// Escribir al server que ya tendriamos inicializado todo liso
		bool escribir_al_server (void*,size_t);

		// Marca al cliente como conectado a un server
		void marcar_conectado();

		// Detiene el thread que esta escuchando al server
		void detener();

};

