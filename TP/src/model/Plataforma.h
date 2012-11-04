#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_
#include "Cuerpo.h"
#include "Area.h"
#include "Actualizable.h"

class Manual;
class Escalera;

class Plataforma : public Cuerpo{
private:
	bool vigaDer, vigaIzq;
	float angulo;
	int direccion;
public:
	Plataforma(const char* , Area*);
	virtual ~Plataforma();
	int obtenerEstado();	 //de observable
	void actualizar(float delta); 		//de cuerpo

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
	bool esVigaPorDerecha();
	bool esVigaPorIzquierda();

	//Significa que tiene a un cacho de viga a la derecha!
	void setearComoVigaPorDerecha();
	//Idem con izquierda
	void setearComoVigaPorIzquierda();
	void setearAngulo(float);
	void setearDireccion(int);
	bool caeADerecha();
	bool caeAIzquierda();
};

#endif /* PLATAFORMA_H_ */
