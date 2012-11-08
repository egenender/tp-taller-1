#ifndef BOLADEFUEGO_H_
#define BOLADEFUEGO_H_

#include "../Cuerpo.h"
#include "../Actualizable.h"

#define FACTOR_BOLA_FUEGO 60
#define VELOCIDAD_BOLA_STD 10
#define DERECHA_BF 1
#define IZQUIERDA_BF -1
#define ACELERACION_BF 5


class BolaDeFuego: public Cuerpo {
private:
	int direccion, estado, velocidadX, velocidadY, velocidadSaltoBase;
	bool tengoPiso, chocaConSosten;

public:
	BolaDeFuego(const char*, Area*, int, int, int);
	virtual ~BolaDeFuego();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConHongo(Hongo*);
	void chocarConBarril(Barril*);

	void actualizar(float);
	int obtenerEstado();
	bool estaMuerto();
private:
	void morir();
	void validarPiso();
	void actualizarSalto();
	void actualizarMovimiento();
	void actualizarEstados();
	bool estoySaltando();
	void saltar();
};

#endif /* BOLADEFUEGO_H_ */
