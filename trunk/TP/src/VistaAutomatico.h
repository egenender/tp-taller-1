#ifndef VISTAAUTOMATICO_H_
#define VISTAAUTOMATICO_H_
#include "VistaAnimada.h"
#include "Animacion.h"
#include "Automatico.h"
#include "Timer.h"
#include <vector>
#define INMOVIL 1
#define MOVIENDO 2
using namespace std;

class VistaAutomatico:public VistaAnimada {
private:
	int actual;
	bool terminoAhora;
	vector<int>* periodos;
	Timer* timer;
public:
	VistaAutomatico(Automatico*, vector<Animacion*>*d, vector<int>*);
	//VistaAutomatico(Automatico* , vector<Animacion*>*, vector<int>*);
	virtual ~VistaAutomatico();
	void actualizar(Observable* observable);
private:
	void cambiarAnimacion();
};

#endif /* VISTAAUTOMATICO_H_ */
