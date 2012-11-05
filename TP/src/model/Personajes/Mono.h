#ifndef MONO_H_
#define MONO_H_
#include "../Cuerpo.h"
#include "../Timer.h"
#include "../Fabricas/FabricaActualizable.h"

class Escalera;
class Plataforma;
class Manual;
class Barril;

#define TIEMPO_LANZAMIENTO 1000

class Mono : public Cuerpo{
private:
	int estado;
	Timer* timer;
	float media;
	float tiempoEspera;
	FabricaActualizable* fabrica;
public:
	Mono(const char*, Area*, FabricaActualizable*,float);
	virtual ~Mono();

	void actualizar(float);
	int obtenerEstado();

	void chocarCon(Actualizable*);

private:
	float calcularTiempo();
	void tirarBarril();
};

#endif /* MONO_H_ */
