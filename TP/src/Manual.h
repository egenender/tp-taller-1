#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 5
#include "Area.h"
#include "Cuerpo.h"
#include "Observable.h"

//Defino constantes para conocer mi estado
#define QUIETO 0
#define CAMINANDOIZQ 1
#define CAMINANDODER 2
//#define SALTANDOIZQ 3
//#define SALTANDODER 4


class Manual:public Cuerpo {
private:
	int velocidad;
	int estado;
public:
	Manual(const char*, Area*);
	Manual(const char*, Area*, int);
	virtual ~Manual();
	void moverALaIzquierda();
	void moverALaDerecha();
	//Estos 3 por ahora no van a hacer nada
	void saltar();
	void atacar();
	void especial();
	void actualizar();
	int obtenerEstado();
private:
	void trasladar(int);
};

#endif /* MANUAL_H_ */
