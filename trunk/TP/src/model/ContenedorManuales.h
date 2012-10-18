
#ifndef CONTENEDORMANUALES_H_
#define CONTENEDORMANUALES_H_
#include "Manual.h"
#include <vector>
#include "structures/structServidor.h"
#include "Observable.h"

class ContenedorManuales : public Actualizable {
private:
	vector<int>* vectorEstados;
	vector<Manual*>* vectorManuales;
	vector<bool>* vectorHuboCambios;
public:
	ContenedorManuales(vector<int>*);
	virtual ~ContenedorManuales();
	void actualizar(float);
	void agregarManual(Manual*);
private:
	void actualizarManual(Manual*, int,unsigned int);
};

#endif /* CONTENEDORMANUALES_H_ */
