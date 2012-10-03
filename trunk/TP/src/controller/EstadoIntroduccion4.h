#ifndef ESTADOINTRO4_H
#define ESTADOINTRO4_H

#include "Estado.h"
#include "../view/Camara.h"
#include "../view/Animacion.h"

class EstadoIntroduccion4 : public Estado {
    private:
        static EstadoIntroduccion4 instancia;
        Superficie* fondo;
        Animacion* yoshiNormal;
        Camara* camara;
        float x,y, dx,dy;
        float velocidadX, velocidadY;

    private:
        EstadoIntroduccion4();

    public:
        void manejarEvento(SDL_Event* evento);
        void iniciar();
        void terminar();
        void actualizar(float delta);
        void dibujar(SDL_Surface* display);

    public:
        static EstadoIntroduccion4* obtenerInstancia();
};

#endif
