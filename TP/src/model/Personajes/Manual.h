#ifndef MANUAL_H_
#define MANUAL_H_
#define VELOCIDAD_STANDARD 10
#include "../Area.h"
#include "../Cuerpo.h"
#include "../Actualizable.h"
#include "../Observable.h"
#include "Plataforma.h"
#include "../Fabricas/FabricaBolasDeFuego.h"
#include "../Timer.h"

class Hongo;
class Escalera;
class Barril;
class Princesa;

#define DERECHA 1
#define IZQUIERDA -1
#define FACTOR_DE_ESCALA 70
#define FACTOR_EVOLUCION 90
#define CANT_VIDAS 3
#define SUPERFICIE_EVOLUCION 1
#define SUPERFICIE_INVOLUCION 0
#define TIEMPO_TIMEOUT 4
#define TIEMPO_INVENCIBLE 10

/* si quiero cambiar la aceleracion para que caiga mas rapido, pero quiero
 que la altura maxima sea la misma a la que hay ahora:
 VbaseNueva = VbaseVieja * sqrt(aceleracionNueva/aceleracionVieja)
*/
#define ACELERACION 8

class Manual:public Cuerpo {
private:
	static bool cooperativo;

private:
	int velocidad;
	float delta;
	int estado;
	int velocidadY;
	int velocidadSaltoBase;
	bool puedoSubir, tengoPiso, atraviesaBloques, chocaConEscalera;
	bool chocaConSosten, enViga;
	bool chocaConCama, saltoAlto;

	bool pisareViga;

	bool juegoGanado;
	int vidas, x_inicial;

	Area* superficieReemplazo;
	int evolucionado;
	int supActual;

	bool especialHabilitado;
	FabricaBolasDeFuego *fabrica;

	Timer *timeout;
	bool invencible;

	int YEscalera;
	int YTecho;
	
	// NEW:
	bool reposicionar; // Si se tiene que cambiar de posicion (cuando lo matan)
	bool bloquearMovimiento; // Si recibe estimulos de teclado (cuando lo matan)

public:
	static void setearCooperatividad(bool);
	static bool esCooperativo();
	Manual(const char*, Area*, int, int);
	virtual ~Manual();
	void posicionar(Posicion*);

	void moverALaIzquierda();
	void moverALaDerecha();
	void detener();
	void saltar(bool autogenerado = false);
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
	bool estaInvencible();
	bool mataAlContacto();
	void aumentarVida();
	void evolucionar();
	void habilitarEspecial();
	void hacerInvencible();
	bool esEliminable();
	bool puedeMover(); // NEW
	int obtenerVelocidad();
	unsigned int obtenerTipo();
	bool saltaAlto();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
	void chocarConBarril(Barril*);
	void chocarConHongo(Hongo*);
	void chocarConPrincesa(Princesa*);
	void chocarConBolaDeFuego(BolaDeFuego*);
	void chocarConCamaElastica(CamaElastica*);
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
	void actualizarEvolucion();
	void actualizarTimeOut();
};


#endif /* MANUAL_H_ */
