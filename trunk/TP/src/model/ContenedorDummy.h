#ifndef CONTENEDORDUMMY_H_
#define CONTENEDORDUMMY_H_
#include "cola.h"
#include "lista.h" //ver si lo hacemos con vector
#include "Dummy.h"
#include "Actualizable.h"
#include "structures/structServidor.h"

class ContenedorDummy : public Actualizable{
private:
	cola_t* cola_entrada;
	lista_t* lista_dummies;

public:
	ContenedorDummy(cola_t*);
	virtual ~ContenedorDummy();
	void agregarDummy(Dummy*);
	void actualizar(float delta);
private:
	void interpretarStruct(structServidor_t*);
	Dummy* buscarID(unsigned int id);
};

#endif /* CONTENEDORDUMMY_H_ */
