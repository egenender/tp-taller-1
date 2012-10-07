/*
 * Server.h
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <map>

#define PORT	5555
typedef struct prueba{


	int ID;
	int entero;


}prueba_t;

typedef std::map <int,prueba_t> mapa_cambios;
typedef std::map <int,int> mapa_sockid;

class Server{



	private:
		int crear_socket (unsigned short int);
		int puerto;
		bool activado;
		fd_set activos,leidos;
		int sock;
		mapa_cambios* cambios_entrantes;
		mapa_sockid* id_sock;

	public:
		Server();
		Server(int);
		void atender_sockets(void);
		bool leer_de_cliente (int, void*,size_t);
		bool escribir_a_cliente(int,void*,size_t);
		void iniciar ();
		void activar();
		void desactivar();


};
