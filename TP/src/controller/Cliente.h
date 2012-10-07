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



#define PORT		5555
#define SERVERHOST 	"127.0.0.1"

class Cliente {

	private:
		bool conectado;
		int sock;
		const char* serverhost;
		unsigned short int puerto;


	public:

		Cliente();
		Cliente(const char *,unsigned short int);
		~Cliente();
		bool inicializar_address (struct sockaddr_in *, const char *, unsigned short int);
		bool escribir_al_server (void*,size_t);
		bool iniciar ();
		void marcar_conectado();
		void detener();

};

