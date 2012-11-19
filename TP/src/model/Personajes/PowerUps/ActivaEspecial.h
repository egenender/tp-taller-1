#ifndef ACTIVAESPECIAL_H_
#define ACTIVAESPECIAL_H_

#include "PowerUp.h"
#include "../../Timer.h"
#define TIEMPO_VIDA_ESPECIAL 15

class ActivaEspecial: public PowerUp {
private:
	Timer* timer;
public:
	ActivaEspecial(const char*, Area*, int);
	virtual ~ActivaEspecial();
	void chocarConManual(Manual*);
	unsigned int obtenerTipo();
protected:
	void actualizarMovimiento();
};

#endif /* ACTIVAESPECIAL_H_ */
