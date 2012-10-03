#ifndef ESTADOINTRO2_H
#define ESTADOINTRO2_H

#include "Estado.h"
#include "../view/Camara.h"
#include "../view/Animacion.h"

class EstadoIntroduccion2 : public Estado {
    private:
        static EstadoIntroduccion2 instancia;
        Superficie* fondo;
        Animacion* yoshiNormal;
        Camara* camara;
        float x,y, dx,dy;
        float velocidadX, velocidadY;

    private:
        EstadoIntroduccion2();

    public:
        void manejarEvento(SDL_Event* evento);
        void iniciar();
        void terminar();
        void actualizar(float delta);
        void dibujar(SDL_Surface* display);

    public:
        static EstadoIntroduccion2* obtenerInstancia();
};

#endif
