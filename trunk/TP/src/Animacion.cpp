#include "Animacion.h"

Animacion::~Animacion() {
	delete(frames);
}

void Animacion::inicializar() {
	this->frames = NULL;
	frameActual = 0;
	framesTotales = 0;
	incrementoFrame = 1;
	delayFrame = 150; // milisegundos
	tiempoViejo = 0;
	corriendo = true;
	puntoDetencion = -1;
	delaysFrames = NULL;
}

void Animacion::cargarFrames(HojaSprites* frames) {
	if (!frames)
		return;

	this->frames = frames;
	framesTotales = frames->obtenerNumeroSprites();
}

/** Crea una Animacion a partir de una HojaSprites **/
Animacion::Animacion(HojaSprites* frames) {
	inicializar();
	cargarFrames(frames);
}

/** Crea una Animacion a partir de una HojaSprites, con una duracion total definida **/
/*Animacion::Animacion(HojaSprites* frames, int duracion) {

	inicializar();
	cargarFrames(frames);

	if (duracion > 0) {
		delayFrame = duracion/framesTotales;
	}
}*/

/** Crea una Animacion a partir de una HojaSprites, con duracion de frames definido **/
Animacion::Animacion(HojaSprites* frames, int delayFrame) {

	inicializar();
	cargarFrames(frames);

	this->delayFrame = delayFrame;
}


/** Crea una Animacion a partir de una HojaSprites, con duracion de frames definidos (pueden variar) **/
Animacion::Animacion(HojaSprites* frames, vector<int>* frameDelays) {

	inicializar();
	cargarFrames(frames);

	if (frameDelays->size() == frames->obtenerNumeroSprites()) {
		this->delaysFrames = frameDelays;
	}
}

/** Anima la animacion (actualiza) **/
void Animacion::animar() {
	if (framesTotales <= 0)
		return;

	if (!corriendo)
		return;

	if (puntoDetencion == frameActual) {
		corriendo = false;
		return;
	}

	int delay = delayFrame;

	if (delaysFrames) {
		delay = delaysFrames->at(frameActual);
	}

	if (tiempoViejo + delay > SDL_GetTicks()) {
		return;
	}

	tiempoViejo = SDL_GetTicks();

	frameActual += incrementoFrame;

	if (frameActual >= framesTotales) {
		frameActual = 0;
	}
}

/** Setea la duracion de cada frame individual **/
void Animacion::setearDelayFrame(int delay) {
	if (delay <= 0)
		return;
	delayFrame = delay;
}

/** Setea la duracion total de la animacion **/
void Animacion::setearDuracion(int duracion) {
	if (duracion <= 0)
		return;

	delayFrame = duracion/framesTotales;
}

/** Setea como actual a un frame determinado **/
void Animacion::setearFrameActual(int frame) {
	if (frame < 0 || frame >= framesTotales)
		return;

	frameActual = frame;
}

/** Dibuja la animacion actual sobre la superficie "supDest", en la posicion x,y **/
bool Animacion::dibujar(SDL_Surface* supDest, int x, int y) {
	if (supDest == NULL || frames == NULL) {
		return false;
	}

	return frames->dibujar(supDest, x, y, obtenerFrameActual());
}

/** Devuelve el numero de frame actual **/
int Animacion::obtenerFrameActual() {
	return frameActual;
}

/** Detiene la animacion en el frame actual **/
void Animacion::detener() {
	corriendo = false;
}

/** Detiene la animacion en un determinado frame. (Se anima hasta que llega a ese) **/
void Animacion::detenerEn(int frame) {
	if (frame < 0 || frame >= framesTotales)
		return;

	puntoDetencion = frame;
}

/** Continua la animacion si estaba detenida **/
void Animacion::continuar() {
	if (!estaCorriendo()) {
		puntoDetencion = -1;
		corriendo = true;
	}
}

/** Vuelve a comenzar la animacion desde 0 **/
void Animacion::resetear() {
	frameActual = 0;
	puntoDetencion = -1;
	corriendo = true;
}

/** Devuelve la cantidad de frames de la animacion **/
int Animacion::obtenerFramesTotales() {
	return framesTotales;
}

/** Si se esta animando (no esta detenida) **/
bool Animacion::estaCorriendo() {
	return corriendo;
}