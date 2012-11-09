#ifndef VIGAINCLINADA_H_
#define VIGAINCLINADA_H_
#include "../Cuerpo.h"
#include "../Actualizable.h"
#include "../Area.h"
#include "Plataforma.h"
#include <vector>

class Escalera;
class Manual;
class Barril;

using namespace std;

//Por convención, si el angulo está del lado izquierdo, crece positivo (porque crece en Y
//Cuando X crece
#define CRECE_DERECHA -1
#define CRECE_IZQUIERDA 1
#define NINGUNO 0
#define CANT_PLATAFORMAS 50

class VigaInclinada: public Cuerpo {
private:
	float angulo;
	int creceHacia;
	vector<Plataforma*>* plataformas;

public:
	VigaInclinada(const char* , Area*, float angulo);
	virtual ~VigaInclinada();

	void actualizar(float);
	int obtenerEstado();

	void guardarSubPlataformas(vector<Actualizable*>*);

	void chocarCon(Actualizable*);

private:
	void crearPlataformas();
};

#endif /* VIGAINCLINADA_H_ */
