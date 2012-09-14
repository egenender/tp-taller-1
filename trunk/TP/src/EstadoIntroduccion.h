#ifndef ESTADOINTRO_H
#define ESTADOINTRO_H

#include "Estado.h"
#include "Animacion.h"

class EstadoIntroduccion : public Estado {
    private:
        static EstadoIntroduccion instancia;
        Superficie* fondo;
        Animacion* yoshiNormal;
        Animacion* yoshiGigante;
        Superficie* original;
        Superficie* espejada;
        int x,y,dx,dy;

    private:
        EstadoIntroduccion();

    public:
        void iniciar();
        void terminar();
        void actualizar();
        void dibujar(SDL_Surface* display);

    public:
        static EstadoIntroduccion* obtenerInstancia();
};

#endif
