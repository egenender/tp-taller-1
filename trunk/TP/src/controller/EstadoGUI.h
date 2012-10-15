#ifndef ESTADOGUI_H_
#define ESTADOGUI_H_

#include "ManejadorEstados.h"
#include "../gui/view/VistaBoton.h"
#include "../gui/model/Boton.h"
#include "../gui/view/VistaBarraEstado.h"
#include "../gui/view/VistaLabel.h"
#include "../gui/model/Label.h"
#include "../gui/model/BarraEstado.h"
#include "../gui/view/VistaCuadroTexto.h"
#include "../gui/model/CuadroTexto.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "../gui/model/ManejadorSolapa.h"
#include "../gui/model/ManejadorScroll.h"
#include "../model/lista.h"
#include "../gui/model/ListaScrolleable.h"
#include "../gui/view/VistaLista.h"
#include "Evento.h"

class EstadoGUI : public Estado{
private:
	static EstadoGUI instancia;

	lista_t* solapaServidor;
	lista_t* solapaCliente1;
	lista_t* solapaCliente2;
	Boton *btncrear,*btnsolapacliente1, *btnsolapacliente2,*btnsolapaservidor,*btnconectar,*btnjugar;
	CuadroTexto *txtPuertoServidor, *txtPuertoCliente, *txtIP;
	BarraEstado* barra;
	//TODO: faltan las imagenes y las listas
	Label *lblPuertoServidor, *lblIP, *lblPuertoCliente, *lblnombrePersonaje, *lblvelocidad, *lblsalto;

	ListaScrolleable* scroll;
	Boton *btnscrollarriba, *btnscrollabajo;
	VistaBoton *vistaarriba, *vistaabajo;
	VistaLista *vistaScroll;

	VistaBoton *vistaBtncrear, *vistaBtnsolapacliente1, *vistaBtnsolapacliente2, *vistaBtnsolapaservidor, *vistaBtnconectar, *vistaBtnjugar;
	VistaCuadroTexto *vistaTxtPuertoServidor, *vistaTxtPuertoCliente, *vistaTxtIP;
	VistaBarraEstado *vistaBarra;
	VistaLabel *vistalblpuertoservidor, *vistalblpuertocliente, *vistalblIP, *vistalblnombre, *vistalblvelocidad, *vistalblsalto;

private:
        EstadoGUI();
        void crearBtns();
        void crearTxts();
        void crearBarra();
        void crearSolapaServidor();
        void crearSolapaCliente();
        void crearVistas();
        void crearLabels();
        void crearScroll();
public:
        virtual ~EstadoGUI();
        void manejarEvento(SDL_Event* evento);
        void iniciar();
        void terminar();
        void actualizar(float delta);
        void dibujar(SDL_Surface* display);

public:
        static EstadoGUI* obtenerInstancia();
};

#endif /* ESTADOGUI_H_ */
