#include "Evento.h"


Evento::Evento() {}

Evento::~Evento() {}

void Evento::manejarEvento(SDL_Event* evento) {

	switch (evento->type) {

	// Se pueden agregar mas eventos, para teclado, mouse, ventana, etc

		case SDL_ACTIVEEVENT: {
			switch (evento->active.state) {
				case SDL_APPMOUSEFOCUS: {
					if (evento->active.gain)
						mouseFocus();
					else
						mouseBlur();

					break;
				}
				case SDL_APPINPUTFOCUS: {
					if (evento->active.gain)
						inputFocus();
					else
						inputBlur();

					break;
				}
				case SDL_APPACTIVE: {
					if (evento->active.gain)
						restaurar();
					else
						minimizar();

					break;
				}
			}
			break;
		}

		case SDL_KEYDOWN: {
			teclaApretada(evento->key.keysym.sym, evento->key.keysym.mod,
					evento->key.keysym.unicode);
			break;
		}

		case SDL_KEYUP: {
			teclaSoltada(evento->key.keysym.sym, evento->key.keysym.mod,
					evento->key.keysym.unicode);
			break;
		}

		case SDL_MOUSEMOTION: {
			mouseMovimiento(evento->motion.x, evento->motion.y, evento->motion.xrel,
					evento->motion.yrel,
					(evento->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
					(evento->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
					(evento->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			switch (evento->button.button) {
				case SDL_BUTTON_LEFT: {
					mouseClickIzqApretado(evento->button.x, evento->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT: {
					mouseClickDerApretado(evento->button.x, evento->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE: {
					mouseClickMedApretado(evento->button.x, evento->button.y);
					break;
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP: {
			switch (evento->button.button) {
				case SDL_BUTTON_LEFT: {
					mouseClickIzqSoltado(evento->button.x, evento->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT: {
					mouseClickDerSoltado(evento->button.x, evento->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE: {
					mouseClickMedSoltado(evento->button.x, evento->button.y);
					break;
				}
			}
			break;
		}

		case SDL_JOYAXISMOTION: {
			joystickEjes(evento->jaxis.which, evento->jaxis.axis, evento->jaxis.value);
			break;
		}

		case SDL_JOYBALLMOTION: {
			OnJoyBall(evento->jball.which, evento->jball.ball, evento->jball.xrel,
					evento->jball.yrel);
			break;
		}

		case SDL_JOYHATMOTION: {
			OnJoyHat(evento->jhat.which, evento->jhat.hat, evento->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN: {
			joystickBotonApretado(evento->jbutton.which, evento->jbutton.button);
			break;
		}

		case SDL_JOYBUTTONUP: {
			joystickBotonSoltado(evento->jbutton.which, evento->jbutton.button);
			break;
		}

		case SDL_QUIT: {
			salir();
			break;
		}

		case SDL_SYSWMEVENT: {
			//Ignore
			break;
		}

		case SDL_VIDEORESIZE: {
			redimensionar(evento->resize.w, evento->resize.h);
			break;
		}

		case SDL_VIDEOEXPOSE: {
			OnExpose();
			break;
		}

		default: {
			OnUser(evento->user.type, evento->user.code, evento->user.data1,
					evento->user.data2);
			break;
		}
	}
}

void Evento::salir() {}

void Evento::inputFocus() {}

void Evento::inputBlur() {}

void Evento::teclaApretada(SDLKey sym, SDLMod mod, Uint16 unicode) {}

void Evento::teclaSoltada(SDLKey sym, SDLMod mod, Uint16 unicode) {}

void Evento::mouseFocus() {}

void Evento::mouseBlur() {}

void Evento::mouseMovimiento(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {}

void Evento::mouseRueda(bool Up, bool Down) {}

void Evento::mouseClickIzqApretado(int mX, int mY) {}

void Evento::mouseClickIzqSoltado(int mX, int mY) {}

void Evento::mouseClickDerApretado(int mX, int mY) {}

void Evento::mouseClickDerSoltado(int mX, int mY) {}

void Evento::mouseClickMedApretado(int mX, int mY) {}

void Evento::mouseClickMedSoltado(int mX, int mY) {}

void Evento::joystickEjes(Uint8 which, Uint8 axis, Sint16 value) {}

void Evento::joystickBotonApretado(Uint8 which, Uint8 button) {}

void Evento::joystickBotonSoltado(Uint8 which, Uint8 button) {}

void Evento::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {}

void Evento::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {}

void Evento::minimizar() {}

void Evento::restaurar() {}

void Evento::redimensionar(int w,int h) {}

void Evento::OnExpose() {}

void Evento::OnUser(Uint8 type, int code, void* data1, void* data2) {}
