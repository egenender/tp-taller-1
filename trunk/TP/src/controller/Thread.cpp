/*
 * Thread.cpp
 *
 *  Created on: Oct 13, 2012
 *      Author: juaqi
 */


#include "Thread.h"

Thread::Thread(void *(*funcion) (void *)){

	pthread_t thread;

	pthread_create(&thread,NULL,funcion,NULL);

	hilo=thread;



}

Thread::Thread(pthread_attr_t attr ,void *(*funcion) (void *),void* parametro_inicial){


	pthread_t thread;

	pthread_create(&thread,&attr,funcion,parametro_inicial);

	hilo=thread;

}

int Thread::cancelar(){


	return pthread_cancel(hilo);

}

