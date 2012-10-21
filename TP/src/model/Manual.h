#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 150
#include "Area.h"
#include "Cuerpo.h"
#include "Observable.h"

// Nuevo:
#define DERECHA 1
#define IZQUIERDA -1

/* si quiero cambiar la aceleracion para que caiga mas rapido, pero quiero
 que la altura maxima sea la misma a la que hay ahora:
 VbaseNueva = VbaseVieja * sqrt(aceleracionNueva/aceleracionVieja)
*/
#define ACELERACION 10

class Manual:public Cuerpo {
private:
	int velocidad;
	float delta;
	int estado;
	int velocidadY;
	int velocidadSaltoBase;
public:
	Manual(const char*, Area*);
	Manual(const char*, Area*, int);
	Manual(const char*, Area*, int, int);
	virtual ~Manual();
	void moverALaIzquierda();
	void moverALaDerecha();
	void detener();

	void saltar();
	void atacar();
	void especial();
	void actualizar(float delta);
	int obtenerEstado();
	void morir();
	bool estaMuerto();
private:
	void trasladar(int,int);
	void actualizarSalto();
	bool estoySaltando();
	void movimiento(int,int,int);
	bool chocaConPiso();
};


#endif /* MANUAL_H_ */
