#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 150
#include "Area.h"
#include "Cuerpo.h"
#include "Observable.h"

//Defino constantes para conocer mi estado
#define QUIETO 0
#define CAMINANDOIZQ 1
#define CAMINANDODER 2
#define QUIETODER 3
#define QUIETOIZQ 4
//#define SALTANDOIZQ 3
//#define SALTANDODER 4

// Nuevo:
#define DERECHA 1
#define IZQUIERDA -1

/*
// Nuevo:
class Manual:public Cuerpo {
private:
	int velocidad;
	int estado;
	int direccion;
	int velocidadX;
public:
	Manual(const char*, Area*);
	Manual(const char*, Area*, int);
	virtual ~Manual();
	void moverALaIzquierda();
	void moverALaDerecha();
	void detener();
	//Estos 3 por ahora no van a hacer nada
	void saltar();
	void atacar();
	void especial();
	void actualizar(float delta);
	int obtenerEstado();
private:
	void trasladar();
};*/

// Viejo:
class Manual:public Cuerpo {
private:
	int velocidad;
	float delta;
	int estado;
public:
	Manual(const char*, Area*);
	Manual(const char*, Area*, int);
	virtual ~Manual();
	void moverALaIzquierda();
	void moverALaDerecha();
	void detener();
	//Estos 3 por ahora no van a hacer nada
	void saltar();
	void atacar();
	void especial();
	void actualizar(float delta);
	int obtenerEstado();
private:
	void trasladar(int);
};


#endif /* MANUAL_H_ */
