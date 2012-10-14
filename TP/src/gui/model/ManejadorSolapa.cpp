#include "ManejadorSolapa.h"

ManejadorSolapa::ManejadorSolapa(lista_t* s1, lista_t* s2) {
	lista_aparecer = s1;
	lista_desaparecer = s2;
}

void destructor(void* objeto){
	ObjetoGUI* ui = (ObjetoGUI*)objeto;
	delete (ui);
}

ManejadorSolapa::~ManejadorSolapa() {
	//lista_destruir(solapa1,destructor);
	//lista_destruir(solapa2,destructor);
	//lista_destruir(lista_aparecer,NULL);
	//lista_destruir(lista_desaparecer,NULL);
}

void ManejadorSolapa::manejarClic(){
	deshabilitar(lista_desaparecer);
	habilitar(lista_aparecer);
}

void ManejadorSolapa::habilitar(lista_t* solapa){
	habilitacion(solapa,true);
}

void ManejadorSolapa::deshabilitar(lista_t* solapa){
	habilitacion(solapa,false);
}

void ManejadorSolapa::habilitacion(lista_t* solapa, bool habilitar){
	lista_iter_t* iter = lista_iter_crear(solapa);
	while (!lista_iter_al_final(iter)){
		ObjetoGUI* ui = (ObjetoGUI*)lista_iter_ver_actual(iter);
		if (habilitar){
			ui->hacerVisible();
		}else{
			ui->hacerInvisible();
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
}
