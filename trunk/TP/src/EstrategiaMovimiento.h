#ifndef ESTRATEGIAMOVIMIENTO_H_
#define ESTRATEGIAMOVIMIENTO_H_

class EstrategiaMovimiento {

	private:
		int algo;

	public:
		//Deberia tener conocimiento del mundo, o algo asi
		EstrategiaMovimiento();
		virtual void actuar() = 0;

		//Faltaria ver de agregar el actuar(Evento) o algo por el estilo
};

#endif /* ESTRATEGIAMOVIMIENTO_H_ */
