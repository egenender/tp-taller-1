#ifndef OBSERVADOR_H_
#define OBSERVADOR_H_

class Observable;

class Observador {
public:
	Observador();
	virtual void actualizar(Observable* observable) = 0;
	virtual ~Observador();
};

#endif
