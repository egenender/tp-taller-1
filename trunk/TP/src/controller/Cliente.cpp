/*
 * Cliente.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */


#include "Cliente.h"


Cliente::Cliente(){

	conectado=false;
	sock=0;
	serverhost=SERVERHOST;
	puerto=PORT;

}

Cliente::Cliente(const char * dir_host,unsigned short int port){

	conectado=false;
	sock=0;
	serverhost=dir_host;
	puerto=port;

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

	nbytes = write (sock,datos, tamanio);
	if (nbytes < 0){

		//perror ("write"); osea mensaje de log
		return false;

	}

	return true;

}

void Cliente::marcar_conectado(){

	conectado=true;


}


void Cliente::detener(){

	close (sock);

}

//bool Cliente::iniciar (){
//
//	int fdes;
//	struct sockaddr_in direccion_server;
//
//	/* Crear el socket.   */
//	fdes = socket (PF_INET, SOCK_STREAM, 0);
//	if (fdes < 0){
//
//		//perror ("socket (client)"); osea mensaje de log
//		return false;
//
//	}
//
//	/* Connectarse al server.   */
//	inicializar_address (&direccion_server, serverhost, puerto);
//	if (connect (fdes,(struct sockaddr *) &direccion_server, sizeof (direccion_server))<0) {
//
//		//perror ("connect (client)"); osea mensaje de log
//		return false;
//
//	}
//	Log::getInstance()->writeToLogFile("INFO","Se conecto el cliente al server");
//	sock=fdes;
//	marcar_conectado();
//	return true;
//}
