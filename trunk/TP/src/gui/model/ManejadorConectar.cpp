#include "ManejadorConectar.h"

ManejadorConectar::ManejadorConectar(CuadroTexto* cuadroIP, CuadroTexto* cuadroPuerto, BarraEstado* labarra, lista_t* aparecer, lista_t* desaparecer) {
	txtIP = cuadroIP;
	txtPuerto = cuadroPuerto;
	barra = labarra;
	manejador = new ManejadorSolapa(aparecer, desaparecer);
}

ManejadorConectar::~ManejadorConectar() {

}

void ManejadorConectar::manejarClic(){
	string puerto = txtPuerto->obtenerMensaje();
	string ip = txtIP->obtenerMensaje();

	/*TODO:
	 bool ok = Cliente::conectar(ip, puerto);
	 if (!ok){
	 	 labarra->setearMensaje("No se ha podido realizar la conexion");
	 	 return;
	 }

	 ¿¿Agregarle las cosas al scroll de Personajes??

	 * */

	manejador->manejarClic();
	barra->setearMensaje("Aun no puedo realizar la conexion");
}
