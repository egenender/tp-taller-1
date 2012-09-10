#ifndef PERSONAJE_H_
#define PERSONAJE_H_
#include "Posicion.h"
#include "Area.h"
#include "Animacion.h"
#include "Cuerpo.h"
#include "Jugable.h"
#include "EstrategiaMovimiento.h"

class Personaje: public Cuerpo, public Jugable {
	private:
		EstrategiaMovimiento* estrategia;
	public:
		Personaje(Area*, Animacion*, EstrategiaMovimiento*);
		virtual ~Personaje();
		/*Por si quiero trasladar a un personaje a una pos especifica, en vez de a una relativa a la actual:*/
		void trasladarA(Posicion*);
		void morir();
		void jugar();

		//Cada personaje redefine como corresponda:
		virtual void moverAIzquierda()=0;
		virtual void moverADerecha()=0;
		virtual void atacar(/*ver parametros*/)=0;
		virtual void saltar()=0;
		virtual void especial()=0;

		//Habria que implementar luego el double dispatching para resolver colisiones
		//No es necesario por ahora
};

#endif /* PERSONAJE_H_ */
