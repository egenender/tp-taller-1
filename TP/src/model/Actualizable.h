#ifndef ACTUALIZABLE_H_
#define ACTUALIZABLE_H_
#include "Area.h"
class Manual;
class Escalera;
class Plataforma;
class Barril;
class Hongo;
class Princesa;
class BolaDeFuego;
class CamaElastica;

class Actualizable {
public:
	Actualizable();
	virtual ~Actualizable();
	virtual void actualizar(float delta)=0;
	virtual Area* obtenerArea()= 0;
	virtual bool estaMuerto();

	/*DOUBLE DISPATCHING*/
	virtual void chocarCon(Actualizable*)=0;
	virtual void chocarConManual(Manual*);
	virtual void chocarConPlataforma(Plataforma*);
	virtual void chocarConEscalera(Escalera*);
	virtual void chocarConBarril(Barril*);
	virtual void chocarConHongo(Hongo*);
	virtual void chocarConPrincesa(Princesa*);
	virtual void chocarConBolaDeFuego(BolaDeFuego*);
	virtual void chocarConCamaElastica(CamaElastica*);
//Los automaticos no haran nada
};

#endif /* ACTUALIZABLE_H_ */
