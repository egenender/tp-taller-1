#ifndef MANEJOSOLAPA_H_
#define MANEJOSOLAPA_H_
#include "ManejadorBoton.h"
#include "../../model/lista.h"
#include "ObjetoGUI.h"

class ManejadorSolapa:public ManejadorBoton {
private:
	lista_t *lista_aparecer;
	lista_t *lista_desaparecer;
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
