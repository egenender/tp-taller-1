/*
 * GestorConfiguraciones.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GestorConfiguraciones.h"
#include "Estatico.h"
#include "Log.h"
#include <sstream>

#define VEL_PERSONAJE 15
#define MARGEN_SCROLL 80
#define ANCHO_PANTALLA 800
#define ALTO_PANTALLA 600
#define ANCHO_PANTALLA_MINIMO 200
#define ALTO_PANTALLA_MINIMO 200
#define ANCHO_NIVEL_MINIMO 200
#define ALTO_NIVEL_MINIMO 200
#define RUTA_FONDO "src/fondoGrande.png"
#define ANCHO_PERSONAJE 65
#define ALTO_PERSONAJE 73
#define RUTA_ACTIVA "src/charmeleonMovimiento.bmp"
#define RUTA_PASIVA "src/charmeleonQuieto.bmp"
#define PERIODO_PERSONAJE 15
#define ANCHO_NIVEL 1200
#define ALTO_NIVEL 600
#define POS_DEFECTO 60
#define TIPO_DEFECTO "defe"
#define ANCHO_OBJETO 40
#define ALTO_OBJETO 80
#define POS_DEFECTO_OBJ 80
#define TEXTURA_DEFECTO "src/texturaGrande.jpg"


// Puntero estatico para controlar la instanciacion.
GestorConfiguraciones GestorConfiguraciones::instancia;

GestorConfiguraciones* GestorConfiguraciones::getInstance() {
   return &instancia;
}

GestorConfiguraciones::GestorConfiguraciones (){
	vel_personaje=0;
	margen_scroll=0;
	configPantalla=0;
	tiposPersonajes=new mapa_per();
	texturas=new mapa_tex();

	YAML::Node nodo,nodoDef;

	try{
		std::ifstream fin("src/archivoYaml.yaml");
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
		Log::getInstance()->writeToLogFile("INFO","PARSER: El parser de la libreria YAML corre apropiadamente");
	} catch(YAML::ParserException &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El archivo YAML no tiene el formato correcto, se parsea archivo default");
		std::ifstream fin("src/defecto.yaml");
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);

	}
	std::ifstream finDef("src/defecto.yaml");
	YAML::Parser parserDef(finDef);
	parserDef.GetNextDocument(nodoDef);


	try{
		const YAML::Node& nodoRaiz = nodo["juego"];
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se abrio el Archivo YAML");
	}catch(YAML::Exception &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo Juego, se cargan configuraciones por defecto");
		std::ifstream fin("src/defecto.yaml");
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
	}

	const YAML::Node& nodoRaiz = nodo["juego"];
	const YAML::Node& nodoRaizDef = nodoDef["juego"];

	try{
		nodoRaiz["parametros"]["vel_personaje"] >> vel_personaje;
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se carga vel_personaje");
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo vel_personaje, se carga por defecto");
		vel_personaje = VEL_PERSONAJE;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo vel_personaje, se carga por defecto");
			vel_personaje = VEL_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: La vel_personaje no toma valor valido, se carga por defecto");
			vel_personaje = VEL_PERSONAJE;
	}

	if (vel_personaje==0){
		vel_personaje = 1;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: La vel_personaje toma valor nulo, se carga velocidad de 1");
	}

	try{
		configPantalla=CargarConfiguracionPantalla(nodoRaiz["pantalla"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de Pantalla");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo pantalla, se carga por defecto");
		configPantalla=CargarConfiguracionPantalla(ANCHO_PANTALLA,ALTO_PANTALLA,RUTA_FONDO);
	}

	try{
			CargarTiposPersonajes(nodoRaiz["tiposPersonaje"] , nodoRaizDef["tiposPersonaje"]["protagonista"]);
			Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de tiposPersonaje");
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tiposPersonaje, se cargan por defecto");
			CargarTiposPersonajes(nodoRaizDef["tiposPersonaje"], nodoRaizDef["tiposPersonaje"]);
		}

	try{
		CargarTexturas(nodoRaiz["texturas"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de texturas");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo texturas, se cargan por defecto");
		CargarTexturas(nodoRaizDef["texturas"]);
	}

	configNivel = new ConfiguracionNivel();
	try{
		CargarConfiguracionNivel(nodoRaiz["nivel"],nodoRaizDef["nivel"]["personajes"],nodoRaizDef["nivel"]["plataformas"],nodoRaizDef["nivel"]["escaleras"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de Nivel");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo nivel, se carga enteramente por defecto");
		CargarConfiguracionNivel(nodoRaizDef["nivel"],nodoRaizDef["nivel"]["personajes"],nodoRaizDef["nivel"]["plataformas"],nodoRaizDef["nivel"]["escaleras"]);
	}
	Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones del Nivel");


	if ((configPantalla->alto) > (configNivel->alto)){
		configPantalla->alto=configNivel->alto;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto de la pantalla supera al del nivel, se carga alto maximo valido");
	}
	if ((configPantalla->ancho) > (configNivel->ancho)){
		configPantalla->ancho=configNivel->ancho;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho de la pantalla supera al del nivel, se carga alto maximo valido");
	}


	try{
		nodoRaiz["parametros"]["margen_scroll"] >> margen_scroll;
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se carga margen_scroll");
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo margen_scroll, se carga por defecto");
		margen_scroll = MARGEN_SCROLL;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo margen_scroll, se carga por defecto");
		margen_scroll = MARGEN_SCROLL;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El margen_scroll no toma valor valido, se carga por defecto");
		margen_scroll = MARGEN_SCROLL;
	}

	if (margen_scroll<=0 || margen_scroll*2 >= configNivel->ancho ){
		margen_scroll=(configNivel->ancho)/2;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El margen_scroll no toma valor valido dentro de las dimensiones del nivel, se carga uno valido");
	}



}

void GestorConfiguraciones::CargarConfiguracionNivel(const YAML::Node& nodo, const YAML::Node& defPersonajes, const YAML::Node& defPlataformas, const YAML::Node& defEscaleras){

	try{
		nodo["ancho"] >> configNivel->ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo ancho dentro del nivel, se carga por defecto");
		configNivel->ancho = ANCHO_NIVEL;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho no toma valor valido, se carga por defecto");
		configNivel->ancho = ANCHO_NIVEL;
	}

	if ((configNivel->ancho)< ANCHO_NIVEL_MINIMO){
		configNivel->ancho=ANCHO_NIVEL_MINIMO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho del nivel toma valor muy chico o negativo, se carga minimo valido");
	}

	try{
		nodo["alto"] >> configNivel->alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo alto dentro del nivel, se carga por defecto");
		configNivel->alto = ALTO_NIVEL;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor valido, se carga por defecto");
		configNivel->alto = ALTO_NIVEL;
	}

	if ((configNivel->alto)< ALTO_NIVEL_MINIMO){
		configNivel->alto=ALTO_NIVEL_MINIMO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto del nivel toma valor muy chico o negativo, se carga minimo valido");
	}

	try{
		CargarEstaticosNivel(nodo["plataformas"], false, true);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de las plataformas del nivel");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo plataformas, se cargan por defecto");
		CargarEstaticosNivel(defPlataformas, false, true);
	}

	try{
		CargarEstaticosNivel(nodo["escaleras"], true, false);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de las escaleras del nivel");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo escaleras, se cargan por defecto");
		CargarEstaticosNivel(defEscaleras, true, false);
	}

	try{
			CargarPersonajesNivel(nodo["personajes"]);
			Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de los personajes del nivel");
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo personajes, se cargan por defecto");
			CargarPersonajesNivel(defPersonajes);
		}

}

void GestorConfiguraciones::CargarEstaticosNivel(const YAML::Node& nodo, bool escalar, bool cortar){
	int posX,posY;
	int ancho, alto;
	std::string nombreTex;
	Estatico* estatico;
	VistaImagen* vista;
	Superficie* sup;

	for(unsigned i=0;i<nodo.size();i++) {
		try{
			nodo[i]["ancho"] >> ancho;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo ancho dentro del objeto, se carga por defecto");
			ancho = ANCHO_OBJETO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho no toma valor valido, se carga por defecto");
			ancho = ANCHO_OBJETO;
		}

		try{
			nodo[i]["alto"] >> alto;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo alto dentro del objeto, se carga por defecto");
			alto = ALTO_OBJETO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor valido, se carga por defecto");
			alto = ALTO_OBJETO;
		}

		try{
			nodo[i]["x"] >> posX;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo x dentro del objeto, se carga por defecto");
			posX = POS_DEFECTO_OBJ;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x del objeto no toma valor valido, se carga por defecto");
			posX = POS_DEFECTO_OBJ;
		}
		if (posX<0 || posX>= configNivel->ancho){
			posX=POS_DEFECTO_OBJ;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x del objeto no toma valor valido, se carga por defecto");
		}

		try{
			nodo[i]["y"] >> posY;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo y dentro del objeto, se carga por defecto");
			posY = POS_DEFECTO_OBJ;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y del objeto no toma valor valido, se carga por defecto");
			posY = POS_DEFECTO_OBJ;
		}
		if (posY<0 || posY>= configNivel->alto){
			posY=POS_DEFECTO_OBJ;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y del objeto no toma valor valido, se carga por defecto");
		}

		try{
			nodo[i]["textura"] >> nombreTex;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo textura del objeto, se carga por defecto");
			nombreTex = TIPO_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No se especifica textura del objeto, se carga por defecto");
			nombreTex = TIPO_DEFECTO;
		}catch(YAML::BadDereference &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo textura del objeto, se carga por defecto");
			nombreTex = TIPO_DEFECTO;
		}

		estatico = new Estatico(nombreTex.c_str(), new Area(ancho,alto,new Posicion(posX,posY) ) );
		configNivel->cuerpos.push_back(estatico);

		std::string rutaImagen;
		try{
			rutaImagen = texturas->at(nombreTex);
		}catch(std::out_of_range &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No habia definicion del tipo de textura, se carga una definicion por defecto");
			rutaImagen = TEXTURA_DEFECTO;
		}

		_IO_FILE* archiv=fopen(rutaImagen.c_str(),"r");
		if (!(archiv)){
			rutaImagen=TEXTURA_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de imagen de textura invalida, se carga una ruta por defecto");
		}
		else
			fclose(archiv);

		if (cortar)
			sup =  new Superficie( rutaImagen , 0 , 0 , ancho, alto);
		else
			sup =  new Superficie( rutaImagen );

		if (escalar)
			sup->escala(ancho,alto);

		vista = new VistaImagen( sup );
		estatico->agregarObservador(vista);
		configNivel->vistas.push_back(vista);
	}
}

void GestorConfiguraciones::CargarPersonajesNivel(const YAML::Node& personajes){

	std::string tipo;
	int posX,posY;
	Automatico* automatico;
	Cuerpo* cuerpo;
	VistaCuerpo* vistaCuerpo;
	configNivel->manual = NULL;
	for(unsigned i=0;i<personajes.size();i++) {
		try{
			personajes[i]["tipo"] >> tipo;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tipo del personaje, se carga por defecto");
			tipo = TIPO_DEFECTO;
		}

		try{
			personajes[i]["x"] >> posX;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo x dentro del personaje, se carga por defecto");
			posX = POS_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x no toma valor valido, se carga por defecto");
			posX = POS_DEFECTO;
		}
		if (posX<0 || posX>= configNivel->ancho){
			posX=POS_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x del personaje no toma valor valido, se carga por defecto");
		}

		try{
			personajes[i]["y"] >> posY;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo y dentro del personaje, se carga por defecto");
			posY = POS_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y no toma valor valido, se carga por defecto");
			posY = POS_DEFECTO;
		}
		if (posY<0 || posY>=configNivel->alto){
			posY=POS_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y del personaje no toma valor valido, se carga por defecto");
		}

		int x,y;
		int ancho, alto;
		if (strcmp(tipo.c_str(),"protagonista")==0){
			//ya asegure que hay nodo protagonista, entonces esto anda siempre
			ancho = tiposPersonajes->at(tipo)->ancho;
			alto = tiposPersonajes->at(tipo)->alto;
			//el posX posY indica el punto inferior central del personaje (consigna)
			x = posX - ( ancho/2 );
			y = posY - alto;
			configNivel->manual = tiposPersonajes->at(tipo)->CrearManual(tiposPersonajes->at(tipo)->nombre, x, y, vel_personaje);
			cuerpo = configNivel->manual;
			configNivel->vistaManual = new VistaProtagonista(configNivel->manual, tiposPersonajes->at(tipo)->animacionActiva , tiposPersonajes->at(tipo)->animacionPasiva);
			vistaCuerpo = configNivel->vistaManual;
		}else{
			//debo asegurarme de que pasen un tipo de personaje que ya exista:
			try{
				ancho = tiposPersonajes->at(tipo)->ancho;
				alto = tiposPersonajes->at(tipo)->alto;
				//el posX posY indica el punto inferior central del personaje (consigna)
				x = posX - ( ancho/2 );
				y = posY - alto;
				automatico = tiposPersonajes->at(tipo)->CrearAutomatico(tiposPersonajes->at(tipo)->nombre, x, y);
			}catch(std::out_of_range &e){
				//si no hay, por defecto
				automatico = CrearAutomaticoDefecto(tipo.c_str(), posX, posY);
				Log::getInstance()->writeToLogFile("ERROR","PARSER: No habia deficion del tipo de personaje, se carga una definicion por defecto");
			}
			cuerpo = automatico;
			try{
				vistaCuerpo = new VistaAutomatico(automatico, tiposPersonajes->at(tipo)->animacionActiva , tiposPersonajes->at(tipo)->animacionPasiva, tiposPersonajes->at(tipo)->periodo);
			}catch(std::out_of_range &e){
				vistaCuerpo = CrearVistaAutomaticaDefecto(automatico);
			}
			configNivel->vistas.push_back(vistaCuerpo);
		}
		cuerpo->agregarObservador(vistaCuerpo);
		configNivel->cuerpos.push_back(cuerpo);
		}
	configNivel->vistas.push_back(configNivel->vistaManual);

	if (configNivel->manual == NULL){
		tipo = string("protagonista");
		configNivel->manual = tiposPersonajes->at(tipo)->CrearManual(tiposPersonajes->at(tipo)->nombre, POS_DEFECTO, POS_DEFECTO, VEL_PERSONAJE);
		cuerpo = configNivel->manual;
		configNivel->vistaManual = new VistaProtagonista(configNivel->manual, tiposPersonajes->at(tipo)->animacionActiva , tiposPersonajes->at(tipo)->animacionPasiva);
		//configNivel->vistaManual = new VistaProtagonista(configNivel->manual);
		vistaCuerpo = configNivel->vistaManual;
		configNivel->vistas.push_back(configNivel->vistaManual );
		cuerpo->agregarObservador(vistaCuerpo);
		configNivel->cuerpos.push_back(cuerpo);

		Log::getInstance()->writeToLogFile("ERROR","PARSER: No habia personaje principal en el nivel, se carga por defecto");
	}

}


Automatico* GestorConfiguraciones::CrearAutomaticoDefecto(const char* nombre,int posX, int posY){
	int ancho = ANCHO_PERSONAJE;
	int alto = ALTO_PERSONAJE;
	//el posX posY indica el punto inferior central del personaje (consigna)
	int x = posX - ( ancho/2 );
	int y = posY - alto;
	return new Automatico(nombre,new Area(ANCHO_PERSONAJE,ALTO_PERSONAJE,new Posicion(x,y)));
}

VistaAutomatico* GestorConfiguraciones::CrearVistaAutomaticaDefecto(Automatico* automatico){
	return new VistaAutomatico(automatico, new Animacion(new HojaSprites(RUTA_ACTIVA,ANCHO_PERSONAJE,ALTO_PERSONAJE)) , new Animacion(new HojaSprites(RUTA_PASIVA,ANCHO_PERSONAJE,ALTO_PERSONAJE)) , PERIODO_PERSONAJE);
}

vector<Cuerpo*>* GestorConfiguraciones::ObtenerCuerpos(){
	return &configNivel->cuerpos;
}

vector<VistaCuerpo*>* GestorConfiguraciones::ObtenerVistas(){
	return &configNivel->vistas;
}

Manual* GestorConfiguraciones::ObtenerManual(){
	return configNivel->manual;
}

VistaProtagonista* GestorConfiguraciones::ObtenerVistaManual(){
	return configNivel->vistaManual;
}

Superficie* GestorConfiguraciones::ObtenerFondo(){
	return configPantalla->superficieCargada;
}

int GestorConfiguraciones::ObtenerAltoPantalla(){
	return configPantalla->alto;
}


int GestorConfiguraciones::ObtenerAnchoPantalla(){
	return configPantalla->ancho;
}


int GestorConfiguraciones::ObtenerAltoNivel(){
	return configNivel->alto;
}


int GestorConfiguraciones::ObtenerAnchoNivel(){
	return configNivel->ancho;
}

int GestorConfiguraciones::ObtenerMargenScroll(){
	return margen_scroll;
}

void GestorConfiguraciones::CargarTexturas(const YAML::Node& nodo){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {

			std::string nombre, ruta;
		    it.first() >> nombre;
		    it.second() >> ruta;
		    texturas -> insert(pair<std::string , std::string>(nombre,ruta));
	}
}


void GestorConfiguraciones::CargarTiposPersonajes(const YAML::Node& nodo, const YAML::Node& protDef){

	try{
		nodo["protagonista"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		std::string nombre("protagonista");
		TipoPersonaje* tipoper=_CargarTipoPersonaje(protDef, "protagonista");
		tipoper->nombre=nombre.c_str();
		tiposPersonajes -> insert(pair<std::string , TipoPersonaje*>(nombre,tipoper));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay definicion de tipo protagonista, se carga definicion por defecto");
	}

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {
		std::string nombre;
	    it.first() >> nombre;
	    TipoPersonaje* tipoper = _CargarTipoPersonaje(nodo[nombre.c_str()], nombre.c_str());
	    tipoper->nombre=nombre.c_str();
	    tiposPersonajes -> insert(pair<std::string , TipoPersonaje*>(nombre,tipoper));

	}

}


TipoPersonaje* GestorConfiguraciones::_CargarTipoPersonaje(const YAML::Node& nodo, const char* nombrecito){

	TipoPersonaje* tipoper= new TipoPersonaje();

	std::string rutaPasiva,rutaActiva;

	try{
		nodo["ancho"] >> tipoper->ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo ancho dentro del personaje, se carga por defecto");
		tipoper->ancho = ANCHO_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho no toma valor valido, se carga por defecto");
		tipoper->ancho = ANCHO_PERSONAJE;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo ancho, se carga por defecto");
		tipoper->ancho = ANCHO_PERSONAJE;
	}

	try{
		nodo["alto"] >> tipoper->alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo alto dentro del personaje, se carga por defecto");
		tipoper->alto = ALTO_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor valido, se carga por defecto");
		tipoper->alto = ALTO_PERSONAJE;
	}catch(YAML::Exception &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo alto, se carga por defecto");
		tipoper->alto = ALTO_PERSONAJE;
	}

	try{
		nodo["animaciones"];
	}catch( YAML::Exception &e) {
		rutaPasiva = RUTA_PASIVA;
		rutaActiva = RUTA_ACTIVA;
		tipoper->periodo = PERIODO_PERSONAJE;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones dentro del personaje, se cargan por defecto");
		tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		tipoper->animacionActiva=new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto));
		return tipoper;
	}

	const YAML::Node& animaciones=nodo["animaciones"];

	try{
		animaciones["quieto"];
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		rutaPasiva = RUTA_PASIVA;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		rutaPasiva = RUTA_PASIVA;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}

	if (animaciones.size() == 0){
		rutaPasiva = RUTA_PASIVA;
		rutaActiva = RUTA_ACTIVA;
		tipoper->periodo = PERIODO_PERSONAJE;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay ninguna animacion dentro del personaje, se cargan por defecto");
		tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		tipoper->animacionActiva=new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto));
		return tipoper;
	}

	if (animaciones.size() == 1) {
		std::string nombre;
		animaciones.begin().first() >> nombre;
		if (strcmp(nombre.c_str(), "quieto")==0){
			rutaActiva = RUTA_ACTIVA;
			tipoper->periodo = PERIODO_PERSONAJE;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay animacion activa dentro del personaje, se cargan por defecto");
		}
	}

	for(YAML::Iterator it=animaciones.begin();it!=animaciones.end();++it) {
		std::string nombre;
	    it.first() >> nombre;
	    if (strcmp(nombre.c_str(),"quieto")==0){
	    	try{
	    		animaciones["quieto"]["sprites"] >> rutaPasiva;
	    	}catch( YAML::TypedKeyNotFound<std::string> &e){
	    		rutaPasiva = RUTA_PASIVA;
	    		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo sprites en quieto del personaje, se cargan por defecto");
	    	}
	    }else{
	    	try{
	    		animaciones[nombre.c_str()]["sprites"] >> rutaActiva;
	    		if (strcmp(nombrecito,"protagonista")==0)
	    			tipoper->periodo = 0;
	    		else{
	    			try{
	    				animaciones[nombre.c_str()]["periodo"] >> tipoper->periodo;
	    			}catch(YAML::TypedKeyNotFound<std::string> &e){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo periodo dentro del personaje, se carga por defecto");
	    				tipoper->periodo = PERIODO_PERSONAJE;
	    			}catch(YAML::InvalidScalar &e){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: El periodo no toma valor valido, se carga por defecto");
	    				tipoper->periodo = PERIODO_PERSONAJE;
	    			}

	    			if(tipoper->periodo<0){
	    				tipoper->periodo=PERIODO_PERSONAJE;
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: El periodo toma valor negativo, se carga por defecto");
	    			}
	    		}
	    	}catch( YAML::TypedKeyNotFound<std::string> &e){
	    		rutaActiva = RUTA_ACTIVA;
	    		tipoper->periodo = PERIODO_PERSONAJE;
	    		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo sprites en animacion activa del personaje, se cargan por defecto");
	    	}
	    }
	}


	_IO_FILE* archiv=fopen(rutaPasiva.c_str(),"r");

	if (!(archiv)) rutaPasiva=RUTA_PASIVA;
	else fclose(archiv);

	_IO_FILE* archivo=fopen(rutaActiva.c_str(),"r");

	if (!(archivo)) rutaActiva=RUTA_ACTIVA;
	else fclose(archivo);

	tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
	tipoper->animacionActiva=new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto));

	return tipoper;

}

ConfiguracionPantalla* GestorConfiguraciones::CargarConfiguracionPantalla(int alto, int ancho, string ruta){

	ConfiguracionPantalla* config= new ConfiguracionPantalla();
	config->alto = alto;
	config->ancho = ancho;

	config->superficieCargada= new Superficie(ruta);

	return config;
}

ConfiguracionPantalla* GestorConfiguraciones::CargarConfiguracionPantalla(const YAML::Node& nodo){

	ConfiguracionPantalla* config= new ConfiguracionPantalla();

	std::string ruta;
	try{
		nodo["alto"] >> config->alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo alto dentro de pantalla, se carga por defecto");
		config->alto = ALTO_PANTALLA;
	}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor valido, se carga por defecto");
			config->alto = ALTO_PANTALLA;
	}
	if(config->alto < ALTO_PANTALLA_MINIMO){
		config->alto = ALTO_PANTALLA_MINIMO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor muy chico, se carga minimo");
	}

	try{
		nodo["ancho"] >> config->ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo ancho dentro de pantalla, se carga por defecto");
		config->ancho = ANCHO_PANTALLA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho no toma valor valido, se carga por defecto");
		config->ancho = ANCHO_PANTALLA;
	}
	if(config->ancho < ANCHO_PANTALLA_MINIMO){
		config->ancho = ANCHO_PANTALLA_MINIMO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor muy chico, se carga minimo");
	}


	try{
		nodo["fondo"] >> ruta;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo fondo dentro de pantalla, se carga por defecto");
		ruta = RUTA_FONDO;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No se especifica fondo para la pantalla, se carga por defecto");
		ruta=RUTA_FONDO;
	}

	_IO_FILE* archiv=fopen(ruta.c_str(),"r");

	if (!(archiv)) ruta=RUTA_FONDO;
	else fclose(archiv);

	config->superficieCargada= new Superficie(ruta);

	return config;
}

SDL_Surface* GestorConfiguraciones::CrearPantalla(){


	return configPantalla->CrearPantalla();

}
