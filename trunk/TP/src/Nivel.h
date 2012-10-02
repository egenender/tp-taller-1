#ifndef NIVEL_H_
#define NIVEL_H_
#include "controller/Evento.h"
#include "controller/Estado.h"
#include "model/lista.h"
#include "model/Cuerpo.h"
#include "view/VistaCuerpo.h"
#include "model/Manual.h"
#include "view/Camara.h"
#include "controller/Controlador.h"

class Nivel: public Estado {
private:
    static Nivel instancia;
    Controlador* controlador;
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
