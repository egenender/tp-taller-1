#ifndef ESTATICO_H_
#define ESTATICO_H_
#include "model/Cuerpo.h"
#include "model/Area.h"

class Estatico : public Cuerpo{

public:
	Estatico(const char*, Area*);
	virtual ~Estatico();

	//redefino los metodos heredados:
	int obtenerEstado();	 //de observable
	void actualizar(float delta); 		//de cuerpo


};

#endif /* ESTATICO_H_ */
