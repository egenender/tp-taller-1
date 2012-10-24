#include "ManejadorDesconectar.h"
#include "../../controller/Cliente.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../../controller/ManejadorEstados.h"


ManejadorDesconectar::ManejadorDesconectar() {


}

ManejadorDesconectar::~ManejadorDesconectar() {

}

void ManejadorDesconectar::manejarClic(){
	Log::getInstance()->writeToLogFile(Log::INFORMATIVO, "Se volvera al Estado de seleccion.");
	//manejador->manejarClic();
	ManejadorEstados::setearEstadoActual(ESTADO_GUI);
	Cliente *cliente = Cliente::obtenerInstancia("",0);
	int meVoy= -1;
	cliente->escribir_al_server(&meVoy,sizeof(int));
	cliente->detener();
	GestorConfiguraciones* gestor =GestorConfiguraciones::getInstance();
	gestor->acabarGestor();
}
