#ifndef CONTENEDORDUMMY_H_
#define CONTENEDORDUMMY_H_

#include "lista.h" //ver si lo hacemos con vector
#include "Dummy.h"
#include "Actualizable.h"
#include "structures/structServidor.h"
#include "../controller/Cliente.h"
#include "../gui/model/BarraEstado.h"

class ContenedorDummy : public Actualizable{
private:
	lista_t* lista_dummies;
	Cliente* cliente;
	BarraEstado* barra;
public:
	ContenedorDummy();
	virtual ~ContenedorDummy();
	void agregarDummy(Dummy*);
	void actualizar(float delta);
private:
	void interpretarStruct(structServidor_t*);
	Dummy* buscarID(unsigned int id);
	Dummy* crearDummyNuevo(unsigned int);
	string intToString(unsigned int);
};

#endif /* CONTENEDORDUMMY_H_ */
