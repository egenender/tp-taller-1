#include "HojaSprites.h"
#include "VistaProtagonista.h"

VistaProtagonista::VistaProtagonista(/*Observable* protagonista,*/ Animacion* caminar, Animacion* quieto, Animacion* saltar/*, BarraEstado* labarra*/) {
	//barra = labarra;
	//primeraVez = true;
	invisible = false;
	Animacion* caminaDer = caminar;
	caminaDer->transparencia(255,0,255);
	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	Animacion* quietoDer=quieto;
	quietoDer->transparencia(255,0,255);
	Animacion* quietoIzq = quietoDer->voltear(HORIZONTALMENTE);

	Animacion* saltandoDer = saltar;
	saltandoDer->transparencia(255,0,255);
	Animacion* saltandoIzq = saltandoDer->voltear(HORIZONTALMENTE);


	Animacion* subiendoQ = caminaDer->voltear(HORIZONTALMENTE);
	subiendoQ->transparencia(255,0,255);
	Animacion* subiendoM = caminaIzq->voltear(HORIZONTALMENTE);
	subiendoM->transparencia(255,0,255);

	animaciones->insert(pair<int, Animacion*>(QUIETODER, quietoDer));
	animaciones->insert(pair<int, Animacion*>(QUIETOIZQ, quietoIzq));
	animaciones->insert(pair<int, Animacion*>(CAMINANDODER,caminaDer));
	animaciones->insert(pair<int, Animacion*>(CAMINANDOIZQ,caminaIzq));
	animaciones->insert(pair<int, Animacion*>(SALTANDODER, saltandoDer));
	animaciones->insert(pair<int, Animacion*>(SALTANDOIZQ, saltandoIzq));
	animaciones->insert(pair<int, Animacion*>(SUBIENDOQUIETO, subiendoQ));
	animaciones->insert(pair<int, Animacion*>(SUBIENDOMOVIMIENTO, subiendoM));


	//FIXME: Le hardcode para que se pueda ver la evolucion:
	Animacion* anim = new Animacion (new HojaSprites("src/resources/cuerpos/Charmeleon/charmeleonQuieto.bmp", 65, 73));
	anim->transparencia(255,0,255);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + QUIETODER, anim));
	anim = anim->voltear(HORIZONTALMENTE);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + QUIETOIZQ, anim));

	anim = new Animacion (new HojaSprites("src/resources/cuerpos/Charmeleon/charmeleonMovimiento.bmp", 65, 73));
	anim->transparencia(255,0,255);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + CAMINANDODER, anim));
	anim = anim->voltear(HORIZONTALMENTE);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + CAMINANDOIZQ, anim));

	anim = new Animacion (new HojaSprites("src/resources/cuerpos/Charmeleon/charmeleonMovimiento.bmp", 65, 73));
	anim->transparencia(255,0,255);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + SALTANDODER, anim));
	anim = anim->voltear(HORIZONTALMENTE);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + SALTANDOIZQ, anim));

	anim = new Animacion (new HojaSprites("src/resources/cuerpos/Charmeleon/charmeleonMovimiento.bmp", 65, 73));
	anim->transparencia(255,0,255);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + SUBIENDOQUIETO, anim));
	anim = anim->voltear(HORIZONTALMENTE);
	animaciones->insert(pair<int, Animacion*>(EVOLUCION + SUBIENDOMOVIMIENTO, anim));
}

void VistaProtagonista::actualizar(Observable* observable) {
	int estado = observable->obtenerEstado();
	if (estado == MUERTO){
		pararDeDibujar = true;
		return;
	}
	pararDeDibujar = false;

	posicionDibujar = observable->obtenerPosicion();
	animacionActual = animaciones->at(estado);
	invisible = !invisible && observable->estaInvencible();
}

void VistaProtagonista::reiniciar(){

}

VistaProtagonista::~VistaProtagonista() {}

bool VistaProtagonista::dibujar(SDL_Surface* display, int xCamara, int yCamara){
	if (!invisible) return VistaAnimada::dibujar(display, xCamara, yCamara);
	return true;
}
