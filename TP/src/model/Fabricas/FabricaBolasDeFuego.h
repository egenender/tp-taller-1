#ifndef FABRICABOLASDEFUEGO_H_
#define FABRICABOLASDEFUEGO_H_
#include "FabricaActualizable.h"
#include "../Posicion.h"
#include <string>
#include "../Personajes/BolaDeFuego.h"

class FabricaBolasDeFuego : public FabricaActualizable{
private:
	std::string nombre;
	BolaDeFuego* bola;
public:
	FabricaBolasDeFuego(std::string);
	virtual ~FabricaBolasDeFuego();
	void fabricar(Posicion*, int);
};

#endif /* FABRICABOLASDEFUEGO_H_ */
