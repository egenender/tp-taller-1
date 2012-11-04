#ifndef BARRIL_H_
#define BARRIL_H_
#include "Cuerpo.h"
#include "Actualizable.h"
#include "Plataforma.h"
#include "Observable.h"

class Manual;
class Escalera;

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
	bool yaPaso;

public:
	Barril(const char*, Area*, int vel, int dir);
	virtual ~Barril();

	void actualizar(float);
	int obtenerEstado();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);

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
