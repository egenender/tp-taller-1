#ifndef CONTENEDORMANUALES_H_
#define CONTENEDORMANUALES_H_
#include "Manual.h"
#include "Observable.h"
#include "Actualizable.h"
#include "structures/structServidor.h"

#include <vector>
#include <map>

class Plataforma;
class Escalera;

class ContenedorManuales : public Actualizable {
private:
	map<unsigned int, int>* estados;
	map<unsigned int, bool>* huboCambios;
	map<unsigned int, Manual*>* manuales;
	vector<unsigned int>* IDs;
public:
	ContenedorManuales();
	virtual ~ContenedorManuales();
	void actualizar(float);
	void agregarManual(Manual*, unsigned int);
	void encolarCambios();
	void encolarTodos();
	Area* obtenerArea();
	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
private:
	void actualizarManual(Manual*, int,unsigned int);
	void actualizarEstados(unsigned int,int);
	structServidor_t* crearEnvio(Manual*, unsigned int);
};

#endif /* CONTENEDORMANUALES_H_ */
