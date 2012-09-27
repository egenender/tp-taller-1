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

#define VEL_PERSONAJE 300
#define MARGEN_SCROLL 80
#define ANCHO_PANTALLA 800
#define ALTO_PANTALLA 600
#define ANCHO_PANTALLA_MINIMO 200
#define ALTO_PANTALLA_MINIMO 200
#define ANCHO_PANTALLA_MAXIMO 1300
#define ALTO_PANTALLA_MAXIMO 700
#define ANCHO_NIVEL_MINIMO 200
#define ALTO_NIVEL_MINIMO 200
#define RUTA_FONDO "src/fondoGrande.png"
#define ANCHO_PERSONAJE 65
#define ALTO_PERSONAJE 73
#define RUTA_ACTIVA "src/cruzCuadroError4.png"
#define RUTA_PASIVA "src/cruzCuadroError4.png"
#define PERIODO_PERSONAJE 15
#define ANCHO_NIVEL 1200
#define ALTO_NIVEL 600
#define POS_DEFECTO 60
#define TIPO_DEFECTO "defe"
#define ANCHO_OBJETO 40
#define ALTO_OBJETO 80
#define POS_DEFECTO_OBJ 80
#define TEXTURA_DEFECTO "src/texturagrande.jpg"


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

	if (vel_personaje<20){
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

		FILE* archiv=fopen(rutaImagen.c_str(),"r");
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

			//veo si entra en el nivel
			if (!Entra(x,y,ancho,alto)){
				if (!Entra(0,0,ancho,alto)){
					ancho = ANCHO_PERSONAJE;
					alto = ALTO_PERSONAJE;
					tiposPersonajes->at(tipo)->ancho = ANCHO_PERSONAJE;
					tiposPersonajes->at(tipo)->alto = ALTO_PERSONAJE;
					Log::getInstance()->writeToLogFile("ERROR","PARSER: El protagonista fue re-dimensionado para entrar en el nivel");
				}else{
					x = 0;
					y = 0;
					Log::getInstance()->writeToLogFile("ERROR","PARSER: El protagonista fue re-ubicado para entrar en el nivel");
				}
			}

			//recalculo el posX posY, indica el punto inferior central del personaje (consigna)
			x = posX - ( ancho/2 );
			y = posY - alto;

			if (!Entra(x,y,ancho,alto)){
				x=0;
				y=0;
				Log::getInstance()->writeToLogFile("ERROR","PARSER: El protagonista fue re-ubicado para entrar en el nivel");
			}

			configNivel->manual = tiposPersonajes->at(tipo)->CrearManual(tiposPersonajes->at(tipo)->nombre, x, y, vel_personaje);
			cuerpo = configNivel->manual;
			configNivel->vistaManual = new VistaProtagonista(configNivel->manual, tiposPersonajes->at(tipo)->animacionActivaProt , tiposPersonajes->at(tipo)->animacionPasivaProt);
			vistaCuerpo = configNivel->vistaManual;
		}else{
			//debo asegurarme de que pasen un tipo de personaje que ya exista:
			try{
				ancho = tiposPersonajes->at(tipo)->ancho;
				alto = tiposPersonajes->at(tipo)->alto;
				//el posX posY indica el punto inferior central del personaje (consigna)
				x = posX - ( ancho/2 );
				y = posY - alto;

				//veo si entra en el nivel
				if (!Entra(x,y,ancho,alto)){
					if (!Entra(0,0,ancho,alto)){
						ancho = ANCHO_PERSONAJE;
						alto = ALTO_PERSONAJE;
						tiposPersonajes->at(tipo)->ancho = ANCHO_PERSONAJE;
						tiposPersonajes->at(tipo)->alto = ALTO_PERSONAJE;
						Log::getInstance()->writeToLogFile("ERROR","PARSER: El personaje fue re-dimensionado para entrar en el nivel");
					}else{
						x = 0;
						y = 0;
						Log::getInstance()->writeToLogFile("ERROR","PARSER: El personaje fue re-ubicado para entrar en el nivel");
					}
				}
				if (!Entra(x,y,ancho,alto)){
					x=0;
					y=0;
					Log::getInstance()->writeToLogFile("ERROR","PARSER: El personaje fue re-ubicado para entrar en el nivel");
				}

				automatico = tiposPersonajes->at(tipo)->CrearAutomatico(tiposPersonajes->at(tipo)->nombre, x, y);
			}catch(std::out_of_range &e){
				//si no hay, por defecto
				automatico = CrearAutomaticoDefecto(tipo.c_str(), posX, posY);
				Log::getInstance()->writeToLogFile("ERROR","PARSER: No habia deficion del tipo de personaje, se carga una definicion por defecto");
			}
			cuerpo = automatico;
			try{
				vistaCuerpo = new VistaAutomatico(automatico, & tiposPersonajes->at(tipo)->animacionesActiva , & tiposPersonajes->at(tipo)->periodos);
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
		configNivel->vistaManual = new VistaProtagonista(configNivel->manual, tiposPersonajes->at(tipo)->animacionActivaProt , tiposPersonajes->at(tipo)->animacionPasivaProt);
		//configNivel->vistaManual = new VistaProtagonista(configNivel->manual);
		vistaCuerpo = configNivel->vistaManual;
		configNivel->vistas.push_back(configNivel->vistaManual );
		cuerpo->agregarObservador(vistaCuerpo);
		configNivel->cuerpos.push_back(cuerpo);

		Log::getInstance()->writeToLogFile("ERROR","PARSER: No habia personaje principal en el nivel, se carga por defecto");
	}

}

bool GestorConfiguraciones::Entra(int x, int y, int ancho, int alto){
	int izqX, izqY, derX, derY;
	izqX = x;
	izqY = y;
	derX = x + ancho;
	derY = y + alto;

	if (izqX<0 || izqX>=configNivel->ancho){
		return false;
	}
	if (derX<0 || derX>=configNivel->ancho){
		return false;
	}
	if (izqY<0 || izqY>=configNivel->alto){
		return false;
	}
	if (derY<0 || derY>=configNivel->alto){
		return false;
	}

	return true;
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
	vector<Animacion*> animaciones;
	vector<int> periodos;
	animaciones.push_back(new Animacion(new HojaSprites(RUTA_ACTIVA,ANCHO_PERSONAJE,ALTO_PERSONAJE)));
	periodos.push_back(PERIODO_PERSONAJE);
	return new VistaAutomatico(automatico, & animaciones , & periodos);
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

		    FILE* archiv=fopen(ruta.c_str(),"r");

		    if (!(archiv)){
		    	Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la textura no corresponde con un archivo valido, se carga por defecto");
		    	ruta = TEXTURA_DEFECTO;
		    }
		    else
		    	fclose(archiv);

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
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones dentro del personaje, se cargan por defecto");
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		tipoper->animacionActivaProt=new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto));

		tipoper->animacionesActiva.push_back(  new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto))  );
		tipoper->periodos.push_back(PERIODO_PERSONAJE);
		return tipoper;
	}

	const YAML::Node& animaciones=nodo["animaciones"];

	try{
		animaciones["quieto"];
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		rutaPasiva = RUTA_PASIVA;
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		rutaPasiva = RUTA_PASIVA;
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}
	/*
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
	*/
	int unPeriodo;
	std::string unaRuta;
	vector<std::string> rutas;
	for(YAML::Iterator it=animaciones.begin();it!=animaciones.end();++it) {
		std::string nombre;
	    it.first() >> nombre;
	    if ( (strcmp(nombre.c_str(),"quieto")==0) &&  (strcmp(nombrecito,"protagonista")==0) ) {
	    	try{
	    		animaciones["quieto"]["sprites"] >> rutaPasiva;


	    		FILE* archiv=fopen(rutaPasiva.c_str(),"r");

	    			if (!(archiv)){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la animacion pasiva no corresponde con un archivo valido, se carga por defecto");
	    				rutaPasiva=RUTA_PASIVA;
	    			}
	    			else
	    				fclose(archiv);


	    		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
	    	}catch( YAML::TypedKeyNotFound<std::string> &e){
	    		rutaPasiva = RUTA_PASIVA;
	    		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
	    		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo sprites en quieto del personaje, se cargan por defecto");
	    	}
	    }else{
	    	try{
	    		animaciones[nombre.c_str()]["sprites"] >> unaRuta;
	    		if (strcmp(nombrecito,"protagonista")==0){
	    			rutaActiva = unaRuta;

	    			FILE* archivo=fopen(rutaActiva.c_str(),"r");

	    			if (!(archivo)){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la animacion activa no corresponde con un archivo valido, se carga por defecto");
	    				rutaActiva=RUTA_ACTIVA;
	    			}
	    			else
	    				fclose(archivo);

	    			tipoper->animacionActivaProt=new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto));
	    		}
	    		else{
	    			try{
	    				animaciones[nombre.c_str()]["periodo"] >> unPeriodo;
	    			}catch(YAML::TypedKeyNotFound<std::string> &e){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo periodo dentro del personaje, se carga por defecto");
	    				unPeriodo = PERIODO_PERSONAJE;
	    			}catch(YAML::InvalidScalar &e){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: El periodo no toma valor valido, se carga por defecto");
	    				unPeriodo = PERIODO_PERSONAJE;
	    			}

	    			if(unPeriodo<0){
	    				unPeriodo=PERIODO_PERSONAJE;
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: El periodo toma valor negativo, se carga por defecto");
	    			}

	    			FILE* archivo=fopen(unaRuta.c_str(),"r");

	    			if (!(archivo)){
	    				Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la animacion activa no corresponde con un archivo valido, se carga por defecto");
	    				unaRuta=RUTA_ACTIVA;
	    			}
	    			else
	    				fclose(archivo);

	    			tipoper->animacionesActiva .push_back(  new Animacion(new HojaSprites(unaRuta,tipoper->ancho,tipoper->alto))  );
	    			tipoper->periodos.push_back (unPeriodo);

	    		}
	    	}catch( YAML::TypedKeyNotFound<std::string> &e){
	    		rutaActiva = RUTA_ACTIVA;

	    		try{
	    			animaciones[nombre.c_str()]["periodo"] >> unPeriodo;
	    		}catch(YAML::TypedKeyNotFound<std::string> &e){
	    			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo periodo dentro del personaje, se carga por defecto");
	    			unPeriodo = PERIODO_PERSONAJE;
	    		}catch(YAML::InvalidScalar &e){
	    			Log::getInstance()->writeToLogFile("ERROR","PARSER: El periodo no toma valor valido, se carga por defecto");
	    			unPeriodo = PERIODO_PERSONAJE;
	    		}

	    		tipoper->animacionesActiva .push_back(  new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto))  );
	    		tipoper->periodos.push_back (unPeriodo);

	    		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo sprites en animacion activa del personaje, se cargan por defecto");
	    	}
	    }
	}

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
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto toma valor muy chico, se carga minimo");
	}
	if(config->alto > ALTO_PANTALLA_MAXIMO){
		config->alto = ALTO_PANTALLA_MAXIMO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto toma valor muy grande, se carga maximo");
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
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho toma valor muy chico, se carga minimo");
	}
	if(config->ancho > ANCHO_PANTALLA_MAXIMO){
			config->ancho = ANCHO_PANTALLA_MAXIMO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho toma valor muy grande, se carga maximo");
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

	FILE* archiv=fopen(ruta.c_str(),"r");

	if (!(archiv)) {
		ruta=RUTA_FONDO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta del fondo para la pantalla no corresponde con un archivo valido, se carga por defecto");
	}
	else
		fclose(archiv);

	config->superficieCargada= new Superficie(ruta);

	return config;
}

SDL_Surface* GestorConfiguraciones::CrearPantalla(){


	return configPantalla->CrearPantalla();

}
