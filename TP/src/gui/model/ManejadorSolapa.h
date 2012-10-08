#ifndef MANEJOSOLAPA_H_
#define MANEJOSOLAPA_H_
#include "ManejadorBoton.h"
#include "../../model/lista.h"
#include "ObjetoGUI.h"

#define NINGUNO 0
#define SOLAPA1 1
#define SOLAPA2 2

class ManejadorSolapa:public ManejadorBoton {
private:
	lista_t *solapa1;
	lista_t *solapa2;
	int estado;
public:
	ManejadorSolapa(lista_t*, lista_t*);
	virtual ~ManejadorSolapa();
	void manejarClic();
private:
	void habilitacion(lista_t*, bool);
	void habilitar(lista_t*);
	void deshabilitar(lista_t*);
};

#endif /* MANEJOSOLAPA_H_ */
