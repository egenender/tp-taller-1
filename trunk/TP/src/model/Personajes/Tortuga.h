#ifndef TORTUGA_H_
#define TORTUGA_H_

#include "Hongo.h"
#include "../Area.h"
#define MULTIPLICADOR 3
#define FACTOR_TORTUGA_CHICA 50

class Tortuga: public Hongo {
private:
	int velocidadInicial;
	bool recien_movido;
	Area* superficieReemplazo;
	int proxEstado;
public:
	Tortuga(const char*, Area*, int);
	virtual ~Tortuga();
	bool recienMovido();
	void actualizar(float);
	unsigned int obtenerTipo();
protected:
	void perderVida();
	void modificacionMovimiento(int);

};

#endif /* TORTUGA_H_ */
