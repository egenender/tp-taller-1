#ifndef PERSONAJE_H_
#define PERSONAJE_H_

class Personaje: public Cuerpo{
private:
	lista_t* acciones;

public:
	Personaje(Area*, Animacion*,lista_t*);
	virtual ~Personaje();
	/*Por si quiero trasladar a un personaje a una pos especifica, en vez de a una relativa a la actual:*/
	void trasladarA(Posicion);
	void morir();

	//Habria que implementar luego el double dispatching para resolver colisiones
	//No es necesario por ahora
};

#endif /* PERSONAJE_H_ */
