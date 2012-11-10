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
#include "../model/Personajes/Escalera.h"
#include "../model/Personajes/Plataforma.h"
#include "../model/Area.h"
#include "SDL/SDL_mixer.h"
#include "../log/Log.h"
#include <sstream>
#include "Sounds.h"
#include "../view/VistaVarios.h"
#include "../model/Observable.h"

#define VEL_PERSONAJE_MINIMA 2
#define VEL_PERSONAJE 10
#define SALTO_PERSONAJE 20
#define SALTO_PERSONAJE_MINIMO 10
#define MARGEN_SCROLL 80
#define ANCHO_PANTALLA 800
#define ALTO_PANTALLA 600
#define ANCHO_PANTALLA_MINIMO 633
#define ALTO_PANTALLA_MINIMO 530
#define ANCHO_PANTALLA_MAXIMO 1300
#define ALTO_PANTALLA_MAXIMO 700
#define ANCHO_NIVEL_MINIMO 200
#define ALTO_NIVEL_MINIMO 200
#define RUTA_FONDO "src/resources/fondoGrande.png"
#define ANCHO_PERSONAJE 65
#define ALTO_PERSONAJE 73
#define RUTA_ACTIVA "src/resources/cruzCuadroError4.png"
#define RUTA_PASIVA "src/resources/cruzCuadroError4.png"
#define RUTA_SALTA "src/resources/cruzCuadroError4.png"
#define PERIODO_PERSONAJE 15
#define ANCHO_NIVEL 1200
#define ALTO_NIVEL 600
#define PISO_NIVEL 600
#define POS_DEFECTO 60
#define TIPO_DEFECTO "defe"
#define ANCHO_OBJETO 40
#define ALTO_OBJETO 80
#define POS_DEFECTO_OBJ 80
#define TEXTURA_DEFECTO "src/resources/viga2.jpg"


// Puntero estatico para controlar la instanciacion.
GestorConfiguraciones* GestorConfiguraciones::instancia;

GestorConfiguraciones* GestorConfiguraciones::getInstance() {
   if(instancia!=NULL)
	   return instancia;
   instancia = new GestorConfiguraciones();
   return instancia;
}

void GestorConfiguraciones::acabarGestor() {
   instancia = NULL;
}

void GestorConfiguraciones::AgregarAVector(string ruta){


	for (unsigned int i = 0; i < vectorRutas->size(); i++) {
		const char* rutaVector = (vectorRutas->at(i).c_str());
		if (strcmp(rutaVector,ruta.c_str())==0) return;
	}

	vectorRutas->push_back(ruta);

}

GestorConfiguraciones::GestorConfiguraciones (){
	margen_scroll=0;
	configPantalla=0;
	nivelElegido = 0;
	tiposProtagonista=new mapa_prot();
	tiposAutomatico=new mapa_auto();
	texturas=new mapa_tex();
	vectorRutas=new std::vector<string>();
	manuales = NULL;
	esCliente = false;
	headerTemp = "Temp/";
	rutaYaml = "src/config/archivoYaml.yaml";
	rutaYamlDefecto = "src/config/defecto.yaml";
	dummy = NULL;
	configNivel = NULL;
	contenedor = NULL;
	nombresProt = NULL;
	posiblesNiveles = NULL;
	posiblesTiposProt = NULL;
	mapaParam = new mapa_parametrosPersonaje();
}

void GestorConfiguraciones::setEsCliente (){
	esCliente = true;
	rutaYaml = headerTemp + rutaYaml;
	rutaYamlDefecto = headerTemp + rutaYamlDefecto;
}

//void GestorConfiguraciones::CargarPantalla(){
//	YAML::Node nodo,nodoDef;
//
//	try{
//		std::ifstream fin("src/config/archivoYaml.yaml");
//		YAML::Parser parser(fin);
//		parser.GetNextDocument(nodo);
//	} catch(YAML::ParserException &e){
//		std::ifstream fin("src/config/defecto.yaml");
//		YAML::Parser parser(fin);
//		parser.GetNextDocument(nodo);
//
//	}
//	std::ifstream finDef("src/config/defecto.yaml");
//	AgregarAVector("src/config/defecto.yaml");
//	YAML::Parser parserDef(finDef);
//	parserDef.GetNextDocument(nodoDef);
//
//
//	try{
//		const YAML::Node& nodoRaiz = nodo["juego"];
//	}catch(YAML::Exception &e){
//		std::ifstream fin("src/config/defecto.yaml");
//		YAML::Parser parser(fin);
//		parser.GetNextDocument(nodo);
//	}
//
//	const YAML::Node& nodoRaiz = nodo["juego"];
//	const YAML::Node& nodoRaizDef = nodoDef["juego"];
//
//	try{
//		configPantalla=CargarConfiguracionPantalla(nodoRaiz["pantalla"]);
//		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de Pantalla");
//	}catch(YAML::TypedKeyNotFound<std::string> &e){
//		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo pantalla, se carga por defecto");
//		configPantalla=CargarConfiguracionPantalla(ANCHO_PANTALLA,ALTO_PANTALLA);
//	}
//}

void GestorConfiguraciones::inicioCarga(){
	YAML::Node nodo,nodoDef;
	if(!esCliente){
		AgregarAVector("src/config/archivoYaml.yaml");
		AgregarAVector("src/resources/fondoGrande.png");
		AgregarAVector("src/resources/cruzCuadroError4.png");
		AgregarAVector("src/resources/viga2.jpg");
	}

	try{
		std::ifstream fin(rutaYaml.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
		Log::getInstance()->writeToLogFile("INFO","PARSER: El parser de la libreria YAML corre apropiadamente");
	} catch(YAML::ParserException &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El archivo YAML no tiene el formato correcto, se parsea archivo default");
		std::ifstream fin(rutaYamlDefecto.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
	}

	std::ifstream finDef(rutaYamlDefecto.c_str());
	YAML::Parser parserDef(finDef);
	parserDef.GetNextDocument(nodoDef);

	if(!esCliente)
		AgregarAVector(rutaYamlDefecto);

	try{
		const YAML::Node& nodoRaiz = nodo["juego"];
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se abrio el Archivo YAML");
	}catch(YAML::Exception &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo Juego, se cargan configuraciones por defecto");
		std::ifstream fin(rutaYamlDefecto.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
	}

	const YAML::Node& nodoRaiz = nodo["juego"];
	const YAML::Node& nodoRaizDef = nodoDef["juego"];

//	try{
//		configPantalla=CargarConfiguracionPantalla(nodoRaiz["pantalla"]);
//	}catch(YAML::TypedKeyNotFound<std::string> &e){
//		configPantalla=CargarConfiguracionPantalla(ANCHO_PANTALLA,ALTO_PANTALLA);
//	}

	try{
		CargarTiposProtagonista(nodoRaiz["tiposProtagonista"] , nodoRaizDef["tiposProtagonista"]["protagonista"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de tiposPersonaje");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tiposPersonaje, se cargan por defecto");
		CargarTiposProtagonista(nodoRaizDef["tiposProtagonista"], nodoRaizDef["tiposProtagonista"]);
	}

	try{
		CargarTiposAutomaticos(nodoRaiz["tiposAutomatico"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de tiposPersonaje");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tiposPersonaje, se cargan por defecto");
		CargarTiposAutomaticos(nodoRaizDef["tiposAutomatico"]);
	}

	try{
		CargarTexturas(nodoRaiz["texturas"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de texturas");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo texturas, se cargan por defecto");
		CargarTexturas(nodoRaizDef["texturas"]);
	}


	CargarPersonajes(nodoRaiz);


}

void GestorConfiguraciones::CargarPersonajes(const YAML::Node& nodoRaiz){

	// Hongo
	parametrosPersonaje* paramHongo= crearParametrosPersonaje(nodoRaiz["hongo"],"hongo");

	string ruta;

	nodoRaiz["hongo"]["animaciones"]["caminando"]>>ruta;

	Animacion* animacionCaminando= new Animacion(new HojaSprites(ruta,paramHongo->ancho,paramHongo->alto));

	paramHongo->animaciones->push_back(animacionCaminando);

	nodoRaiz["hongo"]["animaciones"]["cayendo"]>>ruta;

	Animacion* animacionCayendo= new Animacion(new HojaSprites(ruta,paramHongo->ancho,paramHongo->alto));

	paramHongo->animaciones->push_back(animacionCayendo);

	std::vector<int>* aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramHongo->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(SALTANDODER);
	aux->push_back(SALTANDOIZQ);

	paramHongo->matrizEstados->push_back(aux);

	// Princesa
	parametrosPersonaje* paramPrincesa= crearParametrosPersonaje(nodoRaiz["princesa"],"princesa");

	nodoRaiz["princesa"]["animaciones"]["quieto"]>>ruta;

	Animacion* animacionQuieto= new Animacion(new HojaSprites(ruta,paramPrincesa->ancho,paramPrincesa->alto));

	paramPrincesa->animaciones->push_back(animacionQuieto);

	nodoRaiz["princesa"]["animaciones"]["gritando"]>>ruta;

	Animacion* animacionGritando= new Animacion(new HojaSprites(ruta,paramPrincesa->ancho,paramPrincesa->alto));

	paramPrincesa->animaciones->push_back(animacionGritando);

	aux= new std::vector<int>();

	aux->push_back(QUIETO);

	paramPrincesa->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(GRITANDO);

	paramPrincesa->matrizEstados->push_back(aux);

	// Mono

	parametrosPersonaje* paramMono= crearParametrosPersonaje(nodoRaiz["mono"],"mono");

	nodoRaiz["mono"]["animaciones"]["quieto"]>>ruta;

	animacionQuieto= new Animacion(new HojaSprites(ruta,paramMono->ancho,paramMono->alto));

	paramMono->animaciones->push_back(animacionQuieto);

	nodoRaiz["mono"]["animaciones"]["lanzando"]>>ruta;

	Animacion* animacionLanzando= new Animacion(new HojaSprites(ruta,paramMono->ancho,paramMono->alto));

	paramMono->animaciones->push_back(animacionLanzando);

	aux= new std::vector<int>();

	aux->push_back(QUIETO);

	paramMono->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(LANZANDO);

	paramMono->matrizEstados->push_back(aux);

	// Barril

	parametrosPersonaje* paramBarril= crearParametrosPersonaje(nodoRaiz["barril"],"barril");

	nodoRaiz["barril"]["animaciones"]["saltar"]>>ruta;

	Animacion* animacionSaltar= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionSaltar);

	nodoRaiz["barril"]["animaciones"]["quieto"]>>ruta;

	animacionQuieto= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionGritando);

	nodoRaiz["barril"]["animaciones"]["caminando"]>>ruta;

	animacionCaminando= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionCaminando);


	aux= new std::vector<int>();

	aux->push_back(SALTAR);

	paramBarril->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(QUIETO);

	paramBarril->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramBarril->matrizEstados->push_back(aux);

	// Tortuga
	parametrosPersonaje* paramTortuga= crearParametrosPersonaje(nodoRaiz["tortuga"],"tortuga");

	nodoRaiz["tortuga"]["animaciones"]["saltando"]>>ruta;

	Animacion* animacionSaltando= new Animacion(new HojaSprites(ruta,paramTortuga->ancho,paramTortuga->alto));

	paramTortuga->animaciones->push_back(animacionSaltando);

	nodoRaiz["tortuga"]["animaciones"]["quieto"]>>ruta;

	animacionQuieto= new Animacion(new HojaSprites(ruta,paramTortuga->ancho,paramTortuga->alto));

	paramTortuga->animaciones->push_back(animacionQuieto);

	nodoRaiz["tortuga"]["animaciones"]["caminando"]>>ruta;

	animacionCaminando= new Animacion(new HojaSprites(ruta,paramTortuga->ancho,paramTortuga->alto));

	paramTortuga->animaciones->push_back(animacionCaminando);

	nodoRaiz["tortuga"]["animaciones"]["movil"]>>ruta;

	Animacion* animacionMovil= new Animacion(new HojaSprites(ruta,paramTortuga->ancho,paramTortuga->alto));

	paramTortuga->animaciones->push_back(animacionMovil);

	aux= new std::vector<int>();

	aux->push_back(SALTANDODER);
	aux->push_back(SALTANDOIZQ);

	paramTortuga->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(QUIETO);

	paramTortuga->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramTortuga->matrizEstados->push_back(aux);

	aux= new std::vector<int>();

	aux->push_back(MOVILDERECHA);
	aux->push_back(MOVILIZQUIERDA);

	paramTortuga->matrizEstados->push_back(aux);

	//PowerUp Vida Extra:

	parametrosPersonaje* paramVidaExtra= crearParametrosPersonaje(nodoRaiz["vidaExtra"],"vidaExtra");

	nodoRaiz["tortuga"]["animaciones"]["movimiento"]>>ruta;

	Animacion* animacionMov= new Animacion(new HojaSprites(ruta,paramTortuga->ancho,paramTortuga->alto));

	paramVidaExtra->animaciones->push_back(animacionMov);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramVidaExtra->matrizEstados->push_back(aux);

}

parametrosPersonaje* GestorConfiguraciones::crearParametrosPersonaje(const YAML::Node& nodo, string nombre){

	parametrosPersonaje* param= (parametrosPersonaje*)malloc(sizeof(parametrosPersonaje));

	param->animaciones= new std::vector<Animacion*>();
	param->matrizEstados= new std::vector<std::vector<int>*>();


	nodo["alto"]>>param->alto;
	nodo["ancho"]>>param->ancho;
	nodo["velocidad"]>>param->velocidad;

	mapaParam->insert(pair<string,parametrosPersonaje*>(nombre,param));

	return param;
}

parametrosPersonaje* GestorConfiguraciones::obtenerParametrosPersonaje(string nombre){

	return mapaParam->at(nombre);

}

void GestorConfiguraciones::crearVista(Cuerpo* cuerpo,string clave){

	parametrosPersonaje* paramPersonaje=mapaParam->at(clave);

	VistaVarios* vista=new VistaVarios();
	for (unsigned int i =0; i<paramPersonaje->animaciones->size();i++){

		if (paramPersonaje->matrizEstados->at(i)->size()==1){

			vista->agregarEstadoSoportado(paramPersonaje->matrizEstados->at(i)->at(0),paramPersonaje->animaciones->at(i));

		}else{
			vista->agregarEstadoSoportadoEInverso(paramPersonaje->matrizEstados->at(i)->at(0),paramPersonaje->matrizEstados->at(i)->at(1),paramPersonaje->animaciones->at(i));

		}

	}

	cuerpo->agregarObservador(vista);
	configNivel->actualizables.push_back(cuerpo);
	configNivel->vistas.push_back(vista);
}
void GestorConfiguraciones::CargaRestante(){
	YAML::Node nodo,nodoDef;
	try{
		std::ifstream fin(rutaYaml.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
	} catch(YAML::ParserException &e){
		std::ifstream fin(rutaYamlDefecto.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
	}
	std::ifstream finDef(rutaYamlDefecto.c_str());
	if (!esCliente)
		AgregarAVector(rutaYamlDefecto);
	YAML::Parser parserDef(finDef);
	parserDef.GetNextDocument(nodoDef);

	try{
		const YAML::Node& nodoRaiz = nodo["juego"];
	}catch(YAML::Exception &e){
		std::ifstream fin(rutaYamlDefecto.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodo);
	}

	const YAML::Node& nodoRaiz = nodo["juego"];
	const YAML::Node& nodoRaizDef = nodoDef["juego"];


	configNivel = new ConfiguracionNivel();
	try{
		CargarConfiguracionNivel(nodoRaiz["nivel"],nodoRaizDef["nivel"]["personajes"],nodoRaizDef["nivel"]["plataformas"],nodoRaizDef["nivel"]["escaleras"]);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones del Nivel");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo nivel, se carga enteramente por defecto");
		CargarConfiguracionNivel(nodoRaizDef["nivel"],nodoRaizDef["nivel"]["personajes"],nodoRaizDef["nivel"]["plataformas"],nodoRaizDef["nivel"]["escaleras"]);
	}


//	if ((configPantalla->alto) > (configNivel->alto)){
//		configPantalla->alto=configNivel->alto;
//		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto de la pantalla supera al del nivel, se carga alto maximo valido");
//	}
//	if ((configPantalla->ancho) > (configNivel->ancho)){
//		configPantalla->ancho=configNivel->ancho;
//		Log::getInstance()->writeToLogFile("ERROR","PARSER: El ancho de la pantalla supera al del nivel, se carga alto maximo valido");
//	}


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

void GestorConfiguraciones::setPosiblesNiveles(){
	posiblesNiveles = new std::vector<string>();
	YAML::Node nodo;
	std::string nombre, ruta;
	std::ifstream fin(rutaYaml.c_str());
	YAML::Parser parser(fin);
	parser.GetNextDocument(nodo);

	const YAML::Node& nodoNivel = nodo["juego"]["nivel"];

	for(unsigned i=0;i<nodoNivel.size();i++) {
		nodoNivel[i]["nivel"] >> nombre;
		nodoNivel[i]["fondo"] >> ruta;
		posiblesNiveles->push_back(nombre);
	}

}

void GestorConfiguraciones::setPosiblesTiposProtagonistas(){
	posiblesTiposProt = new std::vector<TipoProtagonista*>();
	nombresProt = new vector<string>();
	YAML::Node nodo;
	std::string ruta;
	std::ifstream fin(rutaYaml.c_str());
	YAML::Parser parser(fin);
	parser.GetNextDocument(nodo);

	const YAML::Node& nodoProt = nodo["juego"]["tiposProtagonista"];

	for(YAML::Iterator it=nodoProt.begin();it!=nodoProt.end();++it) {
		std::string nombre;
		it.first() >> nombre;
		TipoProtagonista* tipoper = _CargarTipoProtagonista(nodoProt[nombre.c_str()], nombre.c_str());
		tipoper->nombre=nombre.c_str();
		tiposProtagonista -> insert(pair<std::string , TipoProtagonista*>(nombre,tipoper));
		posiblesTiposProt->push_back(tipoper);
		nombresProt->push_back(nombre);
	}
}


std::vector<string>* GestorConfiguraciones::ObtenerPosiblesNiveles(){
	return posiblesNiveles;
}

std::vector<TipoProtagonista*>* GestorConfiguraciones::ObtenerPosiblesTiposProtagonistas(){
	return posiblesTiposProt;
}
std::vector<string>* GestorConfiguraciones::obtenerNombresProtagonistas(){
	return nombresProt;
}

void GestorConfiguraciones::setNivelElegido(int nivel){
	nivelElegido = nivel;
}

int GestorConfiguraciones::ObtenerNivelElegido(){
	return nivelElegido;
}

void GestorConfiguraciones::CargarConfiguracionNivel(const YAML::Node& nodo, const YAML::Node& defPersonajes, const YAML::Node& defPlataformas, const YAML::Node& defEscaleras){

	try{
		nodo[nivelElegido]["ancho"] >> configNivel->ancho;
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
		nodo[nivelElegido]["alto"] >> configNivel->alto;
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


	string ruta;

	nodo[nivelElegido]["musica"] >> ruta;

	if (ruta!="~"){

		AgregarAVector(ruta);
		ruta="./"+ruta;
		configNivel->musica=Mix_LoadMUS(ruta.c_str());

	}

	int ancho,alto,x,y;
	float inclinacion;
	string rutaImagen,tex;
	//VistaImagen * vista;
	for(unsigned i=0;i<nodo[nivelElegido]["vigas"].size();i++) {

		nodo[nivelElegido]["vigas"][i]["textura"] >> tex;
		nodo[nivelElegido]["vigas"][i]["ancho"]>> ancho;
		nodo[nivelElegido]["vigas"][i]["alto"]>> alto;
		nodo[nivelElegido]["vigas"][i]["inclinacion"]>> inclinacion;
		nodo[nivelElegido]["vigas"][i]["x"]>> x;
		nodo[nivelElegido]["vigas"][i]["y"]>> y;


		VigaInclinada* viga= new VigaInclinada("nombre",new Area(ancho,alto,new Posicion(x,y)),inclinacion);

		viga->guardarSubPlataformas(&configNivel->actualizables);

		configNivel->actualizables.push_back(viga);

//		rutaImagen = texturas->at(texturas->at(tex));
//		vista = new VistaImagen(new Superficie(rutaImagen)); // warap, aca tema rotable
//
//		configNivel->vistas.push_back(vista);
//
//		viga->agregarObservador(vista);

	}


	try{
		nodo[nivelElegido]["piso"] >> configNivel->piso;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo piso dentro del nivel, se carga por defecto");
		configNivel->piso = PISO_NIVEL;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El piso no toma valor valido, se carga por defecto");
		configNivel->piso = PISO_NIVEL;
	}

	if ((configNivel->piso)< 300){
		configNivel->piso=PISO_NIVEL;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El alto del nivel toma valor muy chico o negativo, se carga minimo valido");
	}


	if ((configNivel->piso)> configNivel->alto){
		configNivel->piso=configNivel->alto;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El piso del nivel toma valor muy alto, se carga maximo valido");
	}


	try{
		nodo[nivelElegido]["fondo"] >> ruta;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo fondo dentro de pantalla, se carga por defecto");
		ruta = RUTA_FONDO;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No se especifica fondo para la pantalla, se carga por defecto");
		ruta=RUTA_FONDO;
	}

	if (esCliente)
		ruta = headerTemp + ruta;

	FILE* archiv=fopen(ruta.c_str(),"r");

	if (!(archiv)) {
		ruta=RUTA_FONDO;
		if (esCliente)
				ruta = headerTemp + ruta;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta del fondo para la pantalla no corresponde con un archivo valido, se carga por defecto");
	}
	else
		fclose(archiv);

	if (!esCliente)
		AgregarAVector(ruta);
	configNivel->superficieCargada= new Superficie(ruta);


	try{
		CargarEstaticosNivel(nodo[nivelElegido]["plataformas"], false, true, PLATAFORMA);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de las plataformas del nivel");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo plataformas, se cargan por defecto");
		CargarEstaticosNivel(defPlataformas, false, true, PLATAFORMA);
	}

	try{
		CargarEstaticosNivel(nodo[nivelElegido]["escaleras"], true, false, ESCALERA);
		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de las escaleras del nivel");
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo escaleras, se cargan por defecto");
		CargarEstaticosNivel(defEscaleras, true, false, ESCALERA);
	}

	try{
			CargarPersonajesNivel(nodo[nivelElegido]["personajes"]);
			Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de los personajes del nivel");
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo personajes, se cargan por defecto");
			CargarPersonajesNivel(defPersonajes);
		}

}

void GestorConfiguraciones::CargarEstaticosNivel(const YAML::Node& nodo, bool escalar, bool cortar, int tipo){
	int posX,posY;
	int ancho, alto;
	std::string nombreTex;
	Cuerpo* estatico;
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
		if (tipo == ESCALERA)
			estatico = new Escalera(nombreTex.c_str(), new Area(ancho,alto,new Posicion(posX,posY) ) );
		else
			estatico = new Plataforma(nombreTex.c_str(), new Area(ancho,alto,new Posicion(posX,posY) ) );
		configNivel->actualizables.push_back(estatico);

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
			if(esCliente)
				rutaImagen = headerTemp + rutaImagen;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Ruta de imagen de textura invalida, se carga una ruta por defecto");
		}
		else
			fclose(archiv);

		if(!esCliente)
			AgregarAVector(rutaImagen);

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

		//debo asegurarme de que pasen un tipo de personaje que ya exista:
		try{
			ancho = tiposAutomatico->at(tipo)->ancho;
			alto = tiposAutomatico->at(tipo)->alto;
			//el posX posY indica el punto inferior central del personaje (consigna)
			x = posX - ( ancho/2 );
			y = posY - alto;
				//veo si entra en el nivel
			if (!Entra(x,y,ancho,alto)){
				if (!Entra(0,0,ancho,alto)){
					ancho = ANCHO_PERSONAJE;
					alto = ALTO_PERSONAJE;
					tiposAutomatico->at(tipo)->ancho = ANCHO_PERSONAJE;
					tiposAutomatico->at(tipo)->alto = ALTO_PERSONAJE;
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

			automatico = tiposAutomatico->at(tipo)->CrearAutomatico(tiposAutomatico->at(tipo)->nombre, x, y);
		}catch(std::out_of_range &e){
			//si no hay, por defecto
			automatico = CrearAutomaticoDefecto(tipo.c_str(), posX, posY);
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No habia deficion del tipo de personaje, se carga una definicion por defecto");
		}
		cuerpo = automatico;
		try{
			vistaCuerpo = new VistaAutomatico(automatico, tiposAutomatico->at(tipo)->animacionPasiva, & tiposAutomatico->at(tipo)->animacionesActiva , & tiposAutomatico->at(tipo)->periodos);
		}catch(std::out_of_range &e){
			vistaCuerpo = CrearVistaAutomaticaDefecto(automatico);
		}
		configNivel->vistas.push_back(vistaCuerpo);
		cuerpo->agregarObservador(vistaCuerpo);
		configNivel->actualizables.push_back(cuerpo);
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
	string rutaPasiva = headerTemp + RUTA_PASIVA;
	string rutaActiva = headerTemp + RUTA_ACTIVA;
	Animacion* pasiva =  new Animacion(new HojaSprites(rutaPasiva,ANCHO_PERSONAJE,ALTO_PERSONAJE));
	animaciones.push_back(new Animacion(new HojaSprites(rutaActiva,ANCHO_PERSONAJE,ALTO_PERSONAJE)));
	periodos.push_back(PERIODO_PERSONAJE);
	return new VistaAutomatico(automatico, pasiva, & animaciones , & periodos);
}

vector<Actualizable*>* GestorConfiguraciones::ObtenerActualizables(){
	return &configNivel->actualizables;
}

vector<VistaCuerpo*>* GestorConfiguraciones::ObtenerVistas(){
	return &configNivel->vistas;
}

Mix_Music* GestorConfiguraciones::ObtenerMusica(){

	return configNivel->musica;

}


void GestorConfiguraciones::setProtagonista(string nombre){
	bool encontrado = false;
	unsigned int i = 0;
	while ( !encontrado && i< posiblesTiposProt->size() ){
		encontrado = ( strcmp ( posiblesTiposProt->at(i)->nombre , nombre.c_str() ) == 0 );
		i++;
	}
	i--;
	if (!encontrado)
		return ;

	VistaProtagonista* vista = new VistaProtagonista(posiblesTiposProt->at(i)->animacionActivaProt, posiblesTiposProt->at(i)->animacionPasivaProt, posiblesTiposProt->at(i)->animacionSaltaProt);
	configNivel->vistas.push_back(vista);
	configNivel->vistas.push_back(posiblesTiposProt->at(i)->vistaSonora);
	if (esCliente){
		dummy = new Dummy(i, new Posicion(50,50), posiblesTiposProt->at(i)->ancho, posiblesTiposProt->at(i)->alto);
		dummy->agregarObservador(vista);
		dummy->agregarObservador(posiblesTiposProt->at(i)->vistaSonora);
		contenedor = new ContenedorDummy();
		contenedor->agregarDummy(dummy);
		configNivel->actualizables.push_back(contenedor);
	}else{
		Posicion* pos = new Posicion(10, Posicion::obtenerPiso()-posiblesTiposProt->at(i)->alto);
		Area* sup = new Area(posiblesTiposProt->at(i)->ancho, posiblesTiposProt->at(i)->alto, pos);
		configNivel->manual = new Manual(nombresProt->at(i).c_str(), sup, posiblesTiposProt->at(i)->velocidad, posiblesTiposProt->at(i)->salto);
		configNivel->manual->agregarObservador(vista);
		configNivel->manual->agregarObservador(posiblesTiposProt->at(i)->vistaSonora);
		configNivel->actualizables.push_back(configNivel->manual);
	}

}

Manual* GestorConfiguraciones::ObtenerManual(){
	return configNivel->manual;
}

VistaProtagonista* GestorConfiguraciones::ObtenerVistaManual(){
	return configNivel->vistaManual;
}

Superficie* GestorConfiguraciones::ObtenerFondo(){
	return configNivel->superficieCargada;
}

int GestorConfiguraciones::ObtenerAltoPantalla(){
	return 600;
	//return configPantalla->alto;
}


int GestorConfiguraciones::ObtenerAnchoPantalla(){
	return 800;
	//return configPantalla->ancho;
}

int GestorConfiguraciones::ObtenerAnchoNivel(){
	return configNivel->ancho;
}

int GestorConfiguraciones::ObtenerAltoNivel(){
	return configNivel->alto;
}

int GestorConfiguraciones::ObtenerPisoNivel(){
	return configNivel->piso;
}

int GestorConfiguraciones::ObtenerMargenScroll(){
	return margen_scroll;
}

void GestorConfiguraciones::CargarTexturas(const YAML::Node& nodo){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {

			std::string nombre, ruta;
		    it.first() >> nombre;
		    it.second() >> ruta;

		    if (esCliente)
		    	ruta = headerTemp + ruta;

		    FILE* archiv=fopen(ruta.c_str(),"r");

		    if (!(archiv)){
		    	Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la textura no corresponde con un archivo valido, se carga por defecto");
		    	ruta = TEXTURA_DEFECTO;
		    	if (esCliente)
		    		ruta = headerTemp + ruta;
		    }
		    else
		    	fclose(archiv);

		    texturas -> insert(pair<std::string , std::string>(nombre,ruta));
	}
}


void GestorConfiguraciones::CargarTiposProtagonista(const YAML::Node& nodo, const YAML::Node& protDef){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {
		std::string nombre;
	    it.first() >> nombre;
	    TipoProtagonista* tipoper = _CargarTipoProtagonista(nodo[nombre.c_str()], nombre.c_str());
	    tipoper->nombre=nombre.c_str();
	    tiposProtagonista -> insert(pair<std::string , TipoProtagonista*>(nombre,tipoper));

	}

}

void GestorConfiguraciones::CargarTiposAutomaticos(const YAML::Node& nodo){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {
		std::string nombre;
	    it.first() >> nombre;
	    TipoPersonaje* tipoper = _CargarTipoAutomatico(nodo[nombre.c_str()], nombre.c_str());
	    tipoper->nombre=nombre.c_str();
	    tiposAutomatico -> insert(pair<std::string , TipoPersonaje*>(nombre,tipoper));

	}

}

TipoPersonaje* GestorConfiguraciones::_CargarTipoAutomatico(const YAML::Node& nodo, const char* nombrecito){

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
		if (esCliente)
			rutaPasiva = headerTemp + rutaPasiva;
		rutaActiva = RUTA_ACTIVA;
		if (esCliente)
			rutaPasiva = headerTemp + rutaPasiva;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones dentro del personaje, se cargan por defecto");

		tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		tipoper->animacionesActiva.push_back(  new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto))  );
		tipoper->periodos.push_back(PERIODO_PERSONAJE);
		return tipoper;
	}

	const YAML::Node& animaciones=nodo["animaciones"];

	try{
		animaciones["quieto"];
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		rutaPasiva = RUTA_PASIVA;
		if (esCliente)
			rutaPasiva = headerTemp + rutaPasiva;
		tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		rutaPasiva = RUTA_PASIVA;
		if (esCliente)
			rutaPasiva = headerTemp + rutaPasiva;
		tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}

	if (animaciones.size() == 0){
		rutaPasiva = RUTA_PASIVA;
		if (esCliente)
			rutaPasiva = headerTemp + rutaPasiva;
		rutaActiva = RUTA_ACTIVA;
		if (esCliente)
			rutaActiva = headerTemp + rutaActiva;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay ninguna animacion dentro del personaje, se cargan por defecto");

		tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
		tipoper->animacionesActiva.push_back(  new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto))  );
		tipoper->periodos.push_back(PERIODO_PERSONAJE);
		return tipoper;
	}

	if (animaciones.size() == 1) {
		std::string nombre;
		animaciones.begin().first() >> nombre;
		if (strcmp(nombre.c_str(), "quieto")==0){
			rutaActiva = RUTA_ACTIVA;
			if (esCliente)
				rutaActiva = headerTemp + rutaActiva;
			tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
			tipoper->animacionesActiva.push_back(  new Animacion(new HojaSprites(rutaActiva,tipoper->ancho,tipoper->alto))  );
			tipoper->periodos.push_back(PERIODO_PERSONAJE);
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay animacion activa dentro del personaje, se cargan por defecto");
		}
	}

	int unPeriodo;
	std::string unaRuta;
	vector<std::string> rutas;
	for(YAML::Iterator it=animaciones.begin();it!=animaciones.end();++it) {
		std::string nombre;
		it.first() >> nombre;
		if ( (strcmp(nombre.c_str(),"quieto")==0) ) {
			try{
				animaciones["quieto"]["sprites"] >> rutaPasiva;

				if (esCliente)
					rutaPasiva = headerTemp + rutaPasiva;

				FILE* archiv=fopen(rutaPasiva.c_str(),"r");

				if (!(archiv)){
					Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la animacion pasiva no corresponde con un archivo valido, se carga por defecto");
					rutaPasiva=RUTA_PASIVA;
					if (esCliente)
						rutaPasiva = headerTemp + rutaPasiva;
				}
				else
					fclose(archiv);

				if (!esCliente)
					AgregarAVector(rutaPasiva);

				tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
			}catch( YAML::TypedKeyNotFound<std::string> &e){
				rutaPasiva = RUTA_PASIVA;
				if (esCliente)
					rutaPasiva = headerTemp + rutaPasiva;
				tipoper->animacionPasiva=new Animacion(new HojaSprites(rutaPasiva,tipoper->ancho,tipoper->alto));
				Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo sprites en quieto del personaje, se cargan por defecto");
			}
		}else{
			try{
				animaciones[nombre.c_str()]["sprites"] >> unaRuta;
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

				if (esCliente)
					unaRuta = headerTemp + unaRuta;

				FILE* archivo=fopen(unaRuta.c_str(),"r");

				if (!(archivo)){
					Log::getInstance()->writeToLogFile("ERROR","PARSER: La ruta de la animacion activa no corresponde con un archivo valido, se carga por defecto");
					unaRuta=RUTA_ACTIVA;
					if (esCliente)
						unaRuta = headerTemp + unaRuta;
				}
				else
					fclose(archivo);

				if (!esCliente)
					AgregarAVector(unaRuta);

				tipoper->animacionesActiva.push_back(  new Animacion(new HojaSprites(unaRuta,tipoper->ancho,tipoper->alto))  );
				tipoper->periodos.push_back (unPeriodo);

			}catch( YAML::TypedKeyNotFound<std::string> &e){
				rutaActiva = RUTA_ACTIVA;
				if (esCliente)
					rutaActiva = headerTemp + rutaActiva;

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


TipoProtagonista* GestorConfiguraciones::_CargarTipoProtagonista(const YAML::Node& nodo, const char* nombrecito){

	TipoProtagonista* tipoper= new TipoProtagonista();

	std::string ruta;

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
		nodo["vel_personaje"] >> tipoper->velocidad;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo vel_personaje en personaje, se carga por defecto");
		tipoper->velocidad = VEL_PERSONAJE;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo vel_personaje en personaje, se carga por defecto");
		tipoper->velocidad = VEL_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: La vel_personaje en personaje no toma valor valido, se carga por defecto");
		tipoper->velocidad = VEL_PERSONAJE;
	}

	if (tipoper->velocidad<VEL_PERSONAJE_MINIMA){
		tipoper->velocidad = VEL_PERSONAJE_MINIMA;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: La vel_personaje en personaje toma valor bajo, se carga velocidad de 25");
	}


	try{
		nodo["salto"] >> tipoper->salto;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo salto en personaje, se carga por defecto");
		tipoper->salto = SALTO_PERSONAJE;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo salto en personaje, se carga por defecto");
		tipoper->salto = SALTO_PERSONAJE;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El salto en personaje no toma valor valido, se carga por defecto");
		tipoper->salto = SALTO_PERSONAJE;
	}

	if (tipoper->salto<SALTO_PERSONAJE_MINIMO){
		tipoper->salto = SALTO_PERSONAJE_MINIMO;
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El salto en personaje toma valor bajo, se carga salto de 25");
	}

	try{
		nodo["animaciones"];
	}catch( YAML::Exception &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		ruta = RUTA_ACTIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionActivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		ruta = RUTA_SALTA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionSaltaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones dentro del personaje, se cargan por defecto");
		return tipoper;
	}

	const YAML::Node& animaciones=nodo["animaciones"];



	VistaSonora* vistaSonora = new VistaSonora();


	try{
		animaciones["quieto"]["sprites"] >> ruta;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		AgregarAVector(ruta);
		animaciones["quieto"]["sonido"] >> ruta;
		if (ruta!="~"){

			if (esCliente) ruta=headerTemp+ruta;

			vistaSonora->agregarSonido(ruta, QUIETO);

		}

	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionPasivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones quieto dentro del personaje, se cargan por defecto");
	}

	AgregarAVector(ruta);

	try{
		animaciones["caminar"]["sprites"] >> ruta;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionActivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		AgregarAVector(ruta);
		animaciones["caminar"]["sonido"] >> ruta;
		if (ruta!="~"){

			if (esCliente) ruta=headerTemp+ruta;

			vistaSonora->agregarSonido(ruta, CAMINANDODER);
		}
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionActivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionActivaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}

	AgregarAVector(ruta);

	try{
		animaciones["saltar"]["sprites"] >> ruta;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionSaltaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		AgregarAVector(ruta);
		animaciones["saltar"]["sonido"] >> ruta;
		if (ruta!="~"){

			if (esCliente) ruta=headerTemp+ruta;

			vistaSonora->agregarSonido(ruta, SALTAR);

		}
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		ruta = RUTA_SALTA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionSaltaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones saltar dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		ruta = RUTA_SALTA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionSaltaProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones saltar dentro del personaje, se cargan por defecto");
	}

	AgregarAVector(ruta);
	tipoper->vistaSonora=vistaSonora;

	return tipoper;

}

ConfiguracionPantalla* GestorConfiguraciones::CargarConfiguracionPantalla(int alto, int ancho){

	ConfiguracionPantalla* config= new ConfiguracionPantalla();
	config->alto = alto;
	config->ancho = ancho;

	return config;
}

ConfiguracionPantalla* GestorConfiguraciones::CargarConfiguracionPantalla(const YAML::Node& nodo){

	ConfiguracionPantalla* config= new ConfiguracionPantalla();

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

	return config;
}

Ventana* GestorConfiguraciones::CrearPantalla(){


	return configPantalla->CrearPantalla();

}

std::vector<string>* GestorConfiguraciones::devolverVectorRutas(){



	return vectorRutas;

}

Dummy* GestorConfiguraciones::obtenerDummyMio(){
	return dummy;
}

void GestorConfiguraciones::crearManual(unsigned int id){
	if (!manuales){
		manuales = new ContenedorManuales();
		configNivel->actualizables.push_back(manuales);
	}
	TipoProtagonista* tipo = posiblesTiposProt->at(id);

	int x = id * 80 + tipo->ancho;

	Posicion* pos = new Posicion (x,Posicion::obtenerPiso() - tipo->alto);

	Area* sup = new Area (	tipo->ancho, tipo->alto, pos );

	Manual* nuevoManual = new Manual(tipo->nombre, sup,tipo->velocidad, tipo->salto);
	manuales->agregarManual(nuevoManual, id);
	configNivel->actualizables.push_back(nuevoManual);
}

ContenedorManuales* GestorConfiguraciones::obtenerContenedorManuales(){
	return manuales;
}
