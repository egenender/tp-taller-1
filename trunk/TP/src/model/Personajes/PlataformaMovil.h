#ifndef PLATAFORMAMOVIL_H_
#define PLATAFORMAMOVIL_H_

#include "Plataforma.h"
#include "../Cuerpo.h"
#include <vector>

#define VELOCIDAD_PLTMOVIL_STD 5
#define DIST_PLTMOVIL_STD 50

class PlataformaMovil: public Plataforma {
private:
	std::vector<Cuerpo*>* cuerposContacto;
	int velocidad, desplazamiento, actual;
	bool esElevador;
public:
	PlataformaMovil(const char*, Area*, int, int D = 0);
	virtual ~PlataformaMovil();
	void actualizar(float);
	unsigned int obtenerTipo();
	void setearElevador();

	void chocarConManual(Manual*);
	void chocarConBarril(Barril*);
	void chocarConHongo(Hongo*);
	void chocarConPlataforma(Plataforma*);
	//virtual void chocarConPrincesa(Princesa*); Por ahora este no lo pongo...

};

#endif /* PLATAFORMAMOVIL_H_ */
