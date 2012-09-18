#ifndef ANIMACION_H_
#define ANIMACION_H_

#include "SDL/SDL.h"
#include "HojaSprites.h"
#include <vector>
using namespace std;

#define VERTICALMENTE 0x00000001
#define HORIZONTALMENTE 0x00000010

class Animacion {
	private:
		HojaSprites* frames;
		int frameActual;
		int incrementoFrame;
		bool corriendo;
		int framesTotales;
		unsigned int delayFrame; //Milisegundos
		unsigned long tiempoViejo;
		int puntoDetencion;
		vector<int>* delaysFrames;

	private:
		void inicializar();
		void cargarFrames(HojaSprites* frames);

	// Contructores y Destructor:
	public:
		Animacion(HojaSprites* frames);
		Animacion(HojaSprites* frames, int delayFrame);
		Animacion(HojaSprites* frames, vector<int>* frameDelays);

		~Animacion();

	// Metodos:
		void animar();
		void detener();
		void detenerEn(int frame);
		void resetear();
		void continuar();
		void setearDelayFrame(int delay);
		void setearFrameActual(int frame);
		void setearDuracion(int duracion);
		int obtenerFrameActual();
		int obtenerFramesTotales();
		bool estaCorriendo();
		bool dibujar(SDL_Surface* supDest, int x, int y);
		Animacion* voltear(int flags);
};

#endif
