#ifndef ACTUALIZABLE_H_
#define ACTUALIZABLE_H_

class Actualizable {
public:
	Actualizable();
	virtual ~Actualizable();
	virtual void actualizar(float delta)=0;
};

#endif /* ACTUALIZABLE_H_ */
