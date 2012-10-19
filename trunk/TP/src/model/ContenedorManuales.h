#ifndef CONTENEDORMANUALES_H_
#define CONTENEDORMANUALES_H_
#include "Manual.h"
#include <vector>
#include "Observable.h"
#include "structures/structServidor.h"

class ContenedorManuales : public Actualizable {
private:
	vector<int>* estados;
	vector<Manual*>* manuales;
	vector<bool>* huboCambios;
public:
	ContenedorManuales();
	virtual ~ContenedorManuales();
	void actualizar(float);
	void agregarManual(Manual*);
	void encolarCambios();
private:
	void actualizarManual(Manual*, int,unsigned int);
	void actualizarEstados(unsigned int,int);
	structServidor_t* crearEnvio(Manual*, unsigned int);
};

#endif /* CONTENEDORMANUALES_H_ */
