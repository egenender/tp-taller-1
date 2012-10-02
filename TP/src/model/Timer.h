#ifndef TIMER_H_
#define TIMER_H_

#include "SDL/SDL.h"

class Timer {

	private:
		int ticksEmpezado, ticksPausado;
		bool empezado, pausado;

	public:
		Timer();
		void comenzar();
		void detener();
		void pausar();
		void quitarPausa();
		bool estaEmpezado();
		bool estaPausado();
		int obtenerTiempo();
};

#endif
