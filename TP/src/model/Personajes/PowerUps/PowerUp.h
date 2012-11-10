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
	bool tengoPiso, chocaConSosten;
	int velocidadX, velocidadY, direccion, estado;

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
	void validarPiso();
	void actualizarEstados();
protected:
	void actualizarMovimiento();
	void actualizarSalto();
};

#endif /* POWERUP_H_ */
