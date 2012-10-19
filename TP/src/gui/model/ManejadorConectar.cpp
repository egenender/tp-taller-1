#include "ManejadorConectar.h"
#include "../../controller/Cliente.h"
#include "../../controller/ManejadorCliente.h"

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

	unsigned short int numPuerto =  atoi(puerto.c_str());
	numPuerto = 5557; //harcode
	ip = "127.0.0.1"; //harcode
	Cliente client =  Cliente(ip.c_str(),numPuerto);
	ManejadorCliente* manejadorCliente= new ManejadorCliente(&client);
	manejadorCliente->recibirRecursos();
	manejadorCliente->iniciarCarga();

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
