#ifndef HONGO_H_
#define HONGO_H_
#include "../Cuerpo.h"
#include "../Actualizable.h"
#include "Plataforma.h"
#include "../Area.h"
#include "../Observable.h"

#define VELOCIDAD_HONGO_STANDARD 5
#define DERECHA 1
#define IZQUIERDA -1
#define FACTOR_ESCALA_HONGO 90
#define ACELERACION_HONGO 1

class Manual;
class Barril;

class Hongo : public Cuerpo{
private:
	int estado;
	int velocidadX, velocidadY, direccion;
	bool tengoPiso, chocaConSosten;

public:
	Hongo(const char*, Area*, int);
	virtual ~Hongo();

	void actualizar(float);
	int obtenerEstado();
	bool estaMuerto();

	void chocarCon(Actualizable*);
	void chocarConPlataforma(Plataforma*);
	void chocarConManual(Manual*);
	void chocarConBarril(Barril*);
private:
	int calculoDireccionRandom();
	void morir();
	void validarPiso();
	void actualizarSalto();
	void actualizarMovimiento();
	void actualizarEstados();
	bool estoySaltando();
};

#endif /* HONGO_H_ */
