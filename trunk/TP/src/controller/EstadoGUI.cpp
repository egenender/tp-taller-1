#include "EstadoGUI.h"


EstadoGUI EstadoGUI::instancia;

EstadoGUI::EstadoGUI() {
	solapaServidor = NULL;
	solapaCliente1 = NULL;
	solapaCliente2 = NULL;
	btnscrollarriba = btnscrollabajo = btncrear = btnsolapacliente1 = btnsolapacliente2 = btnsolapaservidor = btnconectar = btnjugar = NULL;
	txtPuertoServidor = txtPuertoCliente = txtIP;
	barra = NULL;
	lblPuertoServidor = lblIP = lblPuertoCliente = lblnombrePersonaje = lblvelocidad = lblsalto = NULL;
	scroll = NULL;
}

EstadoGUI::~EstadoGUI() {

}

EstadoGUI* EstadoGUI::obtenerInstancia() {
	return &instancia;
}

void EstadoGUI::iniciar() {

	// TODO: aca se deberia configurar la ventana. Habria que hacerla singleton!
	// Ventana::obtenerInstancia()->volverALasDimensionesDeCreacion();


	solapaCliente1 = lista_crear();
	solapaCliente2 = lista_crear();
	solapaServidor = lista_crear();
	crearScroll();
	crearBtns();
	crearTxts();
	crearBarra();
	crearLabels();
	crearSolapaServidor();
	crearSolapaCliente();
	crearVistas();
}

void EstadoGUI::crearScroll(){
	scroll = new ListaScrolleable(100,200, 200, 150);
	scroll->agregarElemento("Charmeleon");
	scroll->agregarElemento("Pikachu");
	scroll->agregarElemento("Mono Goku");
	scroll->agregarElemento("Gengar");
	scroll->agregarElemento("Primeape");
}

void EstadoGUI::crearBtns(){

	btnsolapacliente1 = new Boton(25, 30, 206, 30, new ManejadorSolapa(solapaServidor, solapaCliente1));
	btnsolapaservidor = new Boton(235, 30, 206, 30, new ManejadorSolapa(solapaCliente1, solapaServidor));

	btnsolapacliente2 = new Boton(25,30,206,30, new ManejadorSolapa(solapaServidor, solapaCliente2) );
	btnconectar = new Boton(400,400,100,50, new ManejadorSolapa(solapaCliente2, solapaCliente1) );
	btncrear = new Boton(400, 400, 100, 50, new ManejadorEjemplo());
	btnjugar = new Boton(400, 400, 100, 50 , new ManejadorEjemplo());
	btnscrollarriba = new Boton(300, 200, 30,30, new ManejadorScroll(scroll,ARRIBA));
	btnscrollabajo = new Boton(300, 320, 30,30, new ManejadorScroll(scroll,ABAJO));

	btnsolapacliente1->setearMensaje("Servidor");
	btnsolapacliente2->setearMensaje("Servidor");
	btnsolapaservidor->setearMensaje("Cliente");
	btnconectar->setearMensaje("Conectar");
	btncrear->setearMensaje("Crear");
	btnjugar->setearMensaje("Jugar");
	btnscrollarriba->setearMensaje(" ");
	btnscrollabajo->setearMensaje(" ");

}

void EstadoGUI::crearTxts(){
	txtPuertoServidor = new CuadroTexto(100,300,100,30,4,NUMEROS);
	txtPuertoCliente = new CuadroTexto(100,300,100,30,4,NUMEROS);
	txtIP = new CuadroTexto(100, 250, 300, 30, 15,NUMEROSYPUNTO);
}

void EstadoGUI::crearBarra(){
	barra = new BarraEstado(15,490,611,30);
	barra->setearMensaje("Iddle");
}

void EstadoGUI::crearLabels(){
	//Label *lblPuertoServidor, *lblIP, *lblPuertoCliente, *lblnombrePersonaje, *lblvelocidad, *lblsalto;
	lblPuertoServidor = new Label(20,300,80, 30);
	lblPuertoServidor->setearMensaje("Puerto:");
	lblIP = new Label(20,250, 80,30);
	lblIP->setearMensaje("IP:");
	lblPuertoCliente = new Label(20,300,80,30);
	lblPuertoCliente->setearMensaje("Puerto:");

	lblnombrePersonaje = new Label(80, 370, 200, 30);
	lblnombrePersonaje->setearMensaje("Aca deberia ir el nombre");
	lblvelocidad= new Label(80, 410, 200, 30);
	lblvelocidad->setearMensaje("Aca deberia ir la velocidad");
	lblsalto = new Label(80, 450, 200, 30);
	lblsalto->setearMensaje("Aca deberia ir el salto");

	imgCliente = new ImagenGUI("src/gui/resources/pestanialbl.bmp", "Cliente", 230, 40, 206, 50);
	imgServidor = new ImagenGUI("src/gui/resources/pestanialbl.bmp", "Servidor", 25,40, 206, 50);
}

void EstadoGUI::crearSolapaServidor(){
	lista_insertar_ultimo(solapaServidor, txtPuertoServidor);
	lista_insertar_ultimo(solapaServidor, btncrear);
	lista_insertar_ultimo(solapaServidor, btnsolapaservidor);
	lista_insertar_ultimo(solapaServidor, lblPuertoServidor);
	lista_insertar_ultimo(solapaServidor, imgServidor);
}

void EstadoGUI::crearSolapaCliente(){
	lista_insertar_ultimo(solapaCliente1, txtIP);
	lista_insertar_ultimo(solapaCliente1, txtPuertoCliente);
	lista_insertar_ultimo(solapaCliente1, btnconectar);
	lista_insertar_ultimo(solapaCliente1, btnsolapacliente1);
	lista_insertar_ultimo(solapaCliente1, lblPuertoCliente);
	lista_insertar_ultimo(solapaCliente1, lblIP);
	lista_insertar_ultimo(solapaCliente1, imgCliente);
	lista_insertar_ultimo(solapaCliente2, btnjugar);
	lista_insertar_ultimo(solapaCliente2, btnsolapacliente2);
	lista_insertar_ultimo(solapaCliente2, lblnombrePersonaje);
	lista_insertar_ultimo(solapaCliente2, lblvelocidad);
	lista_insertar_ultimo(solapaCliente2, lblsalto);
	lista_insertar_ultimo(solapaCliente2, scroll);
	lista_insertar_ultimo(solapaCliente2, btnscrollarriba);
	lista_insertar_ultimo(solapaCliente2, btnscrollabajo);
	lista_insertar_ultimo(solapaCliente2, imgCliente);
	txtIP->hacerInvisible();
	txtPuertoCliente->hacerInvisible();
	btnconectar->hacerInvisible();
	btnsolapacliente1->hacerInvisible();
	btnjugar->hacerInvisible();
	btnsolapacliente2->hacerInvisible();
	lblIP->hacerInvisible();
	lblPuertoCliente->hacerInvisible();
	lblvelocidad->hacerInvisible();
	lblsalto->hacerInvisible();
	lblnombrePersonaje->hacerInvisible();
	scroll->hacerInvisible();
	btnscrollarriba->hacerInvisible();
	btnscrollabajo->hacerInvisible();
	imgCliente->hacerInvisible();
}

void EstadoGUI::crearVistas(){
	//VistaBoton *vistaBtncrear, *vistaBtnsolapacliente, *vistaBtnsolapaservidor, *vistaBtnconectar, *vistaBtnJugar;
	//VistaCuadroTexto *vistaTxtPuertoServidor, *vistaTxtPuertoCliente, *vistaTxtIP;
	//VistaBarraEstado *vistaBarra;

	vistaBtncrear = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnsolapacliente1 = new VistaBoton("src/gui/resources/pestania.bmp",
			"src/gui/resources/pestania.bmp");
	vistaBtnsolapacliente2 = new VistaBoton("src/gui/resources/pestania.bmp",
				"src/gui/resources/pestania.bmp");
	vistaBtnsolapaservidor = new VistaBoton("src/gui/resources/pestania.bmp",
			"src/gui/resources/pestania.bmp");
	vistaBtnconectar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");
	vistaBtnjugar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");

	vistaarriba = new VistaBoton("src/gui/resources/flechaArriba.jpg",
			"src/gui/resources/flechaArribaClic.jpg");
	vistaabajo = new VistaBoton("src/gui/resources/flechaAbajo.jpg",
				"src/gui/resources/flechaAbajoClic.jpg");

	vistaBarra = new VistaBarraEstado();
	vistaTxtPuertoServidor = new VistaCuadroTexto();
	vistaTxtPuertoCliente = new VistaCuadroTexto();
	vistaTxtIP = new VistaCuadroTexto();
	vistalblpuertoservidor = new VistaLabel();
	vistalblpuertocliente = new VistaLabel();
	vistalblIP = new VistaLabel();
	vistalblnombre = new VistaLabel();
	vistalblvelocidad = new VistaLabel();
	vistalblsalto = new VistaLabel();

	vistaScroll = new VistaLista(3);
	scroll->agregarObservador(vistaScroll);

	btnsolapacliente1->agregarObservador(vistaBtnsolapacliente1);
	btnsolapacliente2->agregarObservador(vistaBtnsolapacliente2);
	btncrear->agregarObservador(vistaBtncrear);
	btnsolapaservidor->agregarObservador(vistaBtnsolapaservidor);
	btnconectar->agregarObservador(vistaBtnconectar);
	btnjugar->agregarObservador(vistaBtnjugar);
	btnscrollarriba->agregarObservador(vistaarriba);
	btnscrollabajo->agregarObservador(vistaabajo);

	barra->agregarObservador(vistaBarra);
	txtPuertoServidor->agregarObservador(vistaTxtPuertoServidor);
	txtPuertoCliente->agregarObservador(vistaTxtPuertoCliente);
	txtIP->agregarObservador(vistaTxtIP);

	lblPuertoServidor->agregarObservador(vistalblpuertoservidor);
	lblPuertoCliente->agregarObservador(vistalblpuertocliente);
	lblIP->agregarObservador(vistalblIP);
	lblnombrePersonaje->agregarObservador(vistalblnombre);
	lblvelocidad->agregarObservador(vistalblvelocidad);
	lblsalto->agregarObservador(vistalblsalto);

	fondoPestania = new Superficie("src/gui/resources/fondoPestanias.bmp");
	fondoPestania->transparencia(255,0,255);
}


void EstadoGUI::actualizar(float delta){
	btnsolapacliente1->actualizar();
	btnsolapacliente2->actualizar();
	btncrear->actualizar();
	btnsolapaservidor->actualizar();
	btnconectar->actualizar();
	btnjugar->actualizar();
	btnscrollarriba->actualizar();
	btnscrollabajo->actualizar();
	scroll->actualizar();

	barra->actualizar();
	txtPuertoServidor->actualizar();
	txtPuertoCliente->actualizar();
	txtIP->actualizar();
	lblPuertoCliente->actualizar();
	lblPuertoServidor->actualizar();
	lblIP->actualizar();
	lblnombrePersonaje->setearMensaje("Nombre: "+scroll->obtenerSeleccionado());
	lblnombrePersonaje->actualizar();
	lblvelocidad->actualizar();
	lblsalto->actualizar();


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
	fondoPestania->dibujar(display,10,40);
	imgCliente->dibujar(display);
	imgServidor->dibujar(display);
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
	vistalblnombre->dibujar(display);
	vistalblvelocidad->dibujar(display);
	vistalblsalto->dibujar(display);
	vistalblIP->dibujar(display);
	vistalblpuertoservidor->dibujar(display);
	vistalblpuertocliente->dibujar(display);
	vistaScroll->dibujar(display);
	vistaarriba->dibujar(display);
	vistaabajo->dibujar(display);


}

void EstadoGUI::manejarEvento(SDL_Event* evento) {
	btnsolapacliente1->manejarEvento(evento);
	btnsolapacliente2->manejarEvento(evento);
	btncrear->manejarEvento(evento);
	btnsolapaservidor->manejarEvento(evento);
	btnconectar->manejarEvento(evento);
	btnjugar->manejarEvento(evento);
	btnscrollarriba->manejarEvento(evento);
	btnscrollabajo->manejarEvento(evento);

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
	if (lblPuertoCliente){
		delete (lblPuertoCliente);
		lblPuertoCliente = NULL;
	}
	if (lblPuertoServidor){
		delete (lblPuertoServidor);
		lblPuertoServidor = NULL;
	}
	if (lblIP){
		delete (lblIP);
		lblIP = NULL;
	}
	if (lblnombrePersonaje){
		delete (lblnombrePersonaje);
		lblnombrePersonaje = NULL;
	}
	if (lblvelocidad){
		delete (lblvelocidad);
		lblvelocidad = NULL;
	}
	if (lblsalto){
		delete (lblsalto);
		lblsalto = NULL;
	}
	if (vistalblpuertocliente){
			delete (vistalblpuertocliente);
			vistalblpuertocliente = NULL;
	}
	if (vistalblpuertoservidor){
		delete (vistalblpuertoservidor);
		vistalblpuertoservidor = NULL;
	}
	if (vistalblIP){
		delete (vistalblIP);
		vistalblIP = NULL;
	}
	if (vistalblnombre){
		delete (vistalblnombre);
		vistalblnombre = NULL;
	}
	if (vistalblvelocidad){
		delete (vistalblvelocidad);
		vistalblvelocidad = NULL;
	}
	if (vistalblsalto){
		delete (vistalblsalto);
		vistalblsalto = NULL;
	}
	if(scroll){
		delete (scroll);
		scroll = NULL;
	}
	if (vistaScroll){
		delete (vistaScroll);
		vistaScroll = NULL;
	}
	if (btnscrollarriba){
		delete (btnscrollarriba);
		btnscrollarriba = NULL;
	}
	if (vistaarriba){
		delete (vistaarriba);
		vistaarriba = NULL;
	}
	if (btnscrollabajo){
		delete (btnscrollabajo);
		btnscrollabajo = NULL;
	}
	if (vistaabajo){
		delete (vistaabajo);
		vistaabajo = NULL;
	}
	if (imgServidor){
		delete (imgServidor);
		imgServidor = NULL;
	}
	if (imgCliente){
			delete (imgCliente);
			imgCliente = NULL;
		}
}

