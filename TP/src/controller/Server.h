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
#include <queue>
using namespace std;

#define PORT	5555
typedef struct prueba{


	int ID;
	int entero;


}prueba_t;

//typedef std::map <int,prueba_t> mapa_cambios;
//typedef std::map <int,int> mapa_sockid;

typedef queue <void*> Cola ;

class Server{

	// CUESTION: thread para mandar tambien?

	private:

		// Atributos viejos
		//mapa_cambios* cambios_entrantes;
		//prueba_t* cambios_salientes;
		//bool cambios_nuevos;

		// No estoy seguro de la necesidad de que esten LAS DOS colas, pero prefiero mas que menos

		// Esta es la cola de la que se iran desencolando los cambios que ingresen de los clientes
		// (por ahora tipo de dato void* hasta decision)
		Cola cola_entrantes;
		// Mismo, pero los cambios que deben salir a los clientes
		Cola cola_salientes;

		// Crea un socket a partir de un puerto en el servidor
		int crear_socket (unsigned short int);

		// Atributo puerto del servidor
		int puerto;
		// Esta activado o no
		bool activado;
		// Conjuntos de sockets (veremos esto)
		fd_set activos,leidos;
		// El file descriptor del socket del servidor
		int sock;

	public:

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

		// Esto deberia crear un thread que empiece a escuchar a los clientes que le piden conexion,
		// aceptarlos y encolar sus cambios entrantes
		int escuchar();

		// Esto deberia desencolar de las cosas que le mandan para escribir y mandarlo a todos los clientes
		int escribir_cambio();

		// Encola un cambio para recibir (servidor: recibir cambio)
		int recibir_cambio(void*);

		// Encola un cambio para mandar (enviar cambio a servidor)
		int enviar_cambio(void*);

		// Devuelve el cambio mas actual (de la cola) para aplicar en el modelo
		void* devolver_cambio();

		// Detener al server
		int detener ();





};
