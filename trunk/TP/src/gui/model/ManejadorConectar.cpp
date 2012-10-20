#include "ManejadorConectar.h"
#include "../../controller/Cliente.h"
#include "../../controller/ManejadorCliente.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../../view/TipoProtagonista.h"
#include "../../controller/Nivel.h"

ManejadorConectar::ManejadorConectar(CuadroTexto* cuadroIP, CuadroTexto* cuadroPuerto, BarraEstado* labarra, lista_t* aparecer, lista_t* desaparecer, ListaScrolleable* lista, Muestra* animaciones) {
	txtIP = cuadroIP;
	txtPuerto = cuadroPuerto;
	barra = labarra;
	manejador = new ManejadorSolapa(aparecer, desaparecer);
	scroll = lista;
	muestra = animaciones;
}

ManejadorConectar::~ManejadorConectar() {

}

void ManejadorConectar::manejarClic(){
	barra->setearMensaje("Iniciando Conexion...");

	string puerto = txtPuerto->obtenerMensaje();
	string ip = txtIP->obtenerMensaje();

	unsigned short int numPuerto =  atoi(puerto.c_str());
	numPuerto = 5557; //harcode
	//ip = "127.0.0.1"; //harcode

	Cliente* client= Cliente::obtenerInstancia(ip.c_str(),numPuerto);

	ManejadorCliente* manejadorCliente= ManejadorCliente::obtenerInstancia(client);
	manejadorCliente->recibirRecursos();
	manejadorCliente->iniciarCarga();

	GestorConfiguraciones* gestor =GestorConfiguraciones::getInstance();
	gestor->CargaRestante();

//	bool ok = Cliente::conectar(ip, puerto);
//	if (!ok){
//	 	 labarra->setearMensaje("No se ha podido realizar la conexion");
//	 	 return;
//	 }
//
//	 Agregarle los nombres de los personajes al Scroll.
//	 Agregarle las animaciones a la muestra.


	vector<TipoProtagonista*>* personajes=gestor->ObtenerPosiblesTiposProtagonistas();
	for (unsigned int i = 0; i < personajes->size(); i++){
		if (personajes->at(i)->disponible){
			string texto = personajes->at(i)->nombre;
			scroll->agregarElemento(texto);
			muestra->agregarVista(personajes->at(i));
		}
	}

	manejador->manejarClic();
	barra->setearMensaje("Conectado al Servidor");

	Nivel::obtenerInstancia()->setEstado(CLIENTE);
}
