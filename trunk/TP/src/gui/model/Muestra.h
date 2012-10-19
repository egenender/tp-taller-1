#ifndef MUESTRA_H_
#define MUESTRA_H_
#include "ObjetoGUI.h"
#include "../../view/Animacion.h"

class Muestra :public ObjetoGUI{
private:
	vector<Animacion*>* animaciones;
	unsigned int seleccion;
public:
	Muestra(int,int,int,int);
	virtual ~Muestra();
	void agregarVista (Animacion*);
	void eliminarVista (unsigned int);
	void siguiente();
	void anterior();
	Animacion* obtenerActual();
	bool dibujar(SDL_Surface*);
};

#endif /* MUESTRA_H_ */
