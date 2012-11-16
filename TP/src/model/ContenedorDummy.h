#ifndef CONTENEDORDUMMY_H_
#define CONTENEDORDUMMY_H_

#include "lista.h" //ver si lo hacemos con vector
#include "Dummy.h"
#include "Actualizable.h"
#include "structures/structServidor.h"
#include "../controller/Cliente.h"
#include "../gui/model/BarraEstado.h"
class Manual;
class Plataforma;
class Escalera;
class Barril;
#define MAX_ACTUALIZACION 5

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
	Area* obtenerArea();

	void chocarCon(Actualizable*);
private:
	void interpretarStruct(structServidor_t*);
	Dummy* buscarID(unsigned int id);
	void borrarID(unsigned int id);
	Dummy* crearDummyNuevo(unsigned int, unsigned int);
	string intToString(unsigned int);
};

#endif /* CONTENEDORDUMMY_H_ */
