
#include "ManejadorJugar.h"
#include "../../controller/ManejadorCliente.h"
#include "../../controller/ManejadorEstados.h"
#include "../../controller/GestorConfiguraciones.h"
#include "../../model/structures/structCliente.h"
#include "../../model/structures/structServidor.h"

ManejadorJugar::ManejadorJugar(ListaScrolleable* lista, BarraEstado* laBarra) {
	scroll = lista;
	barra = laBarra;
}

ManejadorJugar::~ManejadorJugar() {
	// TODO Auto-generated destructor stub
}

void ManejadorJugar::manejarClic(){
	string elegido = scroll->obtenerSeleccionado();
	if (strcmp(elegido.c_str()," ")==0 ){
		barra->setearMensaje("No hay personajes para elegir, elija otro servidor");
		return;
	}
	ManejadorCliente *mCliente = ManejadorCliente::obtenerInstancia(NULL);

	mCliente->seleccionarProt(elegido);

	if (! mCliente->personajeAceptado() ){
		barra->setearMensaje("No se pudo elegir al personaje, ya fue elegido por otro cliente");
		//scroll->eliminarElemento(scroll->indiceSeleccionado());
		return ;
	}

	GestorConfiguraciones *gestor = GestorConfiguraciones::getInstance();
	gestor->setProtagonista(elegido);

	Cliente* cliente = Cliente::obtenerInstancia("Hola Diego",0);
	cliente->escritura(structCliente_obtener_tamanio());
	cliente->escuchar(structServidor_obtener_tamanio());
	ManejadorEstados::setearEstadoActual(ESTADO_JUEGO);


	/*Cliente* cliente = Cliente::ObtenerInstancia();

	cliente->indicarPersonaje(elegido);
	if (!cliente->PersonajeAceptado()){
		barra->setearMensaje("No se pudo elegir al personaje, ya fue elegido por otro cliente");
		//scroll->eliminarElemento(elegido); ->vemos si hay que hacer esto o no.
		return;
	}
	decirle al servidor que quiero ese personaje...
	terminar de cargar las cosas del nivel (personajes restantes, etc...)
	cambiar de estado (ya no lo debe hacer el EstadoGUI)

	*/
}

