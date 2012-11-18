#ifndef SERVER_H
#define SERVER_H

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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <map>
#include <queue>
#include <pthread.h>
#include "../model/Timer.h"

using namespace std;

#define PORT	5556
#define TIEMPO_ENVIO 7
#define TIME_OUT_SERVER  100
#define CLIENTE_TIME_OUT 50

typedef struct prueba{


	int ID;
	int entero;


}prueba_t;

//typedef std::map <int,prueba_t> mapa_cambios;
//typedef std::map <int,int> mapa_sockid;

typedef queue <void*> Cola ;

typedef struct parametrosServer{

	Cola* entrantes;
	Cola* salientes;
	size_t tamanio;
	fd_set* act;
	fd_set* rd;
	int sock;
	int puerto;
	std::map <int,bool> *sockets;
	std::map <int,int> *IDsockets;

} parametrosServer_t;

typedef struct parametrosInicializacion{

	fd_set* act;
	int sock;
	std::map <int,bool> *sockets;
	std::map <int,int> *IDsockets;

} parametrosInit_t;

class Server{

	// CUESTION: thread para mandar tambien? respuesta: si
	// CUESTION: tema del head, que es lo que manda al principio para especificar el tamanio

	public:
		//dice si ese socket esta apto estado estacionario
		std::map <int,bool> *sockets;
		//me dice, para cada socket, el id
		std::map <int,int> *IDsockets;

		std::map <int,Timer*> *timerSockets;

		fd_set activos;
		bool desco;

		bool aceptando;

		Timer* envio;

		int yaJugando;

		int sock;
		bool jugando;
	private:

		static Server* instancia;

		// Atributos viejos
		//mapa_cambios* cambios_entrantes;
		//prueba_t* cambios_salientes;
		//bool cambios_nuevos;

		// Esta es la cola de la que se iran desencolando los cambios que ingresen de los clientes
		Cola cola_entrantes;
		// Mismo, pero los cambios que deben salir a los clientes
		Cola cola_salientes;

		// Crea un socket a partir de un puerto en el servidor
		int crear_socket (unsigned short int);

		// Atributo puerto del servidor
		unsigned short int puerto;
		// Esta activado o no
		bool activado;
		// Conjuntos de sockets (veremos esto)
		fd_set leidos;
		// El file descriptor del socket del servidor

		pthread_t thread_escuchar;
		pthread_t thread_escritura;

	public:

	static Server* obtenerInstancia(int);
	static Server* reiniciarInstancia(int);

		// Metodos viejos
		//void atender_sockets(void);
		//void informar_cambios();
		//bool leer_de_cliente (int, void*,size_t);
		//bool escribir_a_cliente(int,void*,size_t);
		//void iniciar ();
		//void activar();
		//void desactivar();

		// Crea un server asi noma
		Server();

		// Crea un server especificando un Port
		Server(int);

		parametrosServer_t* inicializar_parametros(size_t);

		bool estaActivo();

		// Esto deberia crear un thread que empiece a escuchar a los clientes que le piden conexion,
		// aceptarlos y encolar sus cambios entrantes
		void escuchar(size_t);

		void escribir(size_t);

		void escribir_a_cliente(int, void*, size_t);

		// Esto deberia desencolar de las cosas que le mandan para escribir y mandarlo a todos los clientes
		int escribir_cambio();

		// Encola un cambio para recibir (servidor: recibir cambio)
		int recibir_cambio(void*);

		// desencola un cambio para mandar (enviar cambio a servidor)
		void encolar_cambio(void*);

		void Autoencolar_cambio(void* cambio);

		// Devuelve el cambio mas actual (de la cola) para aplicar en el modelo
		void* devolver_cambio();

		bool hay_cambios();

		void* desencolar_cambio();

		// Detener al server
		void detener ();

		void detenerServer();

		void detener_escribir();
		void detener_escuchar();

};

#endif
