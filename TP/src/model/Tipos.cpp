#include "Tipos.h"

std::string decodificarTipo(unsigned int tipo){
	std::string aux = "";

	//Los casos 0 y 3 deben ser tratados desde afuera
	switch(tipo){
	case 0: aux = " "; break;
	case 1: aux = "hongo"; break;
	case 2: aux = "tortuga"; break;
	case 3: aux = " "; break;
	case 4: aux = "plataformaMovil"; break;
	case 5: aux = "cama"; break;
	case 6: aux = "barril"; break;
	case 7: aux = "caja"; break;
	case 8: aux = "mono"; break;
	case 9: aux = "princesa"; break;
	}

	return aux;
}

