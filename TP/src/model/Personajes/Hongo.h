#ifndef HONGO_H_
#define HONGO_H_
#include "../Cuerpo.h"
#include "../Actualizable.h"
#include "Plataforma.h"
#include "../Area.h"
#include "../Observable.h"

#define VELOCIDAD_HONGO_STANDARD 3
#define DERECHA 1
#define IZQUIERDA -1
#define FACTOR_ESCALA_HONGO 90
#define ACELERACION_HONGO 3

class Manual;
class Barril;

class Hongo : public Cuerpo{
private:
	bool tengoPiso, chocaConSosten;
protected:
	int estado;
	int velocidadX, velocidadY, direccion;

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
	void chocarConHongo(Hongo*);
private:
	int calculoDireccionRandom();
	void validarPiso();
	void actualizarSalto();
	void actualizarMovimiento();
	void actualizarEstados();
	bool estoySaltando();
protected:
	void morir();
	virtual void perderVida();
	virtual void modificacionMovimiento(int);
};

#endif /* HONGO_H_ */
