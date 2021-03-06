#include "ManejadorCrear.h"
#include "../../controller/Server.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../../controller/Nivel.h"
#include "../../model/structures/structCliente.h"

ManejadorCrear::ManejadorCrear(CuadroTexto* cuadro, ListaScrolleable* ventana,BarraEstado* barraNueva) {
	txtPuerto = cuadro;
	scrollNivel = ventana;
	barra = barraNueva;
}

ManejadorCrear::~ManejadorCrear() {

}

void ManejadorCrear::manejarClic(){
	barra->setearMensaje("Iniciando Conexion");
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();
	gestor->setEsServidor();
	gestor->inicioCarga();

	string puerto = txtPuerto->obtenerMensaje();
	int numPuerto = atoi(puerto.c_str());

	int nivel = scrollNivel->indiceSeleccionado();

	//numPuerto = 5557; //harcode

	Server* elServer = Server::reiniciarInstancia(numPuerto);

	if (! elServer->estaActivo()){
		barra->setearMensaje("No se pudo crear el servidor");
		return;
	}

	gestor->setNivelElegido(nivel);
	gestor->setPosiblesTiposProtagonistas();
	elServer->escuchar( structCliente_obtener_tamanio() );

	//Por ahora Dejo hecho esto:

	gestor->CargaRestante();

	barra->setearMensaje("Conexion Concretada");

	Nivel::obtenerInstancia()->setEstado(SERVIDOR);
	ManejadorEstados::setearEstadoActual(ESTADO_JUEGO);

}
