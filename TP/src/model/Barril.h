#ifndef BARRIL_H_
#define BARRIL_H_
#include "Cuerpo.h"
#include "Actualizable.h"
#include "Plataforma.h"
#include "Observable.h"
#include "Escalera.h"

class Manual;

#define ESCALA 90
#define ACELERACION 8
#define VEL_BASE 5
#define DIR_IZQ -1
#define DIR_DER 1
#define PROBABILIDAD_BAJADA 30

class Barril : public Cuerpo {
private:
	int direccion;
	int estado;
	int velocidadX, velocidadY;
	bool puedoBajar, tengoPiso, atraviesaBloques, chocaConEscalera;
	bool chocaConSosten;
	bool bajarEnSiguiente;
	Posicion* posAnterior;
	bool permito; //variable para permitir caida (depende de si ya bajo por una escalera, etc)
	Escalera* esc;
	Plataforma* plt;

public:
	Barril(const char*, Area*, int vel, int dir);
	virtual ~Barril();

	void actualizar(float);
	int obtenerEstado();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
	void chocarConBarril(Barril*);

private:
	void destruir();
	void actualizarEstados();
	void actualizarMovimiento();
	void actualizarSalto();
	void validarPiso();
	bool calculoBajada();
	void bajar();
};

#endif /* BARRIL_H_ */
