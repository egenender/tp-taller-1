/*
 * ImagenGUI.h
 *
 *  Created on: 15/10/2012
 *      Author: martin
 */

#ifndef IMAGENGUI_H_
#define IMAGENGUI_H_
#include <string>
#include "ObjetoGUI.h"
#include "Label.h"
#include "../view/VistaLabel.h"
#include "../../view/Superficie.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
using namespace std;

class ImagenGUI : public ObjetoGUI{
private:
	Superficie* sup;
	Label* label;
	VistaLabel* vista;
public:
	ImagenGUI(string, string, int , int , int, int);
	virtual ~ImagenGUI();
	bool dibujar(SDL_Surface*);
};

#endif /* IMAGENGUI_H_ */
