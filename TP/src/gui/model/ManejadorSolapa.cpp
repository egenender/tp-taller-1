#include "ManejadorSolapa.h"

ManejadorSolapa::ManejadorSolapa(lista_t* s1, lista_t* s2) {
	solapa1 = s1;
	solapa2 = s2;
	estado = NINGUNO;
}

void destructor(void* objeto){
	ObjetoGUI* ui = (ObjetoGUI*)objeto;
	delete (ui);
}

ManejadorSolapa::~ManejadorSolapa() {
	//lista_destruir(solapa1,destructor);
	//lista_destruir(solapa2,destructor);
	lista_destruir(solapa1,NULL);
	lista_destruir(solapa2,NULL);
}

void ManejadorSolapa::manejarClic(){
	lista_t* habilitada;
	lista_t* deshabilitada;
	int valor;

	if (estado == SOLAPA2 || estado == NINGUNO){
		habilitada = solapa1;
		deshabilitada = solapa2;
		valor = SOLAPA1;
	}else{
		habilitada = solapa2;
		deshabilitada = solapa1;
		valor = SOLAPA2;
	}

	habilitar(habilitada);
	deshabilitar(deshabilitada);
	estado = valor;

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
			ui->setearEstado(ACTIVO);
		}else{
			ui->hacerInvisible();
			ui->setearEstado(INACTIVO);
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
}
