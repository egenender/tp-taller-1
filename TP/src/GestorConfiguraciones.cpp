/*
 * GestorConfiguraciones.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include <string.h>
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
#define RUTA_FONDO "src/charmeleonMovimiento.png"
#define ANCHO_PERSONAJE 65
#define ALTO_PERSONAJE 73
#define RUTA_ACTIVA "src/charmeleonMovimiento.png"
#define RUTA_PASIVA "src/charmeleonQuieto.png"
#define PERIODO_PERSONAJE 15


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
	std::ifstream fin("src/archivoYaml.yaml");
	YAML::Parser parser(fin);
	parser.GetNextDocument(nodo);

	std::ifstream finDef("src/defecto.yaml");
	YAML::Parser parserDef(finDef);
	parserDef.GetNextDocument(nodoDef);


	try{
		const YAML::Node& nodoRaiz = nodo["juego"];
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se abrio el Archivo YAML");
	}catch(YAML::Exception &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo Juego");
		std::ifstream fin("src/defecto.yaml");
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargan configuraciones por defecto");
	}

	const YAML::Node& nodoRaiz = nodo["juego"];
	const YAML::Node& nodoRaizDef = nodoDef["juego"];

	try{
		nodoRaiz["parametros"]["vel_personaje"] >> vel_personaje;
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se carga vel_personaje");
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo vel_personaje, se carga por defecto");
		vel_personaje = VEL_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: La vel_personaje no toma valor valido, se carga por defecto");
			vel_personaje = VEL_PERSONAJE;
	}

	try{
		nodoRaiz["parametros"]["margen_scroll"] >> margen_scroll;
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se carga margen_scroll");
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo margen_scroll, se carga por defecto");
		margen_scroll = MARGEN_SCROLL;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El margen_scroll no toma valor valido, se carga por defecto");
		margen_scroll = MARGEN_SCROLL;
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
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tiposPersonaje, se carga por defecto");
		 (nodoRaizDef["tiposPersonaje"], nodoRaizDef["tiposPersonaje"]);
	}

	try{
		CargarTexturas(nodoRaiz["texturas"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de texturas");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo texturas, se carga por defecto");
		CargarTexturas(nodoRaizDef["texturas"]);
	}

	configNivel=CargarConfiguracionNivel(nodoRaiz["nivel"]);

	Log::getInstance()->writeToLogFile("INFO","PARSER: Cargo Nivel");

}

ConfiguracionNivel* GestorConfiguraciones::CargarConfiguracionNivel(const YAML::Node& nodo){
	configNivel= new ConfiguracionNivel();

	nodo["alto"] >> configNivel->alto;
	nodo["ancho"] >> configNivel->ancho;

	const YAML::Node& personajes=nodo["personajes"];
	std::string tipo;
	int posX,posY;
	Automatico* automatico;
	Cuerpo* cuerpo;
	VistaCuerpo* vistaCuerpo;
	configNivel->cuerpos = vector<Cuerpo*>();
	for(unsigned i=0;i<personajes.size();i++) {
			personajes[i]["tipo"] >> tipo;
			personajes[i]["x"] >> posX;
			personajes[i]["y"] >> posY;
			if (strcmp(tiposPersonajes->at(tipo)->nombre,"protagonista")==0){
				configNivel->manual = tiposPersonajes->at(tipo)->CrearManual(tiposPersonajes->at(tipo)->nombre, posX, posY, vel_personaje);
				cuerpo = configNivel->manual;
				configNivel->vistaManual = new VistaProtagonista(configNivel->manual, tiposPersonajes->at(tipo)->animacionActiva , tiposPersonajes->at(tipo)->animacionPasiva);
				vistaCuerpo = configNivel->vistaManual;
				configNivel->vistas.push_back(configNivel->vistaManual );
			}else{
				automatico = tiposPersonajes->at(tipo)->CrearAutomatico(tiposPersonajes->at(tipo)->nombre, posX, posY);
				cuerpo = automatico;
				vistaCuerpo = new VistaAutomatico(automatico, tiposPersonajes->at(tipo)->animacionActiva , tiposPersonajes->at(tipo)->animacionPasiva, tiposPersonajes->at(tipo)->periodo);
				configNivel->vistas.push_back(vistaCuerpo);
			}
			cuerpo->agregarObservador(vistaCuerpo);
			configNivel->cuerpos.push_back(cuerpo);
	}

	const YAML::Node& plataformas=nodo["plataformas"];
	int ancho, alto;
	std::string nombreTex;
	Estatico* estatico;
	VistaImagen* vista;
	for(unsigned i=0;i<plataformas.size();i++) {
		plataformas[i]["x"] >> posX;
		plataformas[i]["y"] >> posY;
		plataformas[i]["ancho"] >> ancho;
		plataformas[i]["alto"] >> alto;
		plataformas[i]["textura"] >> nombreTex;
		estatico = new Estatico(nombreTex.c_str(), new Area(alto,ancho,new Posicion(posX,posY) ) );
		configNivel->cuerpos.push_back(cuerpo);
		Superficie* sup =  new Superficie( texturas->at(nombreTex) , 0 , 0 , ancho, alto);
		//sup->escala(ancho,alto);
		vista = new VistaImagen( sup );
		estatico->agregarObservador(vista);
		configNivel->vistas.push_back(vista);
	}

	const YAML::Node& escaleras=nodo["escaleras"];
		for(unsigned i=0;i<escaleras.size();i++) {
			escaleras[i]["x"] >> posX;
			escaleras[i]["y"] >> posY;
			escaleras[i]["ancho"] >> ancho;
			escaleras[i]["alto"] >> alto;
			escaleras[i]["textura"] >> nombreTex;
			estatico = new Estatico(nombreTex.c_str(), new Area(alto,ancho,new Posicion(posX,posY) ) );
			configNivel->cuerpos.push_back(cuerpo);
			Superficie* sup =  new Superficie( texturas->at(nombreTex));
			sup->escala(ancho,alto);
			vista = new VistaImagen( sup );
			estatico->agregarObservador(vista);
			configNivel->vistas.push_back(vista);
		}
	return configNivel;
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
	}

	try{
		nodo["alto"] >> tipoper->alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo alto dentro del personaje, se carga por defecto");
		tipoper->alto = ALTO_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto no toma valor valido, se carga por defecto");
		tipoper->alto = ALTO_PERSONAJE;
	}

	try{
		nodo["animaciones"];
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		rutaPasiva = rutaActiva = RUTA_PASIVA;
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
	}

	if (animaciones.size() == 0){
		rutaPasiva = rutaActiva = RUTA_PASIVA;
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
			rutaActiva = RUTA_PASIVA;
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
	    		}
	    	}catch( YAML::TypedKeyNotFound<std::string> &e){
	    		rutaActiva = RUTA_PASIVA;
	    		tipoper->periodo = PERIODO_PERSONAJE;
	    		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo sprites en animacion activa del personaje, se cargan por defecto");
	    	}
	    }
	}

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

	try{
		nodo["ancho"] >> config->ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo ancho dentro de pantalla, se carga por defecto");
		config->ancho = ANCHO_PANTALLA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho no toma valor valido, se carga por defecto");
		config->ancho = ANCHO_PANTALLA;
	}

	try{
		nodo["fondo"] >> ruta;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo fondo dentro de pantalla, se carga por defecto");
		ruta = RUTA_FONDO;
	}

	config->superficieCargada= new Superficie(ruta);

	return config;
}

SDL_Surface* GestorConfiguraciones::CrearPantalla(){


	return configPantalla->CrearPantalla();

}