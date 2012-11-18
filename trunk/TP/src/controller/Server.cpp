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
#include "../model/structures/structCliente.h"
#include "../model/structures/structServidor.h"
#include "../model/ContenedorManuales.h"
#include "Nivel.h"
#include "../log/Log.h"

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
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se abre un socket server");

	if (listen (sock, 1) < 0){
		perror ("listen");
	}

	// Inicialza el set de sockets activos
	FD_ZERO (&activos);
	FD_SET (sock, &activos);

	sockets = new std::map <int,bool>();
	IDsockets = new std::map <int,int>();

	desco = false;
	envio = new Timer();
	timerSockets = new std::map <int,Timer*>();

	aceptando = true;
	yaJugando = 0;
}

Server* Server::reiniciarInstancia(int port) {
    instancia = new Server(port);

   return instancia;
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
	if (sock > 0)
		Log::getInstance()->writeToLogFile("INFO","SOCK: Se abre un socket server");

	if (listen (sock, 10) < 0){
		activado = false;
    }

	FD_ZERO (&activos);
	FD_SET ( sock , &activos);

	sockets = new std::map <int,bool>();
	IDsockets = new std::map <int,int>();

	desco = false;
	envio = new Timer();
	timerSockets = new std::map <int,Timer*>();

	aceptando = true;

	yaJugando = 0;

}

void detenerServer(){
	Server* server = Server::obtenerInstancia(0);
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	unsigned int i;
	for (i = 0; i < FD_SETSIZE; ++i){
			if (FD_ISSET (i, &server->activos)){
				server->sockets->erase(i);
				close(i);
			}
	}
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se cerraron todos los sockets");
	GestorConfiguraciones::getInstance()->acabarGestor();
	Log::getInstance()->writeToLogFile("INFO","PARSER: Se cierra el Parser");
	server->detener_escuchar();
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se cierra thread escucha");
	server->detener_escribir();
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se cierra thread escritura");
	server->detener();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

}


void Server::detenerServer(){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	unsigned int i;
	for (i = 0; i < FD_SETSIZE; ++i){
			if (FD_ISSET (i, &activos)){
				close(i);
			}
	}
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se cerraron todos los sockets");
	GestorConfiguraciones::getInstance()->acabarGestor();
	Log::getInstance()->writeToLogFile("INFO","PARSER: Se cierra el Parser");
	pthread_cancel(thread_escuchar);
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se cierra thread escucha");
	pthread_cancel(thread_escritura);
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se cierra thread escritura");
	close(sock);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

bool Server::hay_cambios(){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	return !cola_entrantes.empty();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

}

void Server::encolar_cambio(void* cambio){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	cola_salientes.push(cambio);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

}

void Server::Autoencolar_cambio(void* cambio){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	cola_entrantes.push(cambio);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

}

void* Server::desencolar_cambio(){
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	void* cambio= cola_entrantes.front();
	cola_entrantes.pop();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

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
	parametros->sockets=sockets;
	parametros->IDsockets=IDsockets;

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

	size_t nbytes;

	nbytes = read (filedes, buffer, tam);
	if (nbytes < 0){
		free(buffer);
		// Manejar error de lectura
		return NULL;

	} else if (nbytes == 0){
		free(buffer);
		return NULL;
	}else {

		return buffer;
    }
}

void mandarComienzo(void* parametros){
	fd_set* clientes=((parametrosInit_t*)parametros)->act;
	std::map <int,bool> *sockets = ((parametrosInit_t*)parametros)->sockets;
	int i, sock, num;
	num = 0;

	Server* server = Server::obtenerInstancia(0);
	sock = server->sock;

	for ( i = 0; i < FD_SETSIZE; ++i){
		if (FD_ISSET (i, clientes)){
			if (i != sock) {
				//if(sockets->at(i))
					server->escribir_a_cliente(i, &num, sizeof(int) );
			}
		}
	}
}


void* _enviar_inicializacion(void* parametros){

	//Mandar todos los archivos para inicializar

	int cliente=((parametrosInit_t*)parametros)->sock;
	fd_set* conjuntoClientes=((parametrosInit_t*)parametros)->act;
	std::map <int,bool> *sockets = ((parametrosInit_t*)parametros)->sockets;
	std::map <int,int> *IDsockets = ((parametrosInit_t*)parametros)->IDsockets;

	pthread_mutex_t mutex;

	pthread_mutex_init (&mutex , NULL);

	pthread_mutex_lock(&mutex);

	Log::getInstance()->writeToLogFile("INFO","SOCK: Se empiezan a establecer recursos del cliente");
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	std::vector<string>* rutas= gestor->devolverVectorRutas();

	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	string headerTemp ="Temp/";

	int enteroS;
	int* entero=&enteroS;
	for (unsigned int i=0; i< rutas->size() ;i++){

		string rutaServer=(rutas->at(i));
		string rutaCompleta = headerTemp + rutaServer;

		Log::getInstance()->writeToLogFile("INFO","SOCK: Se envia archivo al cliente");
		cout<<rutaCompleta<< endl;

		*entero= rutaCompleta.size();

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

	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se envia nivel a jugar");
	*entero = gestor->ObtenerNivelElegido();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

	//mando disponibilidad de protagonista
	Log::getInstance()->writeToLogFile("INFO","SOCK: Se envia disponibilidad de protagonistas");
	std::vector<TipoProtagonista*>* tiposProt = gestor->ObtenerPosiblesTiposProtagonistas();
	for (unsigned int i; i< tiposProt->size(); i++){
		*entero = 0;
		if (tiposProt->at(i)->disponible)
			*entero = 1;
		escribir_a_cliente(cliente, entero, ( sizeof(int) ) );
	}

	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	*entero = -1;
	escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

	//TODO: no asumir que la eleccion es buena
	
	void* elegido;
	int idElegida;
	while(*entero!=1){
		//recibo eleccion de cliente
		elegido = leer_de_cliente(cliente,sizeof(int)); //una sola lectura???
		//while (elegido == NULL)
		//		elegido = leer_de_cliente(cliente,sizeof(int));
		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);

		if (elegido == NULL){
			idElegida = -1;
			break;
		}
		idElegida = *(int*)elegido;

		if (idElegida == -1)
			break;

		//le respondo si puede o no usarlo
		*entero = 0;
		if ((tiposProt->at( idElegida )->disponible) == true){
			*entero = 1;
			tiposProt->at( idElegida )->disponible = false;
			Log::getInstance()->writeToLogFile("INFO","SOCK: La eleccion de protagonista es correcta");
		}
		escribir_a_cliente(cliente, entero, ( sizeof(int) ) );

		if( *entero == 1 ){
			Server::obtenerInstancia(0)->yaJugando++;

			if (Server::obtenerInstancia(0)->yaJugando == gestor->obtenerCantidadDeJugadores()){
				mandarComienzo( parametros);
				Nivel::obtenerInstancia()->sePuedeJugar();
				Server::obtenerInstancia(0)->jugando = true;
			}
		}

	}

	IDsockets->insert(pair<int,int>(cliente, idElegida ));
	if (idElegida == -1){
		Log::getInstance()->writeToLogFile("INFO","SOCK: El cliente se ha desconectado, no elegio personaje");
		Server* server = Server::obtenerInstancia(0);
		pthread_mutex_t mutex;
		SDL_Delay(200);
		pthread_mutex_init (&mutex , NULL);
		pthread_mutex_lock(&mutex);
		FD_CLR (cliente, &server->activos);
		close (cliente);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);
		return NULL;
	}

	pthread_mutex_init (&mutex , NULL);
	pthread_mutex_lock(&mutex);
	gestor->crearManual( idElegida );

	//IDsockets->insert(pair<int,int>(cliente, idElegida ));
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	pthread_mutex_t mutexSet;
	pthread_mutex_init (&mutexSet , NULL);
	pthread_mutex_lock(&mutexSet);

	sockets->erase(cliente);
	sockets->insert(pair<int,int>(cliente, true ));

	Server* server = Server::obtenerInstancia(0);

	server->timerSockets->erase(cliente);
	server->timerSockets->insert(pair<int,Timer*>(cliente, new Timer() ));
	server->timerSockets->at(cliente)->comenzar();

	ContenedorManuales* manualesYaConectados = gestor->obtenerContenedorManuales();
	manualesYaConectados->encolarTodos();
	//FD_SET(cliente, conjuntoClientes);

	server->envio->comenzar();
	pthread_mutex_unlock(&mutexSet);
	pthread_mutex_destroy(&mutexSet);
	return NULL;
}

void _TerminarCliente(int cliente){
	Server* server = Server::obtenerInstancia(0);
	//lo que se hace si llega un dato erroneo
	Log::getInstance()->writeToLogFile("INFO","SOCK: El cliente se ha desconectado");
	
	int IDabandona = server->IDsockets->at(cliente);
	server->IDsockets->erase(cliente);
	server->sockets->erase(cliente);
	server->sockets->insert(pair<int,int>(cliente, false ));
	server->timerSockets->erase(cliente);
	//close(cliente); esto hacia que rompa

	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();
	std::vector<TipoProtagonista*>* tiposProt = gestor->ObtenerPosiblesTiposProtagonistas();
	tiposProt->at(IDabandona)->disponible = true;

//	close (cliente);
	FD_CLR (cliente, &server->activos);
}

void* _escuchar(void* parametros){

	parametrosServer_t* param=(parametrosServer_t*) parametros;

	int sock= param->sock;
	Cola* cola_entrantes=param->entrantes;
	size_t tamanio=param->tamanio;
	fd_set* act=param->act;
	fd_set* rd=param->rd;
	std::map <int,bool> *sockets = param->sockets;
	std::map <int,int> *IDsockets = param->IDsockets;
	int status;
	int i;

	struct sockaddr_in nombre_cliente;
	size_t size;

	struct timeval intervaloTiempo;

	while (true){

		pthread_mutex_t mutex;

		pthread_mutex_init (&mutex , NULL);

		pthread_mutex_lock(&mutex);

		intervaloTiempo.tv_sec=TIME_OUT_SERVER;
		intervaloTiempo.tv_usec=0;

		Server *server = Server::obtenerInstancia(0);
		// Parar la ejecucion hasta que llegue algo en alguno de los sockets del conjunto
		*rd=*act;
		if(select(FD_SETSIZE,rd,NULL,NULL,&intervaloTiempo)==0){
			if (server->IDsockets->size() > 0){
				server->desco = true;
				server->IDsockets = new std::map <int,int> ();
				Log::getInstance()->writeToLogFile("INFO","SOCK: Se han desconectado todos los clientes por Time Out");
			}
		}

		for (unsigned int j = 0; j < FD_SETSIZE; ++j){
			try{
				if (server->timerSockets->at(j)->obtenerTiempo() >= 1000*CLIENTE_TIME_OUT){
					structCliente_t* haMuerto =  structCliente_crear( IDsockets->at(j) , MUERTO );
					server->Autoencolar_cambio(haMuerto);
					_TerminarCliente(j);
				}
			}catch (std::out_of_range &e){

			}
		}
		pthread_mutex_unlock(&mutex);

		pthread_mutex_destroy(&mutex);

		// Ahora estan los sockets pidiendo permiso, atenderlos:
		for (i = 0; i < FD_SETSIZE; ++i){
			if (FD_ISSET (i, rd)){
				if (i == sock) {
					Server* server = Server::obtenerInstancia(0);
					if (! server->aceptando)
						continue;
					Log::getInstance()->writeToLogFile("INFO","SOCK: Se inicia la escucha del server");
					// Si el socket es sock (el que acepta conexiones) quiere decir que le estan pidiendo conectarse
					size = sizeof (nombre_cliente);
					if ((status=accept (sock,(struct sockaddr *) &nombre_cliente, (unsigned int *)&size)) < 0){
						// Manejar error accept

					}
					Log::getInstance()->writeToLogFile("INFO","SOCK: Se realizo la conexion");
					fprintf (stderr, "Server: conecto con cliente: %s, en puerto: %d\n",inet_ntoa (nombre_cliente.sin_addr),ntohs (nombre_cliente.sin_port));

					sockets->erase(status);
					sockets->insert(pair<int,bool>(status,false));

					if (sockets->size() == GestorConfiguraciones::getInstance()->obtenerCantidadDeJugadores())
						server->aceptando = false;

					//Aca el thread de inicializacion, en el que se deberia agregar a "status" al set de sockets
					pthread_t threadInicializacion;

					parametrosInit_t* param=(parametrosInit_t*)malloc(sizeof(parametrosInit_t));
					param->act=act;
					param->sock=status;
					param->sockets=sockets;
					param->IDsockets=IDsockets;
					pthread_create(&threadInicializacion,NULL,&_enviar_inicializacion,param);

					FD_SET(status,act);

				} else {
					// Aca llegan datos de un socket ya conectado
					void* cambio = leer_de_cliente (i,tamanio);

					if ( cambio == NULL){
						//lo que se hace si llega un dato erroneo
						Log::getInstance()->writeToLogFile("INFO","SOCK: Un cliente abandono la partida");
						int IDabandona = IDsockets->at(i);
						IDsockets->erase(i);
						sockets->erase(i);
						sockets->insert(pair<int,bool>(i,false));

						server->timerSockets->erase(i);

						structCliente_t* haMuerto =  structCliente_crear( IDabandona , MUERTO );
						server->Autoencolar_cambio(haMuerto);

						GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();
						std::vector<TipoProtagonista*>* tiposProt = gestor->ObtenerPosiblesTiposProtagonistas();
						try{
							tiposProt->at(IDabandona)->disponible = true;
						}catch(std::out_of_range &e){
							//nada, es que el cliente no se termino de conectar
						}

						close (i);
						FD_CLR (i, act);

						server->desco = true;
					}else{
						// preguntamos si esta habilitado
						Log::getInstance()->writeToLogFile("INFO","SOCK: A server llega struct");
						if (sockets->at(i)){
							pthread_mutex_t mutex;
							pthread_mutex_init (&mutex , NULL);
							pthread_mutex_lock(&mutex);

							Server* server = Server::obtenerInstancia(0);
							server->timerSockets->at(i)->detener();
							server->timerSockets->at(i)->comenzar();

							cola_entrantes->push(cambio);
							int estado = structCliente_obtener_estado( (structCliente_t*) cambio);
							if(estado == MUERTO){
								_TerminarCliente(i);
								Server *server = Server::obtenerInstancia(0);
								server->desco = true;
							}
							pthread_mutex_unlock(&mutex);
							pthread_mutex_destroy(&mutex);

						}else{
							printf("llego antes un paquete\n");
						}
					}
				}
			}
		}
	}


	return NULL;
}

void Server::escuchar(size_t tamanio){

	parametrosServer_t *param= inicializar_parametros(tamanio);
	pthread_t thread = 0;
	thread_escuchar=thread;

	if (pthread_create(&thread_escuchar,NULL,&_escuchar,(void*)param)!=0) return;

}

void* _escribir(void* parametros){
	parametrosServer_t* param=(parametrosServer_t*) parametros;

	int sock=param->sock;
	Cola* cola_salientes=param->salientes;
	size_t tamanio=param->tamanio;
	fd_set* act=param->act;
	std::map <int,bool> *sockets = param->sockets;
	int i;
	Log::getInstance()->writeToLogFile("INFO","PARSER: Se inicia la escritura del server");

	while (true){
		if ( !Server::obtenerInstancia(0)->jugando )
			continue ;

		if (!cola_salientes->empty()){

			void *cambio = cola_salientes->front();
			cola_salientes->pop();
			for (i = 0; i < FD_SETSIZE; ++i){

				if (FD_ISSET (i, act)){
					if (i!=sock){
						if(sockets->at(i)){
							escribir_a_cliente(i,cambio,tamanio);
							printf("se envia struct\n");
						}
					}
				}
			}
		}
	}
	return NULL;
}

void Server::escribir(size_t tamanio){

	parametrosServer_t *param= inicializar_parametros(tamanio);
	pthread_t thread = 0;
	thread_escritura=thread;

	if (pthread_create(&thread_escritura,NULL,&_escribir,(void*)param)!=0) return;
}

void Server::detener(){

	close(sock);

}


void Server::detener_escribir(){

	pthread_cancel(thread_escritura);

}

void Server::detener_escuchar(){

	pthread_cancel(thread_escuchar);

}



