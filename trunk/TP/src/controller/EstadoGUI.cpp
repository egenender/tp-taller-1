#include "EstadoGUI.h"


EstadoGUI EstadoGUI::instancia;

EstadoGUI::EstadoGUI() {
	solapaServidor = NULL;
	solapaCliente1 = NULL;
	solapaCliente2 = NULL;
	btnscrollarribaNiveles = btnscrollabajoNiveles =	btnscrollarribaPersonajes = btnscrollabajoPersonajes = btncrear = btnsolapacliente1 = btnsolapacliente2 = btnsolapaservidor = btnconectar = btnjugar = NULL;
	txtPuertoServidor = txtPuertoCliente = txtIP;
	barra = NULL;
	lblPuertoServidor = lblIP = lblPuertoCliente = lblnombrePersonaje = lblvelocidad = lblsalto = NULL;
	scrollPersonajes = scrollNiveles = NULL;
	animaciones = NULL;
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
	crearLabels();
	crearScroll();
	crearBarra();
	crearTxts();
	crearBtns();
	crearSolapaServidor();
	crearSolapaCliente();
	crearVistas();
}

void EstadoGUI::crearScroll(){
	scrollPersonajes = new ListaScrolleable(100,150, 200, 150);
//	scrollPersonajes->agregarElemento("Charmeleon");
//	scrollPersonajes->agregarElemento("Pikachu");
//	scrollPersonajes->agregarElemento("Mono Goku");
//	scrollPersonajes->agregarElemento("Gengar");
//	scrollPersonajes->agregarElemento("Primeape");

	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	gestor->setPosiblesNiveles();
	std::vector<string>* nombresNiveles= gestor->ObtenerPosiblesNiveles();

	scrollNiveles = new ListaScrolleable(100,150,200,120);

	for (unsigned int i = 0 ; i< nombresNiveles->size(); i++) {

		scrollNiveles->agregarElemento( nombresNiveles->at(i) );
	}


	animaciones = new Muestra(lblnombrePersonaje, lblvelocidad, lblsalto, 370, 180, 50,50);
	//animaciones->agregarVista(GestorConfiguraciones::getInstance()->ObtenerVistaManual());
}

void EstadoGUI::crearBtns(){

	btnsolapacliente1 = new Boton(25, 30, 206, 30, new ManejadorSolapa(solapaServidor, solapaCliente1));
	btnsolapaservidor = new Boton(235, 30, 206, 30, new ManejadorSolapa(solapaCliente1, solapaServidor));

	btnsolapacliente2 = new Boton(25,30,206,30, new ManejadorSolapa(solapaServidor, solapaCliente2) );
	btnconectar = new Boton(400,400,100,50, new ManejadorConectar(txtIP, txtPuertoCliente, barra, solapaCliente2, solapaCliente1, scrollPersonajes, animaciones) );
	btncrear = new Boton(400, 400, 100, 50, new ManejadorCrear(txtPuertoServidor, scrollNiveles, barra));
	btnscrollarribaPersonajes = new Boton(300, 150, 30,30, new ManejadorScroll(scrollPersonajes,ARRIBA,animaciones));
	btnscrollabajoPersonajes = new Boton(300, 270, 30,30, new ManejadorScroll(scrollPersonajes,ABAJO,animaciones));
	btnscrollarribaNiveles = new Boton(300, 150, 30,30, new ManejadorScroll(scrollNiveles,ARRIBA));
	btnscrollabajoNiveles = new Boton(300, 240, 30,30, new ManejadorScroll(scrollNiveles,ABAJO));

	btnjugar = new Boton(400, 400, 100, 50,  new ManejadorJugar(scrollPersonajes, barra));

	btnsolapacliente1->setearMensaje("Servidor");
	btnsolapacliente2->setearMensaje("Servidor");
	btnsolapaservidor->setearMensaje("Cliente");
	btnconectar->setearMensaje("Conectar");
	btncrear->setearMensaje("Crear");
	btnjugar->setearMensaje("Jugar");
	btnscrollarribaPersonajes->setearMensaje(" ");
	btnscrollabajoPersonajes->setearMensaje(" ");
	btnscrollarribaNiveles->setearMensaje(" ");
	btnscrollabajoNiveles->setearMensaje(" ");

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

	lblnombrePersonaje = new Label(100, 320, 200, 30);
	lblnombrePersonaje->setearMensaje("Aca deberia ir el nombre");
	lblvelocidad= new Label(100, 360, 200, 30);
	lblvelocidad->setearMensaje("Aca deberia ir la velocidad");
	lblsalto = new Label(100, 400, 200, 30);
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
	lista_insertar_ultimo(solapaServidor, scrollNiveles);
	lista_insertar_ultimo(solapaServidor, btnscrollarribaNiveles);
	lista_insertar_ultimo(solapaServidor, btnscrollabajoNiveles);
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
	lista_insertar_ultimo(solapaCliente2, scrollPersonajes);
	lista_insertar_ultimo(solapaCliente2, btnscrollarribaPersonajes);
	lista_insertar_ultimo(solapaCliente2, btnscrollabajoPersonajes);
	lista_insertar_ultimo(solapaCliente2, imgCliente);
	lista_insertar_ultimo(solapaCliente2, animaciones);
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
	scrollPersonajes->hacerInvisible();
	btnscrollarribaPersonajes->hacerInvisible();
	btnscrollabajoPersonajes->hacerInvisible();
	imgCliente->hacerInvisible();
	animaciones->hacerInvisible();
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

	vistaArribaPersonajes = new VistaBoton("src/gui/resources/flechaArriba.jpg",
			"src/gui/resources/flechaArribaClic.jpg");
	vistaAbajoPersonajes = new VistaBoton("src/gui/resources/flechaAbajo.jpg",
				"src/gui/resources/flechaAbajoClic.jpg");
	vistaArribaNiveles = new VistaBoton("src/gui/resources/flechaArriba.jpg",
				"src/gui/resources/flechaArribaClic.jpg");
	vistaAbajoNiveles = new VistaBoton("src/gui/resources/flechaAbajo.jpg",
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

	vistaScrollPersonajes = new VistaLista(3);
	scrollPersonajes->agregarObservador(vistaScrollPersonajes);
	vistaScrollNiveles = new VistaLista(5);
	scrollNiveles->agregarObservador(vistaScrollNiveles);

	btnsolapacliente1->agregarObservador(vistaBtnsolapacliente1);
	btnsolapacliente2->agregarObservador(vistaBtnsolapacliente2);
	btncrear->agregarObservador(vistaBtncrear);
	btnsolapaservidor->agregarObservador(vistaBtnsolapaservidor);
	btnconectar->agregarObservador(vistaBtnconectar);
	btnjugar->agregarObservador(vistaBtnjugar);
	btnscrollarribaPersonajes->agregarObservador(vistaArribaPersonajes);
	btnscrollabajoPersonajes->agregarObservador(vistaAbajoPersonajes);
	btnscrollarribaNiveles->agregarObservador(vistaArribaNiveles);
	btnscrollabajoNiveles->agregarObservador(vistaAbajoNiveles);

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
	fondo = new Superficie("src/gui/resources/fondo.bmp");

}


void EstadoGUI::actualizar(float delta){
	btnsolapacliente1->actualizar();
	btnsolapacliente2->actualizar();
	btncrear->actualizar();
	btnsolapaservidor->actualizar();
	btnconectar->actualizar();
	btnjugar->actualizar();
	btnscrollarribaPersonajes->actualizar();
	btnscrollabajoPersonajes->actualizar();
	btnscrollarribaNiveles->actualizar();
	btnscrollabajoNiveles->actualizar();
	scrollNiveles->actualizar();
	scrollPersonajes->actualizar();

	barra->actualizar();
	txtPuertoServidor->actualizar();
	txtPuertoCliente->actualizar();
	txtIP->actualizar();
	lblPuertoCliente->actualizar();
	lblPuertoServidor->actualizar();
	lblIP->actualizar();
	lblnombrePersonaje->actualizar();
	lblvelocidad->actualizar();
	lblsalto->actualizar();
	animaciones->actualizar();
}

void EstadoGUI::dibujar(SDL_Surface* display) {
	fondo->dibujar(display,0,0);
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
	vistaScrollPersonajes->dibujar(display);
	vistaScrollNiveles->dibujar(display);
	vistaArribaPersonajes->dibujar(display);
	vistaAbajoPersonajes->dibujar(display);
	vistaArribaNiveles->dibujar(display);
	vistaAbajoNiveles->dibujar(display);
	animaciones->dibujar(display);

}

void EstadoGUI::manejarEvento(SDL_Event* evento) {
	btnsolapacliente1->manejarEvento(evento);
	btnsolapacliente2->manejarEvento(evento);
	btnsolapaservidor->manejarEvento(evento);
	btnconectar->manejarEvento(evento);
	btnscrollarribaPersonajes->manejarEvento(evento);
	btnscrollabajoPersonajes->manejarEvento(evento);
	btnscrollarribaNiveles->manejarEvento(evento);
	btnscrollabajoNiveles->manejarEvento(evento);

	txtPuertoServidor->manejarEvento(evento);
	txtPuertoCliente->manejarEvento(evento);
	txtIP->manejarEvento(evento);


	btnjugar->manejarEvento(evento);

	if (ManejadorEstados::obtenerEstadoActual() == obtenerInstancia()){
		btncrear->manejarEvento(evento);
	}
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
	if (vistaBarra){
		delete (vistaBarra);
		vistaBarra = NULL;
	}
	if (vistaTxtPuertoServidor){
		delete (vistaTxtPuertoServidor);
		vistaTxtPuertoServidor = NULL;
	}
	if (vistaTxtPuertoCliente){
		delete (vistaTxtPuertoCliente);
		vistaTxtPuertoCliente = NULL;
	}
	if (vistaTxtIP){
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
	if(scrollPersonajes){
		delete (scrollPersonajes);
		scrollPersonajes = NULL;
	}
	if (vistaScrollPersonajes){
		delete (vistaScrollPersonajes);
		vistaScrollPersonajes = NULL;
	}
	if (scrollNiveles){
		delete(scrollNiveles);
		scrollNiveles= NULL;
	}
	if (vistaScrollNiveles){
		delete(vistaScrollNiveles);
		vistaScrollNiveles= NULL;
	}
	if (btnscrollarribaPersonajes){
		delete (btnscrollarribaPersonajes);
		btnscrollarribaPersonajes = NULL;
	}
	if (vistaArribaPersonajes){
		delete (vistaArribaPersonajes);
		vistaArribaPersonajes = NULL;
	}
	if (btnscrollabajoPersonajes){
		delete (btnscrollabajoPersonajes);
		btnscrollabajoPersonajes = NULL;
	}
	if (vistaAbajoPersonajes){
		delete (vistaAbajoPersonajes);
		vistaAbajoPersonajes = NULL;
	}
	if (btnscrollarribaNiveles){
		delete (btnscrollarribaNiveles);
		btnscrollarribaNiveles = NULL;
	}
	if (vistaArribaNiveles){
		delete (vistaArribaNiveles);
		vistaArribaNiveles = NULL;
	}
	if (btnscrollabajoNiveles){
		delete (btnscrollabajoNiveles);
		btnscrollabajoNiveles = NULL;
	}
	if (vistaAbajoNiveles){
		delete (vistaAbajoNiveles);
		vistaAbajoNiveles = NULL;
	}
	if (imgServidor){
		delete (imgServidor);
		imgServidor = NULL;
	}
	if (imgCliente){
		delete (imgCliente);
		imgCliente = NULL;
	}
	if (animaciones){
		delete (animaciones);
		animaciones = NULL;
	}
	if (fondo){
		delete (fondo);
		fondo = NULL;
	}
}


