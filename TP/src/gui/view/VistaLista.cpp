
#include "VistaLista.h"
#include "../../common/Fuente.h"

VistaLista::VistaLista(unsigned int m) {
	mostrables = m;
	x = y = alto = ancho = 0;
	cuadro = new Superficie("src/gui/resources/lista.bmp");
	mensajeAMostrar = new vector<SDL_Surface*>();

	seleccionado = new Superficie("src/gui/resources/listaSelec.bmp");
	seleccionadoActual = 0;
	visible = false;
	primeraVez = true;

	seleccionadoAnterior = 0;
	sinCarga = true;
	topeInferior = 0;
	topeSuperior = 0;
}

VistaLista::~VistaLista() {
	if (cuadro) {
		delete (cuadro);
		cuadro = NULL;
	}

	if (mensajeAMostrar) {
		unsigned int largo = mensajeAMostrar->size();
		for (unsigned int i = 0; i < largo; i++){
			SDL_Surface* tex = mensajeAMostrar->at(mensajeAMostrar->size()-1);
			mensajeAMostrar->pop_back();
			delete (tex);
			tex = NULL;
		}
		mensajeAMostrar->clear();
		delete (mensajeAMostrar);
		mensajeAMostrar = NULL;
	}
	sinCarga = true;
}

void VistaLista::actualizar(Observable* observable){
	ListaScrolleable* lista = (ListaScrolleable*) observable;
	x = lista->obtenerX();
	y = lista->obtenerY();
	ancho = lista->obtenerAncho();
	alto = lista->obtenerAlto();

	cuadro->escala(ancho,alto);
	seleccionado->escala(ancho, alto/mostrables);
	visible = lista->esVisible();
	if (lista->cantidad() == 0){
		sinCarga = true;
		return;
	}
	sinCarga = false;
	llenarVector(lista);
}

bool VistaLista::dibujar(SDL_Surface* display){
	if (!display) return false;
	if (!visible) return true;

	bool dibujeCuadro = cuadro->dibujar(display, x, y);
	unsigned int dsf;
	dsf = seleccionadoActual - topeSuperior;
	dibujeCuadro&= seleccionado->dibujar(display,x,(y + dsf * alto / mostrables));

	if (sinCarga){
		return false;
	}
	if (!mensajeAMostrar || mensajeAMostrar->size() == 0){
		return false;
	}

	SDL_Rect destino;
	for (unsigned int i = 0; i < mensajeAMostrar->size(); i++){
		unsigned int divisor;
		if (mostrables > mensajeAMostrar->size()) divisor = mostrables;
		else 	divisor = mensajeAMostrar->size();
		int desplazamientoY = (alto/divisor - mensajeAMostrar->at(i)->h) / 2;
		int desplazamientoX = (ancho - mensajeAMostrar->at(i)->w) / 2;
		destino.x = x+desplazamientoX;
		destino.y = y + desplazamientoY+ i * (alto/mostrables);
		SDL_BlitSurface(mensajeAMostrar->at(i), NULL, display, &destino);
	}

	return dibujeCuadro;
}

void VistaLista::llenarVector(ListaScrolleable* lista){
	if (!lista) return;

	seleccionadoAnterior = seleccionadoActual;
	seleccionadoActual = lista->indiceSeleccionado();

	if (seleccionadoActual == seleccionadoAnterior && !primeraVez) return;
	primeraVez = false;
	if (mensajeAMostrar->size() == 0){
		for (unsigned int i = 0; i < mostrables && i < lista->cantidad(); i++){
			string mensaje = acortarMensaje(lista->obtenerElemento(i));
			mensajeAMostrar->push_back(TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensaje.c_str(), Fuente::obtenerInstancia()->obtenerColor()));
		}
		topeSuperior = 0;
		if (mostrables <= lista->cantidad())
			topeInferior = mostrables;
		else
			topeInferior = lista->cantidad();
		return;
	}

	if ((seleccionadoActual < topeInferior) && (seleccionadoActual >= topeSuperior)) return;

	unsigned int largo = mensajeAMostrar->size();
	for (unsigned int i = 0; i < largo; i++){
			SDL_Surface* tex = mensajeAMostrar->at(mensajeAMostrar->size()-1);
			mensajeAMostrar->pop_back();
			delete (tex);
	}

	if (lista->cantidad() == 0){
		topeSuperior = topeInferior = 0;
		return;
	}

	if (seleccionadoActual >= topeInferior){
		//topeSuperior = topeSuperior + seleccionadoActual - topeInferior + 1;
		//topeInferior = topeInferior + seleccionadoActual - topeInferior + 1;
		topeSuperior = topeSuperior + 1;
		topeInferior = topeInferior + 1;
	}else if (seleccionadoActual < topeSuperior){
		//topeSuperior = topeSuperior - (topeSuperior - seleccionadoActual);
		//topeInferior = topeInferior - (topeSuperior - seleccionadoActual);
		topeSuperior = topeSuperior - 1;
		topeInferior = topeInferior - 1;
	}

	for (unsigned int i = topeSuperior; i<topeInferior; i++){
		string mensaje = acortarMensaje(lista->obtenerElemento(i));
		mensajeAMostrar->push_back( TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensaje.c_str(), Fuente::obtenerInstancia()->obtenerColor()));
	}
}

string VistaLista::acortarMensaje(string mensaje){
	string acortado="";
	unsigned int i = 0;
	unsigned int anchito = ancho;
	while ((acortado.size() * ANCHOLETRA <= anchito) && (i < mensaje.size())){
		acortado+=mensaje.at(i);
		i++;
	}
	return acortado;
}
