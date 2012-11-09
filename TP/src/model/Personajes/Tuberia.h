#ifndef TUBERIA_H_
#define TUBERIA_H_

#include "../Fabricas/FabricaActualizable.h"
#include "../Timer.h"
#include "Plataforma.h"
#include "../Posicion.h"
#include <vector>

#define MEDIA_TUBERIA_STD 15
#define ABAJO_TB 2
#define ARRIBA_TB -2
#define DERECHA_TB 1
#define IZQUIERDA_TB -1

class Tuberia : public Plataforma{
private:
	Timer* timer;
	float media;
	float tiempo_espera;
	std::vector<int>* probabilidades;
	std::vector<FabricaActualizable*>* fabricas;
	int direccion;
	Posicion* posCreacion;
public:
	Tuberia(const char*, Area*, float, int, std::vector<int>* ,std::vector<FabricaActualizable*>* );
	virtual ~Tuberia();

	void actualizar(float delta);

private:
	float calcularTiempo();
	int calcularFabrica();
	void crearPosicion();
	float tirarRandom();
};

#endif /* TUBERIA_H_ */
