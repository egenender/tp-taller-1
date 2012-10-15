#ifndef VISTAMUESTRA_H_
#define VISTAMUESTRA_H_
#include "../../common/Observador.h"
#include "../model/Muestra.h"
#include "../../view/VistaProtagonista.h"
#include "../../model/Dummy.h"

class VistaMuestra : public Observador{
private:
	VistaProtagonista* vistaActual;
	bool visible;
	Dummy* tonto;
public:
	VistaMuestra();
	virtual ~VistaMuestra();
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display);

};

#endif /* VISTAMUESTRA_H_ */
