#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 150
#include "../Area.h"
#include "../Cuerpo.h"
#include "../Actualizable.h"
#include "../Observable.h"

class Hongo;
class Escalera;
class Barril;
class Princesa;
#include "Plataforma.h"

// Nuevo:
#define DERECHA 1
#define IZQUIERDA -1
#define FACTOR_DE_ESCALA 80
#define CANT_VIDAS 3

/* si quiero cambiar la aceleracion para que caiga mas rapido, pero quiero
 que la altura maxima sea la misma a la que hay ahora:
 VbaseNueva = VbaseVieja * sqrt(aceleracionNueva/aceleracionVieja)
*/
#define ACELERACION 8

class Manual:public Cuerpo {
private:
	int velocidad;
	float delta;
	int estado;
	int velocidadY;
	int velocidadSaltoBase;
	bool puedoSubir, tengoPiso, atraviesaBloques, chocaConEscalera;
	bool chocaConSosten, enViga;
	bool juegoGanado;
	int vidas, x_inicial;
public:
//	Manual(const char*, Area*);
//	Manual(const char*, Area*, int);
	Manual(const char*, Area*, int, int);
	virtual ~Manual();
	void posicionar(Posicion*);

	void moverALaIzquierda();
	void moverALaDerecha();
	void detener();
	void saltar();
	void atacar();
	void especial();
	void subir();
	void bajar();

	void actualizar(float delta);
	int obtenerEstado();
	void morir();
	bool estaMuerto();
	bool esGanador();
	void setearXInicial(int);
	int obtenerVidas();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
	void chocarConBarril(Barril*);
	void chocarConHongo(Hongo*);
	void chocarConPrincesa(Princesa*);
	void chocarConBolaDeFuego(BolaDeFuego*);
private:
	void mtrasladar(int,int,bool);
	void actualizarSalto();
	bool estoySaltando();
	bool estoySubiendo();
	void movimiento(int,int,int);
	bool chocaConPiso();
	void validarPiso();
	void actualizarEstados();
	void perderVida();
};


#endif /* MANUAL_H_ */
