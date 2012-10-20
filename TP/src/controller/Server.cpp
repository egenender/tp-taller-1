/*
 * Server.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: juaqi
 */


#include "Server.h"
#include "LectorArchivo.h"
#include "SDL/SDL.h"
#include "GestorConfiguraciones.h"

Server* Server::instancia= NULL;

Server::Server(){

	puerto=PORT;
	activos=fd_set();
	leidos=fd_set();
	activado=true;
	cola_entrantes=Cola();
	cola_salientes=Cola();
	//cambios_entrantes= new mapa_cambios();
	//cambios_nuevos=false;

	//Crear el socket e inicializar para que comience a escuchar conexiones
	sock = crear_socket (puerto);

	if (listen (sock, 1) < 0){
		perror ("listen");
	}

	// Inicialza el set de sockets activos
	FD_ZERO (&activos);
	FD_SET (sock, &activos);

}

Server* Server::obtenerInstancia(int puerto) {
   if( instancia == NULL || !instancia->activado){
	   instancia = new Server(puerto);
   }
   return instancia;
}

Server::Server(int port){

	puerto=port;
	activos=fd_set();
	leidos=fd_set();
	activado=true;
	cola_entrantes=Cola();
	cola_salientes=Cola();
	//cambios_entrantes= new mapa_cambios();
	//cambios_nuevos=false;

	sock = crear_socket (puerto);

	if (listen (sock, 10) < 0){
		activado = false;
    }

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

bool Server::estaActivo(){
	return activado;
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

	// Se crea el socket
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		activado = false;
	}

	// Se le pasan los parametros para asociar el socket a una direccion
	name.sin_family = AF_INET;
	name.sin_port = htons (port);
	name.sin_addr.s_addr = htonl (INADDR_ANY); // INADDR_ANY ES LA DIRECCION IP DE LA PROPIA MAQUINA
	if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0){
		activado = false;
		Log::getInstance()->writeToLogFile("ERROR","La direccion del server ya esta en uso");
		return 0;
	}

	return sock;
}

void Server::escribir_a_cliente(int i, void* punt,size_t tam){

	int nbytes;

	nbytes = write (i, punt, tam);

	if (nbytes <=0){
		// Manejar error de lectura


	}
}

void escribir_a_cliente(int i, void* punt,size_t tam){

	int nbytes;

	nbytes = write (i, punt, tam);

	if (nbytes < 0){

		// Manejar error de escritura

    }

}

void* leer_de_cliente (int filedes,size_t tam){

	void* buffer=malloc(tam);

	printf("ESTA LEYENDO\n");

	size_t nbytes;

	nbytes = read (filedes, buffer, tam);
	if (nbytes < 0){
		free(buffer);
		// Manejar error de lectura
		return NULL;

	} else if (nbytes == 0){
		printf("Armamos Bardo\n");
		free(buffer);
		return NULL;
	}else {

		if (nbytes!=tam)
			printf("Armamos Bardo\n");

		return buffer;
    }
}

void* _enviar_inicializacion(void* parametros){

	//Mandar todos los archivos para inicializar

	int cliente=((parametrosInit_t*)parametros)->sock;
	fd_set* conjuntoClientes=((parametrosInit_t*)parametros)->act;

	pthread_mutex_t mutex;

	pthread_mutex_init (&mutex , NULL);

	pthread_mutex_lock(&mutex);

	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();



	std::vector<string>* rutas= gestor->devolverVectorRutas();
//	std::vector<string>* rutas = new vector<string>;
//	string rut = "src/config/defecto.yaml";
//	rutas->push_back(rut);
//	rut = "src/config/archivoYaml.yaml";
//	rutas->push_back(rut);

	string headerTemp ="Temp/";
//	int* entero = (int*) malloc (sizeof (int));

	int enteroS;
	int* entero=&enteroS;
	for (unsigned int i=0; i< rutas->size() ;i++){

		string rutaServer=(rutas->at(i));
		string rutaCompleta = headerTemp + rutaServer;

		cout<<rutaCompleta<< endl;

		*entero= rutaCompleta.size();

		cout<<*entero<< endl;
		escribir_a_cliente(cliente, entero, (sizeof(int)));

		unsigned int j = 0;
		int k = 0;
		int* carac = (int*) malloc (sizeof (int));
		for(j=0; j<  (rutaCompleta.size())  ;j++){
			*carac =  rutaCompleta[j];
			escribir_a_cliente(cliente, carac, ( 1*sizeof(int) ) );
		}

		LectorArchivo* l = new LectorArchivo(rutaServer.c_str());
		int cant;
		int* todo = l->LeerArchivo(&cant);

		*entero=cant;
		escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

		for(k=0;k<cant;k++){
			*entero = todo[k];
			escribir_a_cliente(cliente, entero, ( 1*sizeof(int) ) );
		}
		l->CerrarArchivo();

	}

	*entero = -1;
	escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

	//mando nivel a jugar
	*entero = gestor->ObtenerNivelElegido();
	escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

	//mando disponibilidad de protagonista
	std::vector<TipoProtagonista*>* tiposProt = gestor->ObtenerPosiblesTiposProtagonistas();
	for (unsigned int i; i< tiposProt->size(); i++){
		*entero = 0;
		if (tiposProt->at(i)->disponible)
			*entero = 1;
		escribir_a_cliente(cliente, entero, ( sizeof(int) ) );
	}
	*entero = -1;
	escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

	void* elegido = leer_de_cliente(cliente,sizeof(int));
	while (elegido == NULL)
		void* elegido = leer_de_cliente(cliente,sizeof(int));

	*entero = 1;
	if ((tiposProt->at( *(int*)elegido)->disponible) == 0){
		*entero = 0;
	}
	escribir_a_cliente(cliente, entero, ( sizeof(int) ) );
	cout << "mando  " << *entero << endl;

//	free(entero);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	pthread_mutex_t mutexSet;

	pthread_mutex_init (&mutexSet , NULL);

	pthread_mutex_lock(&mutexSet);

	FD_SET(cliente, conjuntoClientes);

	pthread_mutex_unlock(&mutexSet);

	pthread_mutex_destroy(&mutexSet);
	return NULL;
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

//	printf("cola en _escuchar: %p \n",cola_entrantes);
//	printf("tamanio en _escuchar: %i \n",tamanio);
//	printf("rd en _escuchar: %p \n",rd);
//	printf("act en _escuchar: %p \n",act);

	while (true){

		pthread_mutex_t mutex;

		pthread_mutex_init (&mutex , NULL);

		pthread_mutex_lock(&mutex);

		// Parar la ejecucion hasta que llegue algo en alguno de los sockets del conjunto
		*rd=*act;
		if (select (FD_SETSIZE, rd, NULL, NULL, NULL) < 0){
			// Manejar error select
		}

		pthread_mutex_unlock(&mutex);

		pthread_mutex_destroy(&mutex);

		// Ahora estan los sockets pidiendo permiso, atenderlos:
		for (i = 0; i < FD_SETSIZE; ++i){
			if (FD_ISSET (i, rd)){

				if (i == sock) {
					// Si el socket es sock (el que acepta conexiones) quiere decir que le estan pidiendo conectarse
					size = sizeof (nombre_cliente);
					if ((status=accept (sock,(struct sockaddr *) &nombre_cliente, (unsigned int *)&size)) < 0){
						// Manejar error accept

					}
					fprintf (stderr, "Server: conexion del host %s, en puerto %d\n",inet_ntoa (nombre_cliente.sin_addr),ntohs (nombre_cliente.sin_port));

					//Aca el thread de inicializacion, en el que se deberia agregar a "status" al set de sockets
					pthread_t threadInicializacion;

					parametrosInit_t* param=(parametrosInit_t*)malloc(sizeof(parametrosInit_t));
					param->act=act;
					param->sock=status;
					pthread_create(&threadInicializacion,NULL,&_enviar_inicializacion,param);

				} else {
					// Aca llegan datos de un socket ya conectado
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

