/*
 * Thread.h
 *
 *  Created on: Oct 13, 2012
 *      Author: juaqi
 */

#include <pthread.h>

class Thread {

	private:

		pthread_t hilo;

	public:
		// 1: funcion a pasarle al thread para correr (recibe void* devuelve void*)
		Thread(void *(*__start_routine) (void *));
		//1: puntero adonde va el thread 2:estructura de atributos para el thread (NULL por ahora) 3: funcion a correr en el thread
		// 4: parametro a pasarle al thread
		Thread(pthread_attr_t ,void *(*__start_routine) (void *),void*);
		// Termina el thread que esta corriendo
		int cancelar();


};


