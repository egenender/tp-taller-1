#ifndef POWERUP_H_
#define POWERUP_H_
#include "../../Cuerpo.h"
#include "../Plataforma.h"
#include "../../Actualizable.h"

#define VELOCIDAD_PWRUP_STD 1
#define FACTOR_PWRUP 85
#define IZQUIERDA -1
#define DERECHA 1
#define ACELERACION_PWRUP 2

class PowerUp : public Cuerpo{
private:
	bool chocaConSosten;
	int  velocidadX, direccion;
protected:
	int velocidadY, estado;
	bool tengoPiso;
	bool puedoMovermeEnElAire;

public:
	PowerUp(const char*, Area*, int);
	virtual ~PowerUp();

	virtual void actualizar(float);

	void chocarCon(Actualizable*);
	void chocarConPlataforma(Plataforma*);
	bool estaMuerto();
	int obtenerEstado();

private:
	int calculoDireccionRandom();
	void actualizarEstados();
protected:
	virtual void actualizarMovimiento();
	void actualizarSalto();
	virtual void validarPiso();
};

#endif /* POWERUP_H_ */
