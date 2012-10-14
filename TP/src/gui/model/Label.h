#ifndef LABEL_H_
#define LABEL_H_
#include "BarraEstado.h"

class Label : public BarraEstado{
public:
	Label(int x, int y, int ancho, int alto);
	virtual ~Label();
};

#endif /* LABEL_H_ */
