#include "Timer.h"

Timer::Timer() {
	ticksEmpezado = 0;
	ticksPausado = 0;
	pausado = false;
	empezado = false;
}

void Timer::comenzar() {
	empezado = true;
	pausado = false;
	ticksEmpezado = SDL_GetTicks();
}

void Timer::detener() {
	empezado = false;
	pausado = false;
}
void Timer::pausar() {
	if ((empezado == true) && (pausado == false)) {
		pausado = true;
		ticksPausado = SDL_GetTicks() - ticksEmpezado;
	}
}

void Timer::quitarPausa() {
	if (pausado == true) {
		pausado = false;
		ticksEmpezado = SDL_GetTicks() - ticksPausado;
		ticksPausado = 0;
	}
}

bool Timer::estaEmpezado() {
	return empezado;
}
bool Timer::estaPausado() {
	return pausado;
}

int Timer::obtenerTiempo() {
	if (empezado == true) {
		if (pausado == true)
			return ticksPausado;
		else
			return SDL_GetTicks() - ticksEmpezado;
	}
	return 0;
}
