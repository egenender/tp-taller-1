#ifndef NIVEL_H_
#define NIVEL_H_
#include "Evento.h"
#include "Estado.h"
#include "lista.h"
#include "Cuerpo.h"
//#include "Vista.h"
#include "Manual.h"

class Nivel: public Estado {
private:
	lista_t* lista_cuerpos;
	//lista_t* lista_vistas;
	Manual* principal;
public:
	Nivel();
	virtual ~Nivel();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar();
	void dibujar(SDL_Surface* display);

	//Para agregar elementos al nivel:
	void agregarCuerpo(Cuerpo*);
	//void agregarVista(Vista*);
	void indicarManual(Manual*);
};

#endif /* NIVEL_H_ */
