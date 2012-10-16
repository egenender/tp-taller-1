#include "ManejadorCrear.h"

ManejadorCrear::ManejadorCrear(CuadroTexto* cuadro, ListaScrolleable* ventana,BarraEstado* barraNueva) {
	txtPuerto = cuadro;
	scrollNivel = ventana;
	barra = barraNueva;
}

ManejadorCrear::~ManejadorCrear() {

}

void ManejadorCrear::manejarClic(){
	string puerto = txtPuerto->obtenerMensaje();
	string nivel = scrollNivel->obtenerSeleccionado();

	/*TODO:
	 bool ok = Server::Crear(nivel, puerto);
	 if (!ok){
	 	 barra->setearMensaje("No se pudo crear el servidor");
	 	 return;
	 }
	 string puntos = "";
	 while (Server::estaCargando()){
	 	 barra->seterMensaje("Cargando"+puntos);
	 	 puntos += ".";
	 	 if (strcmp(puntos.c_str, "....")
	 	 	 puntos = "";
	 }
	 Paso al EstadoJuego??
	 */

	//Por ahora Dejo hecho esto:

	barra->setearMensaje("Todavia No puedo conectar");
	//scrollNivel->agregarElemento(puerto);
}
