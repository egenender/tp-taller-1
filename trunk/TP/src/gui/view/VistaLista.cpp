
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
}

VistaLista::~VistaLista() {
	delete (cuadro);
	unsigned int largo = mensajeAMostrar->size();
	for (unsigned int i = 0; i < largo; i++){
		SDL_Surface* tex = mensajeAMostrar->at(mensajeAMostrar->size()-1);
		mensajeAMostrar->pop_back();
		delete (tex);
	}
	delete (mensajeAMostrar);
}

void VistaLista::actualizar(Observable* observable){
	ListaScrolleable* lista = (ListaScrolleable*) observable;
	x = lista->obtenerX();
	y = lista->obtenerY();
	ancho = lista->obtenerAncho();
	alto = lista->obtenerAlto();

	llenarVector(lista);
	cuadro->escala(ancho,alto);
	seleccionado->escala(ancho, alto/mostrables);
	visible = lista->esVisible();
}

bool VistaLista::dibujar(SDL_Surface* display){
	if (!visible) return true;

	bool dibujeCuadro = cuadro->dibujar(display, x, y);
	unsigned int dsf;
	dsf = seleccionadoActual - topeSuperior;
	dibujeCuadro&= seleccionado->dibujar(display,x,(y + dsf * alto / mostrables));


	if (mensajeAMostrar->size() == 0){
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
	seleccionadoAnterior = seleccionadoActual;
	seleccionadoActual = lista->indiceSeleccionado();

	if (seleccionadoActual == seleccionadoAnterior && !primeraVez) return;
	primeraVez = false;
	if (mensajeAMostrar->size() == 0){
		for (unsigned int i = 0; i < mostrables && i < lista->cantidad(); i++){
			mensajeAMostrar->push_back(TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), lista->obtenerElemento(i).c_str(), Fuente::obtenerInstancia()->obtenerColor()));
		}
		topeSuperior = 0;
		if (mostrables <= lista->cantidad())
			topeInferior = mostrables;
		else
			topeInferior = lista->cantidad();
		return;
	}

	if ((seleccionadoActual < topeInferior) && (seleccionadoActual >= topeSuperior)) return;
	mensajeAMostrar->clear();
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
		mensajeAMostrar->push_back( TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), lista->obtenerElemento(i).c_str(), Fuente::obtenerInstancia()->obtenerColor()));
	}
}
