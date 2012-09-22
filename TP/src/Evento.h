#ifndef EVENTO_H
#define EVENTO_H

#include "SDL/SDL.h"

class Evento {
public:
	Evento();

	virtual ~Evento();

	virtual void manejarEvento(SDL_Event* Event);

	// Se pueden agregar mas eventos, para teclado, mouse, ventana, etc

    virtual void inputFocus();

    virtual void inputBlur();

    virtual void teclaApretada(SDLKey sym, SDLMod mod, Uint16 unicode);

    virtual void teclaSoltada(SDLKey sym, SDLMod mod, Uint16 unicode);

    virtual void mouseFocus();

    virtual void mouseBlur();

    virtual void mouseMovimiento(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

    virtual void mouseRueda(bool Up, bool Down);    //Not implemented

    virtual void mouseClickIzqApretado(int mX, int mY);

    virtual void mouseClickIzqSoltado(int mX, int mY);

    virtual void mouseClickDerApretado(int mX, int mY);

    virtual void mouseClickDerSoltado(int mX, int mY);

    virtual void mouseClickMedApretado(int mX, int mY);

    virtual void mouseClickMedSoltado(int mX, int mY);

    virtual void joystickEjes(Uint8 which, Uint8 axis, Sint16 value);

    virtual void joystickBotonApretado(Uint8 which, Uint8 button);

    virtual void joystickBotonSoltado(Uint8 which, Uint8 button);

    virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);

    virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);

    virtual void minimizar();

    virtual void restaurar();

    virtual void redimensionar(int w,int h);

    virtual void OnExpose();

    virtual void OnUser(Uint8 type, int code, void* data1, void* data2);




	virtual void salir();
};

#endif
