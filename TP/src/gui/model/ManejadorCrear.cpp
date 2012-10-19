#include "ManejadorCrear.h"
#include "../../controller/Server.h"
#include "../../controller/GestorConfiguraciones.h"

ManejadorCrear::ManejadorCrear(CuadroTexto* cuadro, ListaScrolleable* ventana,BarraEstado* barraNueva) {
	txtPuerto = cuadro;
	scrollNivel = ventana;
	barra = barraNueva;
}

ManejadorCrear::~ManejadorCrear() {

}

void ManejadorCrear::manejarClic(){
	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	gestor->inicioCarga();

	string puerto = txtPuerto->obtenerMensaje();

	int nivel = scrollNivel->indiceSeleccionado();

	int numPuerto = atoi(puerto.c_str());
	numPuerto = 5557;
	Server* elServer = Server::obtenerInstancia(numPuerto);

	if (! elServer->estaActivo()){
		barra->setearMensaje("No se pudo crear el servidor");
		return;
	}

	elServer->escuchar(sizeof(int));

	//Por ahora Dejo hecho esto:

	gestor->setNivelElegido(nivel);
	gestor->CargaRestante();

	barra->setearMensaje("Realiza Conexion");
	//scrollNivel->agregarElemento(puerto);

}
