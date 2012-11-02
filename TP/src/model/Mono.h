#ifndef MONO_H_
#define MONO_H_
#include "Cuerpo.h"
#include "Timer.h"

class Escalera;
class Plataforma;
class Manual;

#define TIEMPO_LANZAMIENTO 1000

class Mono : public Cuerpo{
private:
	int estado;
	Timer* timer;
	float media;
	float tiempoEspera;
public:
	Mono(const char*, Area*, float);
	virtual ~Mono();

	void actualizar(float);
	int obtenerEstado();

	void chocarCon(Actualizable*);
	void chocarConEscalera(Escalera*);
	void chocarConPlataforma(Plataforma*);
	void chocarConManual(Manual*);

private:
	float calcularTiempo();
	void tirarBarril();
};

#endif /* MONO_H_ */
