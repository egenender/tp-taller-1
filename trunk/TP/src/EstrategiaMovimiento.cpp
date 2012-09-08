#include "EstrategiaMovimiento.h"
/*Revisar como hacer el tema de los constructores.. quien contiene a quien, etc..*/

EstrategiaMovimiento::EstrategiaMovimiento(Personaje* pers) {
	personaje = pers;
}

EstrategiaMovimiento::EstrategiaMovimiento() {

}

void EstrategiaMovimiento::asignarPersonaje(Personaje* pers){
	personaje = pers;
}
