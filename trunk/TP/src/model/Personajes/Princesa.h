#ifndef PRINCESA_H_
#define PRINCESA_H_
#include "../Cuerpo.h"
#include "../Actualizable.h"
#include "../Timer.h"

#define TIEMPO_GRITO 3
#define TIEMPO_ESPERA_STD 10

class Princesa : public Cuerpo{
private:
	int tiempo_espera;
	int tiempo_actual;
	int estado;
	Timer* timer;
public:
	Princesa(const char*, Area*, int);
	virtual ~Princesa();

	void actualizar(float);
	int obtenerEstado();
	unsigned int obtenerTipo();

	void chocarCon(Actualizable*);
private:
	void cambiar_estado();
};

#endif /* PRINCESA_H_ */
