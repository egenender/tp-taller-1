#ifndef ESTADOINTRO_H
#define ESTADOINTRO_H

#include "Estado.h"

#include "../gui/view/VistaBoton.h"
#include "../gui/model/Boton.h"
#include "../gui/view/VistaBarraEstado.h"
#include "../gui/model/BarraEstado.h"

class EstadoIntroduccion : public Estado {
    private:
        static EstadoIntroduccion instancia;

        Boton* botonIniciar;
    	VistaBoton* vistaBotonIniciar;

    	BarraEstado* barra;
    	VistaBarraEstado* vistaBarra;

    private:
        EstadoIntroduccion();

    public:
        void manejarEvento(SDL_Event* evento);
        void iniciar();
        void terminar();
        void actualizar(float delta);
        void dibujar(SDL_Surface* display);

    public:
        static EstadoIntroduccion* obtenerInstancia();
};

#endif
