#ifndef ESTADOINTRO_H
#define ESTADOINTRO_H

#include "Estado.h"

#include "../gui/view/VistaBoton.h"
#include "../gui/model/Boton.h"
#include "../gui/view/VistaBarraEstado.h"
#include "../gui/model/BarraEstado.h"
#include "../gui/view/VistaCuadroTexto.h"
#include "../gui/model/CuadroTexto.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "../gui/model/ManejadorSolapa.h"
#include "../model/lista.h"

class EstadoIntroduccion : public Estado {
    private:
        static EstadoIntroduccion instancia;

        Boton* botonIniciar;
    	VistaBoton* vistaBotonIniciar;

    	Boton* botonSacaCuadro;
    	VistaBoton* vistaBotonSacaCuadro;

    	BarraEstado* barra;
    	VistaBarraEstado* vistaBarra;

    	CuadroTexto* cuadroTexto;
    	VistaCuadroTexto* vistaCuadroTexto;

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
