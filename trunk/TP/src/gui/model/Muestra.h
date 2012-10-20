#ifndef MUESTRA_H_
#define MUESTRA_H_
#include "ObjetoGUI.h"
#include "../../view/Animacion.h"
#include "Label.h"
#include "../../view/TipoProtagonista.h"

class Muestra :public ObjetoGUI{
private:
	unsigned int seleccion;
	Label *nombre, *velocidad, *salto;
	vector<TipoProtagonista*>* personajes;
public:
	Muestra(Label*, Label*, Label*, int,int,int,int);
	virtual ~Muestra();
	void agregarVista ( TipoProtagonista*);
	void eliminarVista (unsigned int);
	void siguiente();
	void anterior();
	//Animacion* obtenerActual();
	bool dibujar(SDL_Surface*);
};

#endif /* MUESTRA_H_ */
