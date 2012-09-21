/*
 * GestorConfiguraciones.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "GestorConfiguraciones.h"
#include "ConfiguracionPantalla.h"
#include <string.h>
#include <iostream>
#include <fstream>

GestorConfiguraciones::GestorConfiguraciones (){
	vel_personaje=0;
	margen_scroll=0;
	configPantalla=0;
	tiposPersonajes=new mapa_per();
	texturas=new mapa_tex();


	std::ifstream fin("src/archivoYaml.yaml");
	YAML::Parser parser(fin);
	YAML::Node nodo;
	parser.GetNextDocument(nodo);

	const YAML::Node& nodoRaiz = nodo["juego"];

	nodoRaiz["parametros"]["vel_personaje"] >> vel_personaje;
	nodoRaiz["parametros"]["margen_scroll"] >> margen_scroll;

	configPantalla=CargarConfiguracionPantalla(nodoRaiz["pantalla"]);

	CargarTiposPersonajes(nodoRaiz["tiposPersonaje"]);
	CargarTexturas(nodoRaiz["texturas"]);

}

void GestorConfiguraciones::CargarTexturas(const YAML::Node& nodo){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {

			std::string nombre, ruta;
		    it.first() >> nombre;
		    it.second() >> ruta;
		    texturas -> insert(pair<std::string , Superficie*>(nombre,new Superficie(ruta)));

	}

}


void GestorConfiguraciones::CargarTiposPersonajes(const YAML::Node& nodo){


	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {

		std::string nombre;
	    it.first() >> nombre;
	    TipoPersonaje* tipoper=_CargarTipoPersonaje(nodo[nombre.c_str()]);
	    tiposPersonajes -> insert(pair<std::string , TipoPersonaje*>(nombre,tipoper));

	}

}


TipoPersonaje* GestorConfiguraciones::_CargarTipoPersonaje(const YAML::Node& nodo){

	TipoPersonaje* tipoper= new TipoPersonaje();

	std::string rutaPasiva,rutaActiva;

	nodo["ancho"] >> tipoper->ancho;
	nodo["alto"] >> tipoper->alto;

	const YAML::Node& animaciones=nodo["animaciones"];

	for(YAML::Iterator it=animaciones.begin();it!=animaciones.end();++it) {

		std::string nombre;
	    it.first() >> nombre;
	    if (strcmp(nombre.c_str(),"quieto")==0) animaciones["quieto"]["sprites"] >>rutaPasiva;
	    else animaciones[nombre.c_str()]["sprites"] >> rutaActiva;

	}

	tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
	tipoper->animacionActiva=new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto));

	return tipoper;

}

ConfiguracionPantalla* GestorConfiguraciones::CargarConfiguracionPantalla(const YAML::Node& nodo){

	ConfiguracionPantalla* config= new ConfiguracionPantalla();

	std::string ruta;

	nodo["alto"] >> config->alto;
	nodo["ancho"] >> config->ancho;
	nodo["fondo"] >> ruta;

	config->superficieCargada= new Superficie(ruta);

	return config;
}

SDL_Surface* GestorConfiguraciones::CrearPantalla(){


	return configPantalla->CrearPantalla();

}
