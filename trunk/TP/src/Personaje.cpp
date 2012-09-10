#include "Personaje.h"

Personaje::Personaje(Area* sup, Animacion* anim, EstrategiaMovimiento* estr):Cuerpo(sup,anim) {
	//Llama al constructor de la clase madre con los parametros de la animacion
	//y la superficie que ocupa
	estrategia = estr;
}

Personaje::~Personaje(){
	delete estrategia;
}

void Personaje::jugar(){
	estrategia->actuar(); //Revisar si estoy pasando el objeto o la referencia
}

void Personaje::morir(){
	vivo = false;
	//algo mas?
}

void Personaje::trasladarA(Posicion* pos){
	superficieOcupada->cambiarPosicion(pos);
}
