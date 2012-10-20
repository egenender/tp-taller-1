#ifndef CONTENEDORMANUALES_H_
#define CONTENEDORMANUALES_H_
#include "Manual.h"
#include "Observable.h"
#include "structures/structServidor.h"

#include <vector>
#include <map>

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
private:
	void actualizarManual(Manual*, int,unsigned int);
	void actualizarEstados(unsigned int,int);
	structServidor_t* crearEnvio(Manual*, unsigned int);
};

#endif /* CONTENEDORMANUALES_H_ */
