/*
 * Server.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */


#include "Server.h"

using namespace std;


Server::Server(){

	puerto=PORT;
	activos=fd_set();
	leidos=fd_set();
	activado=false;
	cambios_entrantes= new mapa_cambios();
	id_sock= new mapa_sockid();

}

Server::Server(int port){

	puerto=port;
	activos=fd_set();
	leidos=fd_set();
	activado=false;
	cambios_entrantes= new mapa_cambios();
	id_sock= new mapa_sockid();
}

int Server::crear_socket (unsigned short int port) {
	int sock;
	struct sockaddr_in name;

	/* Create the socket.  */
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0){

		perror ("socket");
		exit (EXIT_FAILURE);

	}

	/* Give the socket a name.  */
	name.sin_family = AF_INET;
	name.sin_port = htons (port);
	name.sin_addr.s_addr = htonl (INADDR_ANY); // INADDR_ANY ES LA DIRECCION IP DE LA PROPIA MAQUINA
	if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0){

		perror ("bind");
		exit (EXIT_FAILURE);

	}

	return sock;
}

bool Server::leer_de_cliente (int filedes, void* buffer,size_t tamanio){


	int nbytes;

	nbytes = read (filedes, buffer, tamanio);
	if (nbytes < 0){

		/* Read error.  */
		perror ("read");
		exit (EXIT_FAILURE);

	} else if (nbytes == 0){
		/* End-of-file.  */
		return -1;
	}else {
		/* Data read.  */

		if (nbytes!=sizeof(prueba_t)) printf("Armamos Bardo\n");
		return 0;

    }
}

void Server::activar(){

	activado=true;

}

void Server::desactivar(){

	activado=false;

}


bool Server::escribir_a_cliente(int filedes,void* buffer,size_t tamanio){



	int nbytes;

	nbytes = write (filedes, buffer, tamanio);
	if (nbytes < 0){

		/* write error.  */
		perror ("write");
		exit (EXIT_FAILURE);

	} else if (nbytes == 0){
		/* End-of-file.  */
		return -1;
	}else {

		if (nbytes!=sizeof(prueba_t)) printf("Armamos Bardo\n");
		return 0;

    }

}

void Server::atender_sockets(){


	struct sockaddr_in nombre_cliente;
	size_t size;
	int cliente;
	while (activado){

		/* Bloquear hasta que llegue algo en uno o mas de los sockets activos */
		leidos = activos;
		if (select (FD_SETSIZE, &leidos, NULL, NULL, NULL) < 0){

			perror ("select");
			exit (EXIT_FAILURE);

		}

		/* Service all the sockets with input pending.  */
		for (int i = 0; i < FD_SETSIZE; ++i)
			if (FD_ISSET (i, &leidos)){

				if (i == sock) {
					/* Connection request on original socket.  */
					size = sizeof (nombre_cliente);
					if ((cliente=accept (sock,(struct sockaddr *) &nombre_cliente, (unsigned int *)&size)) < 0){
						perror ("accept");
						exit (EXIT_FAILURE);
					}
					//fprintf (stderr, "Server: connect from host %s, port %d\n",inet_ntoa (nombre_cliente.sin_addr),ntohs (nombre_cliente.sin_port));
					//eso va para log
					FD_SET(cliente, &activos);
				} else {
					/* Datos llegando de un socket ya conectado.  */
					prueba_t struct_entrante;
					if (leer_de_cliente (i,&struct_entrante,sizeof(struct_entrante)) < 0){
						close (i);
						FD_CLR (i, &activos);
					}

					// guardar el struct entrante en el mapa con el ID en su clave

					cambios_entrantes->insert(pair <int,prueba_t> (struct_entrante.ID,struct_entrante));

					// asociar el ID con el numerito de socket, puse otro mapa (mmm)

					id_sock->insert(pair <int,int> (struct_entrante.ID,i));

					// if hay que escribir al cliente: hacerlo aca?


				}
			}
    }


}

void Server::iniciar (){



	fd_set conjunto_activos, conjunto_read;
	activos=conjunto_activos;
	leidos=conjunto_read;

	/* Crear el socket e inicializarlo para aceptar conexiones  */

	sock = crear_socket (puerto);

	if (listen (sock, 10) < 0){
		perror ("listen");
		exit (EXIT_FAILURE);
    }

	/* Inicializar el conjunto de sockets activos.  */
	FD_ZERO (&conjunto_activos);
	FD_SET (sock, &conjunto_activos);

	activar();


}


