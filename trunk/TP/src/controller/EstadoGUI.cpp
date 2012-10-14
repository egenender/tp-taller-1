#include "EstadoGUI.h"


EstadoGUI EstadoGUI::instancia;

EstadoGUI::EstadoGUI() {
	solapaServidor = NULL;
	solapaCliente1 = NULL;
	solapaCliente2 = NULL;
	btncrear = btnsolapacliente1 = btnsolapacliente2 = btnsolapaservidor = btnconectar = btnjugar = NULL;
	txtPuertoServidor = txtPuertoCliente = txtIP;
	barra = NULL;

}

EstadoGUI::~EstadoGUI() {

}

EstadoGUI* EstadoGUI::obtenerInstancia() {
	return &instancia;
}

void EstadoGUI::iniciar() {
	solapaCliente1 = lista_crear();
	solapaCliente2 = lista_crear();
	solapaServidor = lista_crear();
	crearBtns();
	crearTxts();
	crearBarra();
	crearSolapaServidor();
	crearSolapaCliente();
	crearVistas();
}

void EstadoGUI::crearBtns(){

	btnsolapacliente1 = new Boton(100, 100, 50, 50, new ManejadorSolapa(solapaServidor, solapaCliente1));
	btnsolapaservidor = new Boton(200, 100, 50, 50, new ManejadorSolapa(solapaCliente1, solapaServidor));

	btnsolapacliente2 = new Boton(100,100,50,50, new ManejadorSolapa(solapaServidor, solapaCliente2) );
	btnconectar = new Boton(400,400,50,50, new ManejadorSolapa(solapaCliente2, solapaCliente1) );
	btncrear = new Boton(400, 400, 50, 50, new ManejadorEjemplo());
	btnjugar = new Boton(400, 400, 50, 50 , new ManejadorEjemplo());

	btnsolapacliente1->setearMensaje("Servidor");
	btnsolapacliente2->setearMensaje("Servidor");
	btnsolapaservidor->setearMensaje("Cliente");
	btnconectar->setearMensaje("Conectar");
	btncrear->setearMensaje("Crear");
	btnjugar->setearMensaje("Jugar");

}

void EstadoGUI::crearTxts(){
	txtPuertoServidor = new CuadroTexto(50,300,100,30,4,NUMEROS);
	txtPuertoCliente = new CuadroTexto(50,300,100,30,4,NUMEROS);
	txtIP = new CuadroTexto(50, 250, 300, 30, 15,NUMEROSYPUNTO);
}

void EstadoGUI::crearBarra(){
	barra = new BarraEstado(0,500,800,50);
	barra->setearMensaje("Iddle");
}

void EstadoGUI::crearSolapaServidor(){
	lista_insertar_ultimo(solapaServidor, txtPuertoServidor);
	lista_insertar_ultimo(solapaServidor, btncrear);
	lista_insertar_ultimo(solapaServidor, btnsolapaservidor);
}

void EstadoGUI::crearSolapaCliente(){
	lista_insertar_ultimo(solapaCliente1, txtIP);
	lista_insertar_ultimo(solapaCliente1, txtPuertoCliente);
	lista_insertar_ultimo(solapaCliente1, btnconectar);
	lista_insertar_ultimo(solapaCliente1, btnsolapacliente1);
	lista_insertar_ultimo(solapaCliente2, btnjugar);
	lista_insertar_ultimo(solapaCliente2, btnsolapacliente2);
	txtIP->hacerInvisible();
	txtPuertoCliente->hacerInvisible();
	btnconectar->hacerInvisible();
	btnsolapacliente1->hacerInvisible();
	btnjugar->hacerInvisible();
	btnsolapacliente2->hacerInvisible();
}

void EstadoGUI::crearVistas(){
	//VistaBoton *vistaBtncrear, *vistaBtnsolapacliente, *vistaBtnsolapaservidor, *vistaBtnconectar, *vistaBtnJugar;
	//VistaCuadroTexto *vistaTxtPuertoServidor, *vistaTxtPuertoCliente, *vistaTxtIP;
	//VistaBarraEstado *vistaBarra;

	vistaBtncrear = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnsolapacliente1 = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnsolapacliente2 = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnsolapaservidor = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnconectar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnjugar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");


	vistaBarra = new VistaBarraEstado();
	vistaTxtPuertoServidor = new VistaCuadroTexto();
	vistaTxtPuertoCliente = new VistaCuadroTexto();
	vistaTxtIP = new VistaCuadroTexto();

	btnsolapacliente1->agregarObservador(vistaBtnsolapacliente1);
	btnsolapacliente2->agregarObservador(vistaBtnsolapacliente2);
	btncrear->agregarObservador(vistaBtncrear);
	btnsolapaservidor->agregarObservador(vistaBtnsolapaservidor);
	btnconectar->agregarObservador(vistaBtnconectar);
	btnjugar->agregarObservador(vistaBtnjugar);

	barra->agregarObservador(vistaBarra);
	txtPuertoServidor->agregarObservador(vistaTxtPuertoServidor);
	txtPuertoCliente->agregarObservador(vistaTxtPuertoCliente);
	txtIP->agregarObservador(vistaTxtIP);
}


void EstadoGUI::actualizar(float delta){
	btnsolapacliente1->actualizar();
	btnsolapacliente2->actualizar();
	btncrear->actualizar();
	btnsolapaservidor->actualizar();
	btnconectar->actualizar();
	btnjugar->actualizar();

	barra->actualizar();
	txtPuertoServidor->actualizar();
	txtPuertoCliente->actualizar();
	txtIP->actualizar();

	// FIXME: ESTO NO SE SI SE DEBERIA HACER ACA!
	if(btnconectar->esClickeado()) {
		barra->setearMensaje("Todavia No Puedo Conectar");
	}else {
		barra->setearMensaje("Iddle");
	}

	if(btnjugar->esClickeado()) {
		ManejadorEstados::setearEstadoActual(ESTADO_JUEGO);
	}
}

void EstadoGUI::dibujar(SDL_Surface* display) {
	vistaBtncrear->dibujar(display);
	vistaBtnsolapacliente1->dibujar(display);
	vistaBtnsolapacliente2->dibujar(display);
	vistaBtnsolapaservidor->dibujar(display);
	vistaBtnconectar->dibujar(display);
	vistaBtnjugar->dibujar(display);
	vistaBarra->dibujar(display);
	vistaTxtPuertoServidor->dibujar(display);
	vistaTxtPuertoCliente->dibujar(display);
	vistaTxtIP->dibujar(display);
}

void EstadoGUI::manejarEvento(SDL_Event* evento) {
	btnsolapacliente1->manejarEvento(evento);
	btnsolapacliente2->manejarEvento(evento);
	btncrear->manejarEvento(evento);
	btnsolapaservidor->manejarEvento(evento);
	btnconectar->manejarEvento(evento);
	btnjugar->manejarEvento(evento);

	txtPuertoServidor->manejarEvento(evento);
	txtPuertoCliente->manejarEvento(evento);
	txtIP->manejarEvento(evento);
}

void EstadoGUI::terminar() {
	if (btnsolapacliente2){
		delete (btnsolapacliente2);
		btnsolapacliente2 = NULL;
	}
	if (btnsolapacliente1){
		delete (btnsolapacliente1);
		btnsolapacliente1 = NULL;
	}
	if (btncrear){
		delete (btncrear);
		btncrear = NULL;
	}
	if (btnconectar){
		delete (btnconectar);
		btnconectar = NULL;
	}
	if (btnjugar){
		delete (btnjugar);
		btnjugar = NULL;
	}
	if (btnsolapaservidor){
		delete (btnsolapaservidor);
		btnsolapaservidor = NULL;
	}
	if (barra){
		delete (barra);
		barra = NULL;
	}
	if (txtPuertoServidor){
		delete (txtPuertoServidor);
		txtPuertoServidor = NULL;
	}
	if (txtPuertoCliente){
		delete (txtPuertoCliente);
		txtPuertoCliente = NULL;
	}
	if (txtIP){
		delete (txtIP);
		txtIP = NULL;
	}

	if (vistaBtncrear){
		delete (vistaBtncrear);
		vistaBtncrear = NULL;
	}
	if (vistaBtnsolapacliente1){
		delete (vistaBtnsolapacliente1);
		vistaBtnsolapacliente1 = NULL;
	}
	if (vistaBtnsolapacliente2){
		delete (vistaBtnsolapacliente2);
		vistaBtnsolapacliente2 = NULL;
	}
	if (vistaBtnsolapaservidor){
		delete (vistaBtnsolapaservidor);
		vistaBtnsolapaservidor = NULL;
	}
	if (vistaBtnconectar){
		delete (vistaBtnconectar);
		vistaBtnconectar = NULL;
	}
	if (vistaBtnjugar){
		delete (vistaBtnjugar);
		vistaBtnjugar = NULL;
	}
	if (!vistaBarra){
		delete (vistaBarra);
		vistaBarra = NULL;
	}
	if (!vistaTxtPuertoServidor){
		delete (vistaTxtPuertoServidor);
		vistaTxtPuertoServidor = NULL;
	}
	if (!vistaTxtPuertoCliente){
		delete (vistaTxtPuertoCliente);
		vistaTxtPuertoCliente = NULL;
	}
	if (!vistaTxtIP){
		delete (vistaTxtIP);
		vistaTxtIP = NULL;
	}
	if (solapaServidor){
		lista_destruir(solapaServidor,NULL);
		solapaServidor = NULL;
	}
	if (solapaCliente1){
		lista_destruir(solapaCliente1,NULL);
		solapaCliente1 = NULL;
	}
	if (solapaCliente2){
		lista_destruir(solapaCliente2,NULL);
		solapaCliente2 = NULL;
	}
}

