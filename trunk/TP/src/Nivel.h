#ifndef NIVEL_H_
#define NIVEL_H_
#include "Evento.h"
#include "Estado.h"
#include "lista.h"
#include "Cuerpo.h"
#include "VistaCuerpo.h"
#include "Manual.h"
#include "Camara.h"

class Nivel: public Estado {
private:
    static Nivel instancia;
	vector<Cuerpo*>* cuerpos;
	vector<VistaCuerpo*>* vistas;
	Manual* principal;
	Camara* camara;
public:
	Nivel();
	virtual ~Nivel();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar();
	void dibujar(SDL_Surface* display);

private:
	//Para agregar elementos al nivel:
	void agregarCuerpo(Cuerpo*);
	void agregarVista(VistaCuerpo*);
	void indicarManual(Manual*);

public:
    static Nivel* obtenerInstancia();

};

#endif /* NIVEL_H_ */
