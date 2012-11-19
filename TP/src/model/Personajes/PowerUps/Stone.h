#ifndef STONE_H_
#define STONE_H_
#include "PowerUp.h"

class Stone : public PowerUp{
public:
	Stone(const char*, Area*, int);
	virtual ~Stone();
	void chocarConManual(Manual*);
	unsigned int obtenerTipo();
};

#endif /* STONE_H_ */
