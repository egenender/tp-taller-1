
#include "ManejadorJugar.h"

ManejadorJugar::ManejadorJugar(ListaScrolleable* lista, BarraEstado* laBarra) {
	scroll = lista;
	barra = laBarra;
}

ManejadorJugar::~ManejadorJugar() {
	// TODO Auto-generated destructor stub
}

void ManejadorJugar::manejarClic(){
	unsigned int elegido = scroll->indiceSeleccionado();
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

