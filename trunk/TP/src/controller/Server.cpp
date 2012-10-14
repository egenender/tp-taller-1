/*
 * Server.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */


#include "Server.h"


Server::Server(){

	puerto=PORT;
	activos=fd_set();
	leidos=fd_set();
	activado=false;
	cola_entrantes=Cola();
	cola_salientes=Cola();
	//cambios_entrantes= new mapa_cambios();
	//cambios_nuevos=false;

	/* Create the socket and set it up to accept connections.  */
	sock = crear_socket (puerto);

	if (listen (sock, 1) < 0){
		perror ("listen");
		exit (EXIT_FAILURE);
	}

	/* Initialize the set of active sockets.  */
	FD_ZERO (&activos);
	FD_SET (sock, &activos);


	printf("rd en inic: %p \n",&leidos);
	printf("act en inic: %p \n",&activos);
}

Server::Server(int port){

	puerto=port;
	activos=fd_set();
	leidos=fd_set();
	activado=false;
	cola_entrantes=Cola();
	cola_salientes=Cola();
	//cambios_entrantes= new mapa_cambios();
	//cambios_nuevos=false;

	/* Create the socket and set it up to accept connections.  */
	sock = crear_socket (puerto);

	if (listen (sock, 10) < 0){
		perror ("listen");
		exit (EXIT_FAILURE);
    }

	/* Initialize the set of active sockets.  */
	FD_ZERO (&activos);
	FD_SET ( sock , &activos);
}

bool Server::hay_cambios(){

	return !cola_entrantes.empty();

}

void Server::encolar_cambio(void* cambio){

	cola_salientes.push(cambio);

}

void* Server::desencolar_cambio(){

	void* cambio= cola_entrantes.front();
	cola_entrantes.pop();

	return cambio;

}

parametrosServer_t* Server::inicializar_parametros(size_t tamanio){

	parametrosServer_t *parametros = (parametrosServer_t*) malloc (sizeof(parametrosServer_t));

	parametros->entrantes=&cola_entrantes;
	parametros->salientes=&cola_salientes;
	parametros->tamanio=tamanio;
	parametros->act=&activos;
	parametros->rd=&leidos;
	parametros->sock=sock;
	parametros->puerto=puerto;

	return parametros;
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
		//perror ("bind");
		//exit (EXIT_FAILURE);
	}

	return sock;
}

void escribir_a_cliente(int i, void* punt,size_t tam){

	int nbytes;

	nbytes = write (i, punt, tam);
	if (nbytes < 0){

		/* Read error.  */
		perror ("read");
		exit (EXIT_FAILURE);

	} else if (nbytes == 0){
		/* End-of-file.  */
	}else {
		/* Data read.  */

		//if (nbytes!=sizeof(prueba_t)) printf("Armamos Bardo\n");
		fprintf (stderr, "Server: envio el struct digamos, y mando el entero:%d \n",*(int*)punt);

    }

}

void* leer_de_cliente (int filedes,size_t tam){

	void* buffer=malloc(tam);

	printf("ESTA LEYENDO\n");

	size_t nbytes;

	nbytes = read (filedes, buffer, tam);
	if (nbytes < 0){
		/* Read error.  */
		free(buffer);
		perror ("read");
		exit (EXIT_FAILURE);
	} else if (nbytes == 0){
		/* End-of-file.  */
		printf("Armamos Bardo\n");
		free(buffer);
		return NULL;
	}else {
		/* Data read.  */
		if (nbytes!=tam)
			printf("Armamos Bardo\n");

		return buffer;
    }
}

void* _escuchar(void* parametros){

	parametrosServer_t* param=(parametrosServer_t*) parametros;

	int sock= param->sock;
	Cola* cola_entrantes=param->entrantes;
	size_t tamanio=param->tamanio;
	fd_set* act=param->act;
	fd_set* rd=param->rd;
	int status;
	int i;

	struct sockaddr_in nombre_cliente;
	size_t size;
//
//	printf("cola en _escuchar: %p \n",cola_entrantes);
//	printf("tamanio en _escuchar: %i \n",tamanio);
//	printf("rd en _escuchar: %p \n",rd);
//	printf("act en _escuchar: %p \n",act);

	while (true){
		/* Block until input arrives on one or more active sockets.  */
		*rd=*act;
		printf("antes select \n");
//		printf ("%p \n", act);
//		printf ("%p \n", rd);

		if (select (FD_SETSIZE, rd, NULL, NULL, NULL) < 0){
			perror ("select");
			exit (EXIT_FAILURE);
		}

		/* Service all the sockets with input pending.  */
		for (i = 0; i < FD_SETSIZE; ++i){
			if (FD_ISSET (i, rd)){

				if (i == sock) {
					/* Connection request on original socket.  */
					size = sizeof (nombre_cliente);
					if ((status=accept (sock,(struct sockaddr *) &nombre_cliente, (unsigned int *)&size)) < 0){
						perror ("accept");
						exit (EXIT_FAILURE);
					}
					fprintf (stderr, "Server: connect from host %s, port %d\n",inet_ntoa (nombre_cliente.sin_addr),ntohs (nombre_cliente.sin_port));
					FD_SET(status, act);

				} else {
					/* Data arriving on an already-connected socket.  */
					void* cambio = leer_de_cliente (i,tamanio);

					if ( cambio == NULL){
						//lo que se hace si llega un dato erroneo
						//close (i);
						//FD_CLR (i, act);
					}else
						cola_entrantes->push(cambio);
				}
			}
		}
    }


	return NULL;
}

void Server::escuchar(size_t tamanio){

	parametrosServer_t *param= inicializar_parametros(tamanio);
	pthread_t thread;
	thread_escuchar=thread;

	if (pthread_create(&thread,NULL,&_escuchar,(void*)param)!=0) return;

}

void* _escribir(void* parametros){
	parametrosServer_t* param=(parametrosServer_t*) parametros;

	int sock=param->sock;
	Cola* cola_salientes=param->salientes;
	size_t tamanio=param->tamanio;
	fd_set* act=param->act;
	int i;

	while (true){
		if (!cola_salientes->empty()){

			void *cambio = cola_salientes->front();
			cola_salientes->pop();
			for (i = 0; i < FD_SETSIZE; ++i){

				if (FD_ISSET (i, act)){

					printf("%d",i);

					if (i!=sock){
						escribir_a_cliente(i,cambio,tamanio);
					}
				}
			}
		}
	}
	return NULL;
}

void Server::escribir(size_t tamanio){

	parametrosServer_t *param= inicializar_parametros(tamanio);
	pthread_t thread;
	thread_escritura=thread;

	if (pthread_create(&thread,NULL,&_escribir,(void*)param)!=0) return;
}

//bool Server::leer_de_cliente (int filedes, void* buffer,size_t tamanio){
//
//
//	int nbytes;
//
//	nbytes = read (filedes, buffer, tamanio);
//	if (nbytes < 0){
//
//		/* Read error.  */ // lo fletamo
//		perror ("read");
//		exit (EXIT_FAILURE);
//
//	} else if (nbytes == 0){
//		/* End-of-file.  */
//		return -1;
//	}else {
//		/* Data read.  */
//
//		if (nbytes!=sizeof(prueba_t)) printf("Armamos Bardo\n");
//		return 0;
//
//    }
//}

/*void Server::informar_cambios(){

	//cambios_nuevos=true;
}*/

//void Server::activar(){
//
//	activado=true;
//
//}
//
//void Server::desactivar(){
//
//	activado=false;
//
//}
//
//
//bool Server::escribir_a_cliente(int filedes,void* buffer,size_t tamanio){
//
//
//
//	int nbytes;
//
//	nbytes = write (filedes, buffer, tamanio);
//	if (nbytes < 0){
//
//		/* write error.  */
//		perror ("write");
//		exit (EXIT_FAILURE);
//
//	} else if (nbytes == 0){
//		/* End-of-file.  */
//		return -1;
//	}else {
//
//		if (nbytes!=sizeof(prueba_t)) printf("Armamos Bardo\n");
//		return 0;
//
//    }
//
//}

//void Server::atender_sockets(){
//
//
//	struct sockaddr_in nombre_cliente;
//	size_t size;
//	int cliente;
//	while (activado){
//
//		/* Bloquear hasta que llegue algo en uno o mas de los sockets activos */
//		leidos = activos;
//		if (select (FD_SETSIZE, &leidos, NULL, NULL, NULL) < 0){
//
//			perror ("select");
//			exit (EXIT_FAILURE);
//
//		}
//
//		/* Service all the sockets with input pending.  */
//		for (int i = 0; i < FD_SETSIZE; ++i)
//			if (FD_ISSET (i, &leidos)){
//
//				if (i == sock) {
//					/* Connection request on original socket.  */
//					size = sizeof (nombre_cliente);
//					if ((cliente=accept (sock,(struct sockaddr *) &nombre_cliente, (unsigned int *)&size)) < 0){
//						perror ("accept");
//						exit (EXIT_FAILURE);
//					}
//					//fprintf (stderr, "Server: connect from host %s, port %d\n",inet_ntoa (nombre_cliente.sin_addr),ntohs (nombre_cliente.sin_port));
//					//eso va para log
//					FD_SET(cliente, &activos);
//				} else {
//					/* Datos llegando de un socket ya conectado.  */
//					prueba_t struct_entrante;
//					if (leer_de_cliente (i,&struct_entrante,sizeof(struct_entrante)) < 0){
//						close (i);
//						FD_CLR (i, &activos);
//					}
//
//					// guardar el struct entrante en el mapa con el ID en su clave
//
//					cambios_entrantes->insert(pair <int,prueba_t> (struct_entrante.ID,struct_entrante));
//
//					// if hay cambios nuevos: escribir aca?
//					if (cambios_nuevos) escribir_a_cliente(i,cambios_salientes,sizeof(cambios_salientes)); // esto hay que hacerlo en otro thread
//
//
//
//				}
//			}
//    cambios_nuevos=false;
//
//	}
//
//
//}

//void Server::iniciar (){
//
//
//
//	fd_set conjunto_activos, conjunto_read;
//	activos=conjunto_activos;
//	leidos=conjunto_read;
//
//	/* Crear el socket e inicializarlo para aceptar conexiones  */
//
//	sock = crear_socket (puerto);
//
//	if (listen (sock, 10) < 0){
//		perror ("listen");
//		exit (EXIT_FAILURE);
//    }
//
//	/* Inicializar el conjunto de sockets activos.  */
//	FD_ZERO (&conjunto_activos);
//	FD_SET (sock, &conjunto_activos);
//
//	activar();
//
//
//}


