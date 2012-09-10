
#ifndef AREA_H_
#define AREA_H_

/* Las Areas estaran definidas como cuadrados, para simplificar el verificar las colisiones*/

#include "Posicion.h"

class Area {
	private:
		int ancho, alto;
		Posicion* pos; //esta posicion indica la posicion que tiene el punto superior izquierdo
	public:
		Area(int, int);
		Area(int, int, Posicion*); //revisar si no deberia ser Posicion a secas
		void cambiarPosicion(Posicion*); //idem
		void mover(Posicion);
		bool verificarColision(Area);
		virtual ~Area();
};

#endif /* AREA_H_ */
