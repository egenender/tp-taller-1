#ifndef FPS_H
#define FPS_H

#include <SDL/SDL.h>

class FPS {
	public:
        static FPS ControlFPS;

	private:
        unsigned int viejoTiempo;
        unsigned int ultimoTiempo;
		float delta;
		int numFrames;
		int frames;

	public:
		FPS();
		void actualizar();
		int obtenerFPS();
		float obtenerDelta();
};

#endif
