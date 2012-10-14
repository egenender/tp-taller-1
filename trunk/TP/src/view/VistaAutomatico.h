#ifndef VISTAAUTOMATICO_H_
#define VISTAAUTOMATICO_H_
#include "VistaAnimada.h"
#include "Animacion.h"
#include "../model/Observable.h"
#include "../model/Timer.h"
#include <vector>
#define INMOVIL 1
#define MOVIENDO 2
using namespace std;

class VistaAutomatico:public VistaAnimada {
private:
	unsigned int actual;
	bool terminoAhora;
	vector<int>* periodos;
	Timer* timer;

	Animacion* animacionQuieto;
	bool quieto;
public:
	//VistaAutomatico(Observable*, vector<Animacion*>*d, vector<int>*);
	VistaAutomatico(Observable*, Animacion*, vector<Animacion*>*, vector<int>*);
	virtual ~VistaAutomatico();
	void actualizar(Observable* observable);
private:
	void cambiarAnimacion();
};

#endif /* VISTAAUTOMATICO_H_ */
