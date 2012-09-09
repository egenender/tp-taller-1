/*
 * Princesa.cpp
 *
 *  Created on: 09/09/2012
 *      Author: martin
 */

#include "Princesa.h"

Princesa::Princesa(Area* sup, Animacion* anim){
	//Idem Mono
}
Princesa::Princesa(Area* sup, Animacion* anim, EstrategiaMovimiento* estr):Personaje(sup,anim,estr){

}
Princesa::~Princesa():~Personaje(){

}

void Princesa::moverAIzquierda(){
	//No hace nada
}

void Princesa::moverADerecha(){
	//No hace nada
}
void Princesa::atacar(){
	//No hace nada
}
void Princesa::saltar(){
	//No hace nada
}
void Princesa::especial(){
	//Llora pidiendo clemencia (?)
}


