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
	cantVecesAnimado = 0;
}

void Animacion::cargarFrames(HojaSprites* frames) {
	if (!frames) {
		printf("Error al cargar Frames: se recibio NULL\n");
		return;
	}

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
		cantVecesAnimado++;
	}
}

/** Setea la duracion de cada frame individual **/
void Animacion::setearDelayFrame(int delay) {
	if (delay <= 0) {
		printf("Warning: se recibio un delay frame negativo, se dejo el default\n");
		return;
	}
	delayFrame = delay;
}

/** Setea la duracion total de la animacion **/
void Animacion::setearDuracion(int duracion) {
	if (duracion <= 0) {
		printf("Warning: se recibio una duracion negativa, se dejo la default\n");
		return;
	}

	delayFrame = duracion/framesTotales;
}

/** Setea como actual a un frame determinado **/
void Animacion::setearFrameActual(int frame) {
	if (frame < 0 || frame >= framesTotales) {
		printf("Warning: se recibio un frame negativo o mayor al total, se dejo el actual\n");
		return;
	}

	frameActual = frame;
}

/** Dibuja la animacion actual sobre la superficie "supDest", en la posicion x,y **/
bool Animacion::dibujar(SDL_Surface* supDest, int x, int y) {
	if (supDest == NULL || frames == NULL) {
		printf("Error al dibujar animacion\n");
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
	if (frame < 0 || frame >= framesTotales) {
		printf("Warning: se recibio un frame negativo o mayor al total, se dejo el actual\n");
		return;
	}

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
	cantVecesAnimado = 0;
}

/** Devuelve la cantidad de frames de la animacion **/
int Animacion::obtenerFramesTotales() {
	return framesTotales;
}

/** Si se esta animando (no esta detenida) **/
bool Animacion::estaCorriendo() {
	return corriendo;
}


/** Devuelve una nueva animacion volteada, respecto de la original.
 * Parametros: El tipo de volteo: HORIZONTALMENTE y VERTICALMENTE
 * Se puede hacer ambos volteos a la vez, pasar como parametro:
 * HORIZONTALMENTE | VERTICALMENTE **/
Animacion* Animacion::voltear(int flags) {
	HojaSprites* volteada = frames->voltear(flags);

	return new Animacion(volteada, delayFrame);
}

/** Escala los sprites de la animacion **/
bool Animacion::escala(Uint16 anchoSprite, Uint16 altoSprite) {
	return frames->escala(anchoSprite, altoSprite);
}

/** Escala los sprites de la animacion **/
bool Animacion::escala(Uint16 factor) {
	return frames->escala(factor);
}

/** Setea un color RGB como transparente **/
void Animacion::transparencia(unsigned int R, unsigned int G, unsigned int B) {
	frames->transparencia(R,G,B);
}

bool Animacion::termino(){
	return (cantVecesAnimado > 0);
}
