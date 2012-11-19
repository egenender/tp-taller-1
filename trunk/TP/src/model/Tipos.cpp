#include "Tipos.h"

std::string decodificarTipo(unsigned int tipo){
	std::string aux = "";

	//Los casos 0 y 3 deben ser tratados desde afuera
	switch(tipo){
	case TIPO_MANUAL: aux = " "; break;
	case TIPO_HONGO: aux = "hongo"; break;
	case TIPO_TORTUGA: aux = "tortuga"; break;
	case TIPO_BOLA_FUEGO: aux = " "; break;
	case TIPO_PLATAFORMA_MOVIL: aux = "plataformaMovil"; break;
	case TIPO_CAMA_ELASTICA: aux = "camaElastica"; break;
	case TIPO_BARRIL: aux = "barril"; break;
	case TIPO_CAJA: aux = "cajaRandom"; break;
	case TIPO_MONO: aux = "mono"; break;
	case TIPO_PRINCESA: aux = "princesa"; break;
	case TIPO_PU_INVENCIBILIDAD: aux = "invencibilidad"; break;
	case TIPO_PU_PIEDRA: aux = "piedraEvolucion"; break;
	case TIPO_PU_VIDA: aux = "vidaExtra"; break;
	case TIPO_PU_BOLA: aux = "activaEspecial"; break;
	}

	return aux;
}

