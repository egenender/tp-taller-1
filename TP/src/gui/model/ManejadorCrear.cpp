#include "ManejadorCrear.h"

ManejadorCrear::ManejadorCrear(/*CuadroTexto* cuadro, VentanaTexto* ventana,*/BarraEstado* barraNueva) {
	/*txtPuerto = cuadro;
	txtPersonaje = ventana;
	*/
	barra = barraNueva;
}

ManejadorCrear::~ManejadorCrear() {
	//No debe destruir las cosas.
	//De eso se encargan al destruir las solapas ya
}

void ManejadorCrear::manejarClic(){
	/*TODO:
	string puerto = txtPuerto->obtenerTexto();
	bool ok = Server::ValidarPuerto(puerto);
	if (!ok){
		barra->setearMensaje("Numero de Puerto indebido");
		return;
	}

	string NombrePersonaje = txtPersonaje->obtenerActual();
	barra->setearMensaje("Cargando");
	//TODO: y ahora tendria que darle el nombre al gestor de configuraciones
	//Deshabilitar todas las cosas?
	 */
}
