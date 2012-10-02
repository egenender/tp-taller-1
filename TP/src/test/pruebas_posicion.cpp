/*
 * pruebas_posicion.cpp
 *
 *  Created on: 06/09/2012
 *      Author: martin
 */

#include "../model/Posicion.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

/* Funcion auxiliar para imprimir si estuvo OK o no. */
void print_test(const char* name, bool result){
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void pruebas_posicionCreada(){
	Posicion *pos = new Posicion();
	print_test("1. La posicion al iniciar es (0,0)", pos->obtenerX()==0 && pos->obtenerY()==0);
	Posicion *pos2 = new Posicion(3,4);
	print_test("2. La posicion al iniciar es (3,4)", pos2->obtenerX()==3 && pos2->obtenerY()==4);

	delete pos;
	delete pos2;
}

void pruebas_posicionAdyacentes(){
	Posicion *pos = new Posicion(5,5);
	Posicion *pos2 = (Posicion*)malloc (sizeof(Posicion*));
	/**pos2 = pos->obtenerDerecha();
	print_test("3. La posicion a la derecha del (5,5) es (6,5)", pos2->getX()==6 && pos2->getY()==5);

	*pos2 = pos->obtenerArriba();
	print_test("4. La posicion arriba del (5,5) es (5,4)", pos2->getX()==5 && pos2->getY()==4);


	*pos2 = pos->obtenerAbajo();
	print_test("5. La posicion abajo del (5,5) es (5,6)", pos2->getX()==5 && pos2->getY()==6);

	*pos2 = pos->obtenerIzquierda();*/
	print_test("6. La posicion a la izquierda del (5,5) es (4,5)", pos2->obtenerX()==4 && pos2->obtenerY()==5);
	delete pos2;
	delete pos;
	free(pos);
	free(pos2);
}

void pruebas_posicionVerficarAdyacencia(){
	Posicion* pos = new Posicion(5,5);
	Posicion* pos2 = new Posicion (5,5);
	Posicion* pos3 = new Posicion (5,0);
	Posicion* pos4 = new Posicion(10,13);

	print_test ("7. El (5,5) esta en el mismo lugar que el (5,5)", !pos->estaALaDerechaDe(*pos2) && !pos->estaALaIzquierdaDe(*pos2) && !pos->estaArribaDe(*pos2) && !pos->estaAbajoDe(*pos2));
	print_test("8. El (5,5) esta abajo del (5,0)", pos->estaAbajoDe(*pos3));
	print_test("9. El (5,5) esta arriba del (10,13)", pos->estaArribaDe(*pos4));
	print_test("10. El (5,5) esta a la izquierda del (10,13)", pos->estaALaIzquierdaDe(*pos4));

	delete pos;
	delete pos2;
	delete pos3;
	delete pos4;
}

void pruebas(){
	pruebas_posicionCreada();
	pruebas_posicionAdyacentes();
	pruebas_posicionVerficarAdyacencia();
}

/*int main (void){
	pruebas();
	return 0;
}*/
