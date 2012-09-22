/*
 * Textura.h
 *
 *  Created on: 22/09/2012
 *      Author: nicolas
 */

#ifndef TEXTURA_H_
#define TEXTURA_H_

#include "Superficie.h"

class Textura : private Superficie {
private:
	int Rfond, Gfond, Bfond;

public:
	Textura(string archivo, int Rtext, int Gtext, int Btext, int Rfond, int Gfond, int Bfond);
	Superficie* aplicarTextura(Superficie* superficie);
	~Textura();
};


#endif /* TEXTURA_H_ */
