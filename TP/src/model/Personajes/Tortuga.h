#ifndef TORTUGA_H_
#define TORTUGA_H_

#include "Hongo.h"
#include "../Area.h"

class Tortuga: public Hongo {
private:
	int velocidadInicial;
public:
	Tortuga(const char*, Area*, int);
	virtual ~Tortuga();

protected:
	void perderVida();
	void modificacionMovimiento(int);
};

#endif /* TORTUGA_H_ */
