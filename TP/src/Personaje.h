#ifndef PERSONAJE_H_
#define PERSONAJE_H_
#include "Posicion.h"
#include "Area.h"
#include "Animacion.h"
#include "EstrategiaMovimiento.h"

class Personaje: public Cuerpo, public Jugable{
private:
EstrategiaMovimiento* estrategia;
public:
	Personaje(Area*, Animacion*, EstrategiaMovimiento*);
	virtual ~Personaje();
	/*Por si quiero trasladar a un personaje a una pos especifica, en vez de a una relativa a la actual:*/
	void trasladarA(Posicion);
	void morir();
	void jugar();

	//Habria que implementar luego el double dispatching para resolver colisiones
	//No es necesario por ahora
};

#endif /* PERSONAJE_H_ */
