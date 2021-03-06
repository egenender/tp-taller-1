#ifndef NIVEL_H_
#define NIVEL_H_
#include "Evento.h"
#include "Estado.h"
#include "ManejadorEstados.h"
#include "../model/lista.h"
#include "../view/VistaCuerpo.h"
#include "../model/Personajes/Manual.h"
#include "../view/Camara.h"
#include "ControladorCliente.h"
#include "Controlador.h"
#include "ControladorSinglePlayer.h"
#include "../model/Actualizable.h"
#include "../view/VistaMusical.h"

#define CLIENTE 0
#define SERVIDOR 1
#define SINGLE 2

class Nivel: public Estado {
private:
    static Nivel instancia;
    Controlador* controlador;
	vector<Actualizable*>* actualizables;
	vector<VistaCuerpo*>* vistas;
	Manual* principal;
	Camara* camara;
	VistaMusical* musica;
	int estado;
	bool parar;
	bool puedoJugar;
	Superficie* fondoServidor;
public:
	Nivel();
	virtual ~Nivel();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar(float delta);
	void dibujar(SDL_Surface* display);
	void setEstado(int);
	void morir();

	void sePuedeJugar();

private:
	//Para agregar elementos al nivel:
	void agregarCuerpo(Cuerpo*);
	void agregarVista(VistaCuerpo*);
	void indicarManual(Manual*);
	void quitarMuertos();

public:
    static Nivel* obtenerInstancia();

};

#endif /* NIVEL_H_ */
