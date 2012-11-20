#ifndef CONTENEDORMANUALES_H_
#define CONTENEDORMANUALES_H_
#include "Personajes/Manual.h"
#include "Observable.h"
#include "Actualizable.h"
#include "structures/structServidor.h"

#include <vector>
#include <map>

class Plataforma;
class Escalera;
class Barril;

class ContenedorManuales : public Actualizable {
private:
	map<unsigned int, int>* estados;
	map<unsigned int, bool>* huboCambios;
	map<unsigned int, Manual*>* manuales;
	map<unsigned int, int>* vidas;
	map<unsigned int, bool>* vidasCambiadas;
	vector<unsigned int>* IDs;
public:
	ContenedorManuales();
	virtual ~ContenedorManuales();
	void actualizar(float);
	void agregarManual(Manual*, unsigned int);
	void encolarCambios();
	void encolarTodos();
	Area* obtenerArea();

	unsigned int obtenerCantidad();

	void chocarCon(Actualizable*);

private:
	void actualizarManual(Manual*, int,unsigned int);
	void actualizarEstados(unsigned int,int);
	structServidor_t* crearEnvio(Manual*, unsigned int);
};

#endif /* CONTENEDORMANUALES_H_ */
