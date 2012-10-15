#ifndef LISTASCROLLEABLE_H_
#define LISTASCROLLEABLE_H_
#include "ObjetoGUI.h"
#include <vector>
#include <string>
using namespace std;

class ListaScrolleable : public ObjetoGUI{
	vector<string>* vectorcito;
	unsigned int seleccionado;
public:
	ListaScrolleable(int, int , int , int);
	virtual ~ListaScrolleable();
	void moverHaciaArriba();
	void moverHaciaAbajo();
	void agregarElemento(string);
	void eliminarElemento(unsigned int);
	string obtenerSeleccionado();
	unsigned int indiceSeleccionado();
	string obtenerElemento(unsigned int);
	unsigned int cantidad();
};

#endif /* LISTASCROLLEABLE_H_ */
