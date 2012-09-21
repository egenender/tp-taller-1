#ifndef ESTATICO_H_
#define ESTATICO_H_
#include "Cuerpo.h"
#include "Area.h"

class Estatico : public Cuerpo{

public:
	Estatico(const char*, Area*);
	virtual ~Estatico();

	//redefino los metodos heredados:
	int obtenerEstado();	 //de observable
	void actualizar(); 		//de cuerpo


};

#endif /* ESTATICO_H_ */
