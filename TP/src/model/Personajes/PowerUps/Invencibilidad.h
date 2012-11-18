#ifndef INVENCIBILIDAD_H_
#define INVENCIBILIDAD_H_

#include "PowerUp.h"
#include "../../Timer.h"
#define TIEMPO_VIDA_INVENCIBILIDAD 10

class Invencibilidad: public PowerUp {
private:
	Timer* timer;
public:
	Invencibilidad(const char*, Area*, int);
	virtual ~Invencibilidad();
	void chocarConManual(Manual*);
protected:
	void actualizarMovimiento();
	void saltar();
	void validarPiso();
};

#endif /* INVENCIBILIDAD_H_ */
