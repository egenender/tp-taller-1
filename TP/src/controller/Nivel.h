#ifndef NIVEL_H_
#define NIVEL_H_
#include "Evento.h"
#include "Estado.h"
#include "ManejadorEstados.h"
#include "../model/lista.h"
#include "../view/VistaCuerpo.h"
#include "../model/Manual.h"
#include "../view/Camara.h"
#include "Controlador.h"
#include "../model/Actualizable.h"

class Nivel: public Estado {
private:
    static Nivel instancia;
    Controlador* controlador;
	vector<Actualizable*>* actualizables;
	vector<VistaCuerpo*>* vistas;
	Manual* principal;
	Camara* camara;
public:
	Nivel();
	virtual ~Nivel();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar(float delta);
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
