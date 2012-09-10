#include "EstrategiaMovimiento.h"
/*Revisar como hacer el tema de los constructores.. quien contiene a quien, etc..*/

EstrategiaMovimiento::EstrategiaMovimiento() {
	algo = 0;
}

void EstrategiaMovimiento::actuar() {
	algo = 1;
}
