#ifndef CONTENEDORCUERPOS_H_
#define CONTENEDORCUERPOS_H_
#include "../common/Observador.h"
#include "Observable.h"
#include "Cuerpo.h"
#include <vector>
#include <map>

using namespace std;

class ContenedorCuerpos : public Observador{
	map<unsigned int, bool>* huboCambios;
	map<unsigned int, Cuerpo*>* cuerpos;
	vector<unsigned int>* IDs;
public:
	ContenedorCuerpos();
	virtual ~ContenedorCuerpos();
	void actualizar(Observable*);
	void encolarCambios();
	void encolarTodos();
};

#endif
