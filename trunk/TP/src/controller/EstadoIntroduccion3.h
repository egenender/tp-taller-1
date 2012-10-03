#ifndef ESTADOINTRO3_H
#define ESTADOINTRO3_H

#include "Estado.h"
#include "../view/Camara.h"
#include "../view/Animacion.h"

class EstadoIntroduccion3 : public Estado {
    private:
        static EstadoIntroduccion3 instancia;
        Superficie* fondo;
        Animacion* yoshiNormal;
        Camara* camara;
        float x,y, dx,dy;
        float velocidadX, velocidadY;

    private:
        EstadoIntroduccion3();

    public:
        void manejarEvento(SDL_Event* evento);
        void iniciar();
        void terminar();
        void actualizar(float delta);
        void dibujar(SDL_Surface* display);

    public:
        static EstadoIntroduccion3* obtenerInstancia();
};

#endif
