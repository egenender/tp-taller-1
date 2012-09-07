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
Animacion::Animacion(HojaSprites* frames) {
	inicializar();
	cargarFrames(frames);
}

Animacion::Animacion(HojaSprites* frames, int duracion) {

	inicializar();
	cargarFrames(frames);

	if (duracion > 0) {
		delayFrame = duracion/framesTotales;
	}
}

Animacion::Animacion(HojaSprites* frames, vector<int>* frameDelays) {

	inicializar();
	cargarFrames(frames);

	if (frameDelays->size() == frames->obtenerNumeroSprites()) {
		this->delaysFrames = frameDelays;
	}
}


void Animacion::animar() {
	if (puntoDetencion == frameActual)
		corriendo = false;

	if (!corriendo)
		return;

	if (framesTotales <= 0)
		return;

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

void Animacion::setearDelayFrame(int delay) {
	if (delay <= 0)
		return;
	delayFrame = delay;
}

void Animacion::setearDuracion(int duracion) {
	if (duracion <= 0)
		return;

	delayFrame = duracion/framesTotales;
}

void Animacion::setearFrameActual(int frame) {
	if (frame < 0 || frame >= framesTotales)
		return;

	frameActual = frame;
}

bool Animacion::dibujar(SDL_Surface* supDest, int x, int y) {
	if (supDest == NULL || frames == NULL) {
		return false;
	}

	return frames->dibujar(supDest, x, y, obtenerFrameActual());
}


int Animacion::obtenerFrameActual() {
	return frameActual;
}

void Animacion::detener() {
	corriendo = false;
}

void Animacion::detenerEn(int frame) {
	if (frame < 0 || frame >= framesTotales)
		return;

	puntoDetencion = frame;
}

void Animacion::continuar() {
	puntoDetencion = -1;
	corriendo = true;
}

void Animacion::resetear() {
	frameActual = 0;
	puntoDetencion = -1;
	corriendo = true;
}

int Animacion::obtenerFramesTotales() {
	return framesTotales;
}
