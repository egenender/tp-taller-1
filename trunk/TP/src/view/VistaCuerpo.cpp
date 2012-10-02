#include "VistaCuerpo.h"

VistaCuerpo::VistaCuerpo() {
	posicionDibujar = NULL;
};

VistaCuerpo::~VistaCuerpo() {

	// TODO: HMMM... no la borraria cuerpo?

	if (posicionDibujar != NULL) {
		delete(posicionDibujar);
		posicionDibujar = NULL;
	}
}
