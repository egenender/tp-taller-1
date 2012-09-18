#include "FPS.h"

FPS FPS::ControlFPS;

FPS::FPS() {
	viejoTiempo = 0;
	ultimoTiempo = 0;
	delta = 0;
	frames = 0;
	numFrames = 0;
}

void FPS::actualizar() {

	// Obtenemos el tiempo que paso desde que se inicializo SDL:
	unsigned int ticks = SDL_GetTicks(); // milisegundos! si lo queremos en segundos, dividir por 1000.

	// Reseteamos los FPS a 0 si paso mas de un segundo:
	if (viejoTiempo + 1000 < ticks) {
		viejoTiempo = ticks;
		numFrames = frames;
		frames = 0;
	}

	delta = ((ticks - ultimoTiempo) / 1000.0f) /* *24.0f */;
	ultimoTiempo = ticks;

	frames++; // Acumulamos un frame.
}

int FPS::obtenerFPS() {
	return numFrames;
}

float FPS::obtenerDelta() {
	return delta;
}
