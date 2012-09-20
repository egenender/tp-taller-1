#include "VistaCuerpo.h"

VistaCuerpo::VistaCuerpo() {
	posicionDibujar = NULL;
};

VistaCuerpo::~VistaCuerpo() {
	if (posicionDibujar != NULL) {
		delete(posicionDibujar);
		posicionDibujar = NULL;
	}
}
