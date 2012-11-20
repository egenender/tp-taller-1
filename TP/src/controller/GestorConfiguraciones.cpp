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
#include "../view/VistaVarios.h"
#include "../model/Observable.h"
#include "../model/Personajes/Princesa.h"
#include "../model/Personajes/Mono.h"
#include "../model/Personajes/Hongo.h"
#include "../model/Personajes/Tortuga.h"
#include "../model/Personajes/Caja.h"
#include "../model/Personajes/Barril.h"
#include "../model/Personajes/PlataformaMovil.h"
#include "../model/Personajes/CamaElastica.h"
#include "../model/Personajes/Tuberia.h"

#include "../model/Fabricas/FabricaActivaEspeciales.h"
#include "../model/Fabricas/FabricaStones.h"
#include "../model/Fabricas/FabricaBarriles.h"
#include "../model/Fabricas/FabricaTortugas.h"
#include "../model/Fabricas/FabricaHongos.h"
#include "../model/Fabricas/FabricaVidasExtra.h"


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
#define TEXTURA_DEFECTO "src/resources/items/viga2.jpg"
#define ALTURA_BOLA 30
#define ANCHO_BOLA 30
#define SALTO_BOLA 15
#define RUTA_BOLA "src/resources/cubosQuieto.bmp"
#define ELEMENTO 1
#define TUBERIA 2
#define CAJA 3


// Puntero estatico para controlar la instanciacion.
GestorConfiguraciones* GestorConfiguraciones::instancia;

GestorConfiguraciones* GestorConfiguraciones::getInstance() {
   if(instancia!=NULL)
	   return instancia;
   instancia = new GestorConfiguraciones();
   return instancia;
}

void GestorConfiguraciones::acabarGestor() {
	destruir = true;
	//instancia = NULL;
}

void GestorConfiguraciones::destruirGestor(){
	if (!destruir) return;
	//aca va all the fucking shit a destruir:

	//destruiyo el mapaParam, que tiene las animaciones (la cosa heavy)
	std::map<std::string, parametrosPersonaje*>::iterator iter;
	parametrosPersonaje* parametros;
	for (iter = mapaParam->begin(); iter != mapaParam->end(); ++iter) {
		 parametros = (*iter).second;
		 destruirParametrosPersonaje(parametros);
		 free(parametros);
	}
	instancia = NULL;
}

void GestorConfiguraciones::destruirParametrosPersonaje(parametrosPersonaje* param){
	std::vector<Animacion*>* anim = param->animaciones;
	for (unsigned int i = 0; i< anim->size(); i++){
		delete (anim->at(i));
	}
	anim->clear();
	delete (anim);

	std::vector<std::vector<int>* >* matriz = param->matrizEstados;
	std::vector<int>* vector;
	for (unsigned int j = 0; j < matriz->size(); j++){
		vector = matriz->at(j);
		vector->clear();
		delete (vector);
	}
	matriz->clear();
	delete (matriz);
}

void GestorConfiguraciones::AgregarAVector(string ruta){


	for (unsigned int i = 0; i < vectorRutas->size(); i++) {
		const char* rutaVector = (vectorRutas->at(i).c_str());
		if (strcmp(rutaVector,ruta.c_str())==0) return;
	}

	vectorRutas->push_back(ruta);

}

GestorConfiguraciones::GestorConfiguraciones (){
	quienGano = 0;
	margen_scroll=0;
	configPantalla=0;
	nivelElegido = 0;
	tiposProtagonista=new mapa_prot();
	tiposAutomatico=new mapa_auto();
	texturas=new mapa_tex();
	vectorRutas=new std::vector<string>();
	manuales = NULL;
	esCliente = esServidor = false;
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
	mapaTub = new mapa_parametrosTuberia();
	mapaCajas = new mapa_parametrosCaja();

	lasCajas = new std::vector<Cuerpo*>();
	lasVistaDeCajas = new std::vector<VistaVarios*>();
	camasElasticas = new std::vector<Cuerpo*>();
	vistasCamasElasticas = new std::vector<VistaVarios*>();
	tuberias = new std::vector<Cuerpo*>();
	vistasTuberias = new std::vector<VistaVarios*>();

	destruir = false;
	contCuerpos = new ContenedorCuerpos();

	IDACT = 0;
}

void GestorConfiguraciones::setEsCliente (){
	esCliente = true;
	rutaYaml = headerTemp + rutaYaml;
	rutaYamlDefecto = headerTemp + rutaYamlDefecto;
}

void GestorConfiguraciones::setEsServidor (){
	esServidor = true;
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
	CargarTuberias(nodoRaiz);
	CargarCajas(nodoRaiz);

}

void GestorConfiguraciones::CargarCajas(const YAML::Node& nodoRaiz){
	int prob;

	//Caja Random
	parametrosCaja* paramCajaR = crearParametrosCaja(nodoRaiz["cajas"]["cajaRandom"],"cajaRandom");

	nodoRaiz["cajas"]["cajaRandom"]["probabilidades"]["vida"] >> prob;
	paramCajaR->probabilidades->push_back( prob );
	nodoRaiz["cajas"]["cajaRandom"]["probabilidades"]["especial"] >> prob;
	paramCajaR->probabilidades->push_back( prob );
	nodoRaiz["cajas"]["cajaRandom"]["probabilidades"]["evolucion"] >> prob;
	paramCajaR->probabilidades->push_back( prob );
	nodoRaiz["cajas"]["cajaRandom"]["probabilidades"]["invencibilidad"] >> prob;
	paramCajaR->probabilidades->push_back( prob );

}


void GestorConfiguraciones::CargarTuberias(const YAML::Node& nodoRaiz){
	//tuberia Hongo-Tortuga arriba
	parametrosTuberia* paramHT= crearParametrosTuberia(nodoRaiz["tuberias"]["tuberiaHTarriba"],"tuberiaHTarriba");
	//tuberia Hongo-Tortuga  abajo
	paramHT= crearParametrosTuberia(nodoRaiz["tuberias"]["tuberiaHTabajo"],"tuberiaHTabajo");
	//tuberia Hongo-Tortuga derecha
	paramHT= crearParametrosTuberia(nodoRaiz["tuberias"]["tuberiaHTderecha"],"tuberiaHTderecha");
	//tuberia Hongo-Tortuga izquierda
	paramHT= crearParametrosTuberia(nodoRaiz["tuberias"]["tuberiaHTizquierda"],"tuberiaHTizquierda");
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

	nodoRaiz["barril"]["animaciones"]["cayendo"]>>ruta;

	Animacion* animacionSaltar= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionSaltar);

	nodoRaiz["barril"]["animaciones"]["quieto"]>>ruta;

	animacionQuieto= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionQuieto);

	nodoRaiz["barril"]["animaciones"]["rodando"]>>ruta;

	animacionCaminando= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionCaminando);

	nodoRaiz["barril"]["animaciones"]["bajando"]>>ruta;

	animacionQuieto= new Animacion(new HojaSprites(ruta,paramBarril->ancho,paramBarril->alto));

	paramBarril->animaciones->push_back(animacionQuieto);

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

	aux= new std::vector<int>();

	aux->push_back(SUBIENDOMOVIMIENTO);

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

	nodoRaiz["vidaExtra"]["animaciones"]["movimiento"]>>ruta;

	Animacion* animacionMov= new Animacion(new HojaSprites(ruta,paramVidaExtra->ancho,paramVidaExtra->alto));

	paramVidaExtra->animaciones->push_back(animacionMov);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramVidaExtra->matrizEstados->push_back(aux);

	//PowerUp Piedra de Evolucion:

	parametrosPersonaje* paramPiedraEvolve= crearParametrosPersonaje(nodoRaiz["piedraEvolucion"],"piedraEvolucion");

	nodoRaiz["piedraEvolucion"]["animaciones"]["movimiento"]>>ruta;

	animacionMov= new Animacion(new HojaSprites(ruta,paramPiedraEvolve->ancho,paramPiedraEvolve->alto));

	paramPiedraEvolve->animaciones->push_back(animacionMov);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramPiedraEvolve->matrizEstados->push_back(aux);

	//PowerUp Activador de Especial:

	parametrosPersonaje* paramAcEsp= crearParametrosPersonaje(nodoRaiz["activaEspecial"],"activaEspecial");

	nodoRaiz["activaEspecial"]["animaciones"]["movimiento"]>>ruta;

	animacionMov= new Animacion(new HojaSprites(ruta,paramAcEsp->ancho,paramAcEsp->alto));

	paramAcEsp->animaciones->push_back(animacionMov);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramAcEsp->matrizEstados->push_back(aux);

	//PowerUp Invencibilidad:

	parametrosPersonaje* paramInvencibilidad= crearParametrosPersonaje(nodoRaiz["invencibilidad"],"invencibilidad");

	nodoRaiz["invencibilidad"]["animaciones"]["movimiento"]>>ruta;

	animacionMov= new Animacion(new HojaSprites(ruta,paramInvencibilidad->ancho,paramInvencibilidad->alto));

	paramInvencibilidad->animaciones->push_back(animacionMov);

	aux= new std::vector<int>();

	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);

	paramInvencibilidad->matrizEstados->push_back(aux);

	//Cama Elastica
	parametrosPersonaje* paramCama= crearParametrosPersonaje(nodoRaiz["camaElastica"],"camaElastica");
	nodoRaiz["camaElastica"]["animaciones"]["quieto"]>>ruta;
	animacionQuieto= new Animacion(new HojaSprites(ruta,paramCama->ancho,paramCama->alto));
	paramCama->animaciones->push_back(animacionQuieto);

	nodoRaiz["camaElastica"]["animaciones"]["lanza"]>>ruta;
	Animacion* animacionLanza= new Animacion(new HojaSprites(ruta,paramCama->ancho,paramCama->alto));
	paramCama->animaciones->push_back(animacionLanza);

	aux= new std::vector<int>();
	aux->push_back(QUIETO);
	paramCama->matrizEstados->push_back(aux);
	aux= new std::vector<int>();
	aux->push_back(LANZANDO);
	paramCama->matrizEstados->push_back(aux);

	//Plataforma Movil

	parametrosPersonaje* paramPlataMovil= crearParametrosPersonaje(nodoRaiz["plataformaMovil"],"plataformaMovil");
	nodoRaiz["plataformaMovil"]["distancia"] >> paramPlataMovil->algo;

	nodoRaiz["plataformaMovil"]["animaciones"]["plataforma"]>>ruta;
	animacionQuieto= new Animacion(new HojaSprites( ruta ,paramPlataMovil->ancho,paramPlataMovil->alto));
	paramPlataMovil->animaciones->push_back(animacionQuieto);

	aux= new std::vector<int>();
	aux->push_back(QUIETO);
	paramPlataMovil->matrizEstados->push_back(aux);

	//Elevador

	parametrosPersonaje* paramElevador= crearParametrosPersonaje(nodoRaiz["elevador"],"elevador");
	nodoRaiz["elevador"]["distancia"] >> paramElevador->algo;

	nodoRaiz["elevador"]["animaciones"]["elevador"]>>ruta;
	animacionQuieto= new Animacion(new HojaSprites(ruta,paramElevador->ancho,paramElevador->alto));
	paramElevador->animaciones->push_back(animacionQuieto);

	aux= new std::vector<int>();
	aux->push_back(QUIETO);
	paramElevador->matrizEstados->push_back(aux);

}

parametrosCaja* GestorConfiguraciones::crearParametrosCaja(const YAML::Node& nodo, string nombre){

	parametrosCaja* param= (parametrosCaja*)malloc(sizeof(parametrosCaja));

	param->probabilidades= new std::vector<int>();

	std::string ruta;

	nodo["alto"]>>param->alto;
	nodo["ancho"]>>param->ancho;

	nodo["animaciones"]["laCajaLaCaja"] >> ruta;
	param->quieto = new Animacion(new HojaSprites(ruta , param->ancho, param->alto));
	nodo["animaciones"]["destruida"] >> ruta;
	param->lanzando = new Animacion(new HojaSprites(ruta , param->ancho, param->alto));

	mapaCajas->insert(pair<string,parametrosCaja*>(nombre,param));


	parametrosPersonaje* paramPer = (parametrosPersonaje*)malloc(sizeof(parametrosPersonaje));
	paramPer->animaciones= new std::vector<Animacion*>();
	paramPer->matrizEstados= new std::vector<std::vector<int>*>();

	nodo["alto"]>>paramPer->alto;
	nodo["ancho"]>>paramPer->ancho;

	nodo["animaciones"]["laCajaLaCaja"] >> ruta;
	Animacion* animacionQ= new Animacion(new HojaSprites(ruta,paramPer->ancho,paramPer->alto));
	paramPer->animaciones->push_back(animacionQ);
	std::vector<int>* aux= new std::vector<int>();
	aux->push_back(QUIETO);
	paramPer->matrizEstados->push_back(aux);

	nodo["animaciones"]["destruida"] >> ruta;
	Animacion* animacionL= new Animacion(new HojaSprites(ruta,paramPer->ancho,paramPer->alto));
	paramPer->animaciones->push_back(animacionL);
	aux= new std::vector<int>();
	aux->push_back(LANZANDO);
	paramPer->matrizEstados->push_back(aux);

	mapaParam->insert(pair<string,parametrosPersonaje*>(nombre,paramPer));

	return param;
}


parametrosTuberia* GestorConfiguraciones::crearParametrosTuberia(const YAML::Node& nodo, string nombre){

	parametrosTuberia* paramTub= (parametrosTuberia*)malloc(sizeof(parametrosTuberia));

	nodo["alto"]>>paramTub->alto;
	nodo["ancho"]>>paramTub->ancho;

	mapaTub->insert(pair<string,parametrosTuberia*>(nombre,paramTub));

	std::string ruta;
	nodo["animaciones"]["tuberia"] >> ruta;
	paramTub->superficie = new Superficie(ruta);
	paramTub->superficie->escala(paramTub->ancho,paramTub->alto);
	paramTub->superficie->transparencia(255,0,255);


	parametrosPersonaje* paramPer = (parametrosPersonaje*)malloc(sizeof(parametrosPersonaje));
	paramPer->animaciones= new std::vector<Animacion*>();
	paramPer->matrizEstados= new std::vector<std::vector<int>*>();


	nodo["alto"]>>paramPer->alto;
	nodo["ancho"]>>paramPer->ancho;

	Animacion* animacionT= new Animacion(new HojaSprites(ruta,paramPer->ancho,paramPer->alto));
	paramPer->animaciones->push_back(animacionT);
	std::vector<int>* aux= new std::vector<int>();
	aux->push_back(QUIETO);
	paramPer->matrizEstados->push_back(aux);

	mapaParam->insert(pair<string,parametrosPersonaje*>(nombre,paramPer));
	return paramTub;
}

parametrosPersonaje* GestorConfiguraciones::crearParametrosPersonaje(const YAML::Node& nodo, string nombre){

	parametrosPersonaje* param= (parametrosPersonaje*)malloc(sizeof(parametrosPersonaje));

	param->animaciones= new std::vector<Animacion*>();
	param->matrizEstados= new std::vector<std::vector<int>*>();

	param->algo = 0;

	nodo["alto"]>>param->alto;
	nodo["ancho"]>>param->ancho;
	nodo["velocidad"]>>param->velocidad;

	mapaParam->insert(pair<string,parametrosPersonaje*>(nombre,param));

	return param;
}

parametrosPersonaje* GestorConfiguraciones::obtenerParametrosPersonaje(string nombre){

	return mapaParam->at(nombre);

}

void GestorConfiguraciones::crearVistaTuberia(Cuerpo* cuerpo,string clave, int dir){
	if (!esCliente && !esServidor){
		VistaImagen* vista = new VistaImagen(mapaTub->at(clave)->superficie);
		configNivel->actualizables.push_back((Cuerpo*)cuerpo);
		cuerpo->agregarObservador(vista);
		configNivel->vistas.push_back(vista);
		return ;
	}

	crearVistaElemento(cuerpo, clave);

}


VistaVarios* GestorConfiguraciones::crearVistaProt(string clave){

	parametrosPersonaje* paramPersonaje=mapaParam->at(clave);
	VistaVarios* vista=new VistaVarios();
	for (unsigned int i =0; i<paramPersonaje->animaciones->size();i++){

		if (paramPersonaje->matrizEstados->at(i)->size()==1){
			vista->agregarEstadoSoportado(paramPersonaje->matrizEstados->at(i)->at(0),paramPersonaje->animaciones->at(i));
		}else{
			vista->agregarEstadoSoportadoEInverso(paramPersonaje->matrizEstados->at(i)->at(0),paramPersonaje->matrizEstados->at(i)->at(1),paramPersonaje->animaciones->at(i));

		}
	}

	return vista;
}

void GestorConfiguraciones::crearVistaElemento(Observable* cuerpo,string clave, bool esCuerpo){
	printf("clave: %s\n", clave.c_str());

	parametrosPersonaje* paramPersonaje=mapaParam->at(clave);
	VistaVarios* vista = new VistaVarios();
	if (!esServidor){

		for (unsigned int i =0; i<paramPersonaje->animaciones->size();i++){

			if (paramPersonaje->matrizEstados->at(i)->size()==1){
				vista->agregarEstadoSoportado(paramPersonaje->matrizEstados->at(i)->at(0),paramPersonaje->animaciones->at(i));
			}else{
				vista->agregarEstadoSoportadoEInverso(paramPersonaje->matrizEstados->at(i)->at(0),paramPersonaje->matrizEstados->at(i)->at(1),paramPersonaje->animaciones->at(i));

			}
		}

	}

	if ( strcmp(clave.c_str() , "plataformaMovil") == 0 ){
		YAML::Node nodoRaiz;
		std::ifstream fin(rutaYaml.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodoRaiz);
		std::string ruta;
		nodoRaiz["juego"]["plataformaMovil"]["animaciones"]["plataforma"] >> ruta;
		Superficie* sup = new Superficie(ruta);
		sup->escala(mapaParam->at(clave)->ancho,mapaParam->at(clave)->alto);
		VistaImagen* vi = new VistaImagen(sup);
		if (esCuerpo)
				configNivel->actualizables.push_back((Cuerpo*)cuerpo);
		cuerpo->agregarObservador(vi);
		configNivel->vistas.push_back(vi);
		if (esServidor){
			Cuerpo* c = (Cuerpo*) cuerpo;
			c->setearID(IDACT);
			IDACT++;
			cuerpo->agregarObservador(contCuerpos);
			delete (vista);
		}
		return ;
	}

	if ( strcmp(clave.c_str() , "elevador") == 0 ){
		YAML::Node nodoRaiz;
		std::ifstream fin(rutaYaml.c_str());
		YAML::Parser parser(fin);
		parser.GetNextDocument(nodoRaiz);
		std::string ruta;
		nodoRaiz["juego"]["elevador"]["animaciones"]["elevador"] >> ruta;
		Superficie* sup = new Superficie(ruta);
		sup->escala(mapaParam->at(clave)->ancho,mapaParam->at(clave)->alto);
		VistaImagen* vi = new VistaImagen(sup);
		if (esCuerpo)
			configNivel->actualizables.push_back((Cuerpo*)cuerpo);
		cuerpo->agregarObservador(vi);
		configNivel->vistas.push_back(vi);
		if (esServidor){
			Cuerpo* c = (Cuerpo*) cuerpo;
			c->setearID(IDACT);
			IDACT++;
			cuerpo->agregarObservador(contCuerpos);
			delete (vista);
		}
		return ;
	}


	if (esCuerpo)
		configNivel->actualizables.push_back((Cuerpo*)cuerpo);

	if (esServidor){
		Cuerpo* c = (Cuerpo*) cuerpo;
		c->setearID(IDACT);
		IDACT++;
		cuerpo->agregarObservador(contCuerpos);
		delete (vista);
	}else{
		cuerpo->agregarObservador(vista);
		configNivel->vistas.push_back(vista);
	}
}

void GestorConfiguraciones::crearVistaCaja(Cuerpo* cuerpo,string clave){

	parametrosCaja* paramCaja = mapaCajas->at(clave);

	VistaVarios* vista=new VistaVarios();
	vista->agregarEstadoSoportado(QUIETO , paramCaja->quieto);
	vista->agregarEstadoSoportado(LANZANDO , paramCaja->lanzando);

	//configNivel->actualizables.push_back(cuerpo);
	//cuerpo->agregarObservador(vista);
	//configNivel->vistas.push_back(vista);

	lasCajas->push_back( cuerpo );
	lasVistaDeCajas->push_back( vista );

	if (esServidor){
		cuerpo->setearID(IDACT);
		IDACT++;
		cuerpo->agregarObservador(contCuerpos);
	}
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
	IDACT = posiblesTiposProt->size() + 3;
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
		nodo[nivelElegido]["players"] >> configNivel->players;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo players dentro del nivel, se carga por defecto");
		configNivel->players = 2;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El valor de players no toma valor valido, se carga por defecto");
		configNivel->players = 2;
	}

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
	VistaImagen * vista;
	for(unsigned i=0;i<nodo[nivelElegido]["vigas"].size();i++) {

		nodo[nivelElegido]["vigas"][i]["textura"] >> tex;
		nodo[nivelElegido]["vigas"][i]["ancho"]>> ancho;
		nodo[nivelElegido]["vigas"][i]["alto"]>> alto;
		nodo[nivelElegido]["vigas"][i]["inclinacion"]>> inclinacion;
		nodo[nivelElegido]["vigas"][i]["x"]>> x;
		nodo[nivelElegido]["vigas"][i]["y"]>> y;


		VigaInclinada* viga= new VigaInclinada("viga",new Area(ancho,alto,new Posicion(x,y)),inclinacion);

		viga->guardarSubPlataformas(&configNivel->actualizables);

		configNivel->actualizables.push_back(viga);

		rutaImagen = texturas->at(tex);
		Superficie* sup = new Superficie(rutaImagen);
		sup->escala(ancho,alto);
		vista = new VistaImagen(sup,-inclinacion);

		configNivel->vistas.push_back(vista);

		viga->agregarObservador(vista);

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

	if (!esCliente){
		try{
			CargarElementosNivel(nodo[nivelElegido]["elementos"], ELEMENTO);
			Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de los elementos del nivel");
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo elementos");
		}

		try{
			CargarTuberiasNivel(nodo[nivelElegido]["tuberias"]);
			Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de las tuberias del nivel");
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tuberias");
		}

		try{
			CargarCajasNivel(nodo[nivelElegido]["cajas"]);
			Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de las cajas del nivel");
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo cajas");
		}
	}
	if ( esCliente ){
		CargarVistasTuberias(nodo[nivelElegido]["tuberias"]);
	}

//	try{
//		CargarPersonajesNivel(nodo[nivelElegido]["personajes"]);
//		Log::getInstance()->writeToLogFile("INFO","PARSER: Se cargaron configuraciones de los personajes del nivel");
//	}catch(YAML::TypedKeyNotFound<std::string> &e){
//		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo personajes, se cargan por defecto");
//		CargarPersonajesNivel(defPersonajes);
//	}

}

unsigned int GestorConfiguraciones::obtenerCantidadDeJugadores (){
	return configNivel->players;
}


void GestorConfiguraciones::CargarVistasTuberias(const YAML::Node& tubs){
	Plataforma* plat;
	std::string tipo;
	int posX,posY;
	for(unsigned i=0;i<tubs.size();i++) {
		try{
			tubs[i]["tipo"] >> tipo;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tipo del elemento, se carga por defecto");
			tipo = TIPO_DEFECTO;
		}

		try{
			tubs[i]["x"] >> posX;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo x dentro del elemento, se carga por defecto");
			posX = POS_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x no toma valor valido, se carga por defecto");
			posX = POS_DEFECTO;
		}
		if (posX<0 || posX>= configNivel->ancho){
			posX=POS_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x del elemento no toma valor valido, se carga por defecto");
		}

		try{
			tubs[i]["y"] >> posY;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo y dentro del elemento, se carga por defecto");
			posY = POS_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y no toma valor valido, se carga por defecto");
			posY = POS_DEFECTO;
		}
		if (posY<0 || posY>=configNivel->alto){
			posY=POS_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y del elemento no toma valor valido, se carga por defecto");
		}

		int x,y;
		int ancho, alto;

		ancho = mapaParam->at(tipo)->ancho;
		alto = mapaParam->at(tipo)->alto;

		//el posX posY indica el punto inferior central del personaje (consigna)
		x = posX - ( ancho/2 );
		y = posY - alto;
		plat = new Plataforma("plat", new Area (ancho, alto, new Posicion (x,y)) );
		VistaImagen* vista = new VistaImagen(mapaTub->at(tipo)->superficie);
		configNivel->vistas.push_back(vista);
		plat->agregarObservador(vista);
		//configNivel->actualizables.push_back(plat);
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
			estatico = new Escalera("escalera", new Area(ancho,alto,new Posicion(posX,posY) ) );
		else
			estatico = new Plataforma("plat", new Area(ancho,alto,new Posicion(posX,posY) ) );
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

void GestorConfiguraciones::CargarTuberiasNivel(const YAML::Node& tuberias){
	CargarElementosNivel(tuberias, TUBERIA);
}

void GestorConfiguraciones::CargarCajasNivel(const YAML::Node& cajas){
	CargarElementosNivel(cajas, CAJA);
}

void GestorConfiguraciones::CargarElementosNivel(const YAML::Node& elementos, int tipoElem){
	std::string tipo, direccion;
	int posX,posY, m, dir;
	Cuerpo* cuerpo;
	for(unsigned i=0;i<elementos.size();i++) {
		try{
			elementos[i]["tipo"] >> tipo;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo tipo del elemento, se carga por defecto");
			tipo = TIPO_DEFECTO;
		}

		if(tipoElem == TUBERIA){
			try{
				elementos[i]["direccion"] >> direccion;
				if (strcmp("abajo", direccion.c_str())==0)
					dir = 2;
				if (strcmp("arriba", direccion.c_str())==0)
					dir = -2;
				if (strcmp("derecha", direccion.c_str())==0)
					dir = 1;
				if (strcmp("izquierda", direccion.c_str())==0)
					dir = -1;
			}catch(YAML::TypedKeyNotFound<std::string> &e){
				dir = 2;
			}catch(YAML::InvalidScalar &e){
				dir = 2;
			}
			try{
				elementos[i]["eme"] >> m;
			}catch(YAML::TypedKeyNotFound<std::string> &e){
				m = 5;
			}catch(YAML::InvalidScalar &e){
				m = 5;
			}
		}

		try{
			elementos[i]["x"] >> posX;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo x dentro del elemento, se carga por defecto");
			posX = POS_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x no toma valor valido, se carga por defecto");
			posX = POS_DEFECTO;
		}
		if (posX<0 || posX>= configNivel->ancho){
			posX=POS_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El x del elemento no toma valor valido, se carga por defecto");
		}

		try{
			elementos[i]["y"] >> posY;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo y dentro del elemento, se carga por defecto");
			posY = POS_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y no toma valor valido, se carga por defecto");
			posY = POS_DEFECTO;
		}
		if (posY<0 || posY>=configNivel->alto){
			posY=POS_DEFECTO;
			Log::getInstance()->writeToLogFile("ERROR","PARSER: El y del elemento no toma valor valido, se carga por defecto");
		}

		int x,y;
		int ancho, alto;

		//debo asegurarme de que pasen un tipo de personaje que ya exista:
		//try{
			if(tipoElem == ELEMENTO){
				ancho = mapaParam->at(tipo)->ancho;
				alto = mapaParam->at(tipo)->alto;
			}
			if(tipoElem == TUBERIA){
				ancho = mapaTub->at(tipo)->ancho;
				alto = mapaTub->at(tipo)->alto;
			}
			if(tipoElem == CAJA){
				ancho = mapaCajas->at(tipo)->ancho;
				alto = mapaCajas->at(tipo)->alto;
			}
			//el posX posY indica el punto inferior central del personaje (consigna)
			x = posX - ( ancho/2 );
			y = posY - alto;
			//veo si entra en el nivel
			if (!Entra(x,y,ancho,alto)){
				if (!Entra(0,0,ancho,alto)){
					ancho = ANCHO_PERSONAJE;
					alto = ALTO_PERSONAJE;
					if(tipoElem == ELEMENTO){
						mapaParam->at(tipo)->ancho = ANCHO_PERSONAJE;
						mapaParam->at(tipo)->alto = ALTO_PERSONAJE;
					}
					if(tipoElem == TUBERIA){
						mapaTub->at(tipo)->ancho = ANCHO_PERSONAJE;
						mapaTub->at(tipo)->alto = ALTO_PERSONAJE;
					}
					if(tipoElem == CAJA){
						mapaCajas->at(tipo)->ancho = ANCHO_PERSONAJE;
						mapaCajas->at(tipo)->alto = ALTO_PERSONAJE;
					}
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

			if(tipoElem == ELEMENTO){
				cuerpo = instanciarCuerpo(tipo, x, y);
				this->crearVistaElemento(cuerpo,tipo);
			}
			if(tipoElem == TUBERIA){
				cuerpo = instanciarTuberia(tipo, x, y, m , dir);
				this->crearVistaTuberia(cuerpo,tipo, dir);
			}
			if(tipoElem == CAJA){
				cuerpo = instanciarCaja(tipo, x, y);
				this->crearVistaCaja(cuerpo,tipo);
			}
		//}catch(std::out_of_range &e){
			//si no hay, por defecto
		//}
	}

}

Cuerpo* GestorConfiguraciones::instanciarCaja(std::string tipo, int x, int y){
	if( strcmp ( tipo.c_str() , "cajaRandom" ) == 0 )
		return new Caja("cajaRandom", new Area(mapaCajas->at(tipo)->ancho,mapaCajas->at(tipo)->alto, new Posicion(x,y) ) , new FabricaPowerUps() );
	return NULL;
}

Cuerpo* GestorConfiguraciones::instanciarTuberia(std::string tipo, int x, int y, float m, int dir){
	std::vector<int>* probabilidades = new std::vector<int>;
	probabilidades->push_back(50);
	probabilidades->push_back(50);
	if( strcmp ( tipo.c_str() , "tuberiaHTarriba" ) == 0 ){
		std::vector<FabricaActualizable*>* fabrs = new std::vector<FabricaActualizable*>();
		fabrs->push_back(new FabricaHongos());
		fabrs->push_back(new FabricaTortugas());
		return new Tuberia("tuberiaHTarriba", new Area(mapaTub->at(tipo)->ancho,mapaTub->at(tipo)->alto, new Posicion(x,y) ), m , -2, probabilidades, fabrs );
	}
	if( strcmp ( tipo.c_str() , "tuberiaHTabajo" ) == 0 ){
		std::vector<FabricaActualizable*>* fabrs = new std::vector<FabricaActualizable*>();
		fabrs->push_back(new FabricaHongos());
		fabrs->push_back(new FabricaTortugas());
		return new Tuberia("tuberiaHTabajo", new Area(mapaTub->at(tipo)->ancho,mapaTub->at(tipo)->alto, new Posicion(x,y) ), m , 2, probabilidades, fabrs );
	}
	if( strcmp ( tipo.c_str() , "tuberiaHTderecha" ) == 0 ){
		std::vector<FabricaActualizable*>* fabrs = new std::vector<FabricaActualizable*>();
		fabrs->push_back(new FabricaHongos());
		fabrs->push_back(new FabricaTortugas());
		return new Tuberia("tuberiaHTderecha", new Area(mapaTub->at(tipo)->ancho,mapaTub->at(tipo)->alto, new Posicion(x,y) ), m , 1, probabilidades, fabrs );
	}
	if( strcmp ( tipo.c_str() , "tuberiaHTizquierda" ) == 0 ){
		std::vector<FabricaActualizable*>* fabrs = new std::vector<FabricaActualizable*>();
		fabrs->push_back(new FabricaHongos());
		fabrs->push_back(new FabricaTortugas());
		return new Tuberia("tuberiaHTizquierda", new Area(mapaTub->at(tipo)->ancho,mapaTub->at(tipo)->alto, new Posicion(x,y) ), m , -1, probabilidades, fabrs );
	}
	return NULL;
}

Cuerpo* GestorConfiguraciones::instanciarCuerpo(std::string tipo, int x, int y){
	if( strcmp ( tipo.c_str() , "princesa" ) == 0 )
		return new Princesa("princesa",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto, new Posicion(x,y)), mapaParam->at(tipo)->velocidad);
	if( strcmp ( tipo.c_str() , "hongo" ) == 0 )
		return new Hongo("hongo",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto, new Posicion(x,y)), mapaParam->at(tipo)->velocidad);
	if( strcmp ( tipo.c_str() , "tortuga" ) == 0 )
		return new Tortuga("tortuga",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto, new Posicion(x,y)), mapaParam->at(tipo)->velocidad);
	if( strcmp ( tipo.c_str() , "mono" ) == 0 )
		return new Mono("mono",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto, new Posicion(x,y)), new FabricaBarriles(),mapaParam->at(tipo)->velocidad);
	if( strcmp ( tipo.c_str() , "barril" ) == 0 )
			return new Barril("barril",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto, new Posicion(x,y)), mapaParam->at(tipo)->velocidad, 1);
	if( strcmp ( tipo.c_str() , "camaElastica" ) == 0 )
		return new CamaElastica("camaElastica",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto,new Posicion(x,y)));
	if( strcmp ( tipo.c_str() , "plataformaMovil" ) == 0 )
		return new PlataformaMovil("plataformaMovil",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto,new Posicion(x,y)), mapaParam->at(tipo)->velocidad, mapaParam->at(tipo)->algo );
	if( strcmp ( tipo.c_str() , "elevador" ) == 0 ){
		PlataformaMovil* p = new PlataformaMovil("elevador",new Area(mapaParam->at(tipo)->ancho,mapaParam->at(tipo)->alto,new Posicion(x,y)), mapaParam->at(tipo)->velocidad, mapaParam->at(tipo)->algo );
		p->setearElevador();
		return p;
	}
	return NULL;
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

	VistaVarios* vistaProt = this->crearVistaProt(nombre);
	configNivel->vistas.push_back(vistaProt);
	configNivel->vistas.push_back(posiblesTiposProt->at(i)->vistaSonora);
	if (esCliente){
		dummy = new Dummy(i, new Posicion(50,50), posiblesTiposProt->at(i)->ancho, posiblesTiposProt->at(i)->alto);
		dummy->agregarObservador(vistaProt);
		dummy->agregarObservador(posiblesTiposProt->at(i)->vistaSonora);
		contenedor = new ContenedorDummy();
		contenedor->agregarDummy(dummy);
		configNivel->actualizables.push_back(contenedor);
	}else{
		Posicion* pos = new Posicion(10, Posicion::obtenerPiso()-posiblesTiposProt->at(i)->alto);
		Area* sup = new Area(posiblesTiposProt->at(i)->ancho, posiblesTiposProt->at(i)->alto, pos);
		configNivel->manual = new Manual(nombresProt->at(i).c_str(), sup, posiblesTiposProt->at(i)->velocidad, posiblesTiposProt->at(i)->salto);
		configNivel->manual->setearID(i);
		configNivel->actualizables.push_back(configNivel->manual);

		if (esServidor)
			configNivel->manual->agregarObservador(contCuerpos);
		else{
			configNivel->manual->agregarObservador(vistaProt);
			configNivel->manual->agregarObservador(posiblesTiposProt->at(i)->vistaSonora);
		}
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

	parametrosPersonaje *param = (parametrosPersonaje*)malloc (sizeof(parametrosPersonaje));

	try{
		nodo["poster"] >> tipoper->rutaGanador;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo poster dentro del personaje, se carga por defecto");
		tipoper->rutaGanador = RUTA_ACTIVA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: El poster no toma valor valido, se carga por defecto");
		tipoper->rutaGanador = RUTA_ACTIVA;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo poster, se carga por defecto");
		tipoper->rutaGanador = RUTA_ACTIVA;
	}

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
	param->ancho = tipoper->ancho;

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
	param->alto = tipoper->alto;

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
	param->velocidad = tipoper->velocidad;

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
		//Faltan las animaciones de subir escalera y que quede quieto + todas en modo evolucion
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


	try{
		animaciones["escalera"]["sprites"] >> ruta;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionEscaleraProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		AgregarAVector(ruta);
		animaciones["escalera"]["sonido"] >> ruta;
		if (ruta!="~"){

			if (esCliente) ruta=headerTemp+ruta;

			vistaSonora->agregarSonido(ruta, SUBIENDOQUIETO);
		}
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionEscaleraProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionEscaleraProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}

	AgregarAVector(ruta);

	try{
		animaciones["escalar"]["sprites"] >> ruta;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionEscalarProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		AgregarAVector(ruta);
		animaciones["escalar"]["sonido"] >> ruta;
		if (ruta!="~"){

			if (esCliente) ruta=headerTemp+ruta;

			vistaSonora->agregarSonido(ruta, SUBIENDOMOVIMIENTO);
		}
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionEscalarProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionEscalarProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}

	AgregarAVector(ruta);


	try{
		animaciones["herido"]["sprites"] >> ruta;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionHeridoProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		tipoper->animacionHeridoEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		AgregarAVector(ruta);
		animaciones["herido"]["sonido"] >> ruta;
		if (ruta!="~"){

			if (esCliente) ruta=headerTemp+ruta;

			vistaSonora->agregarSonido(ruta, HERIDO);
		}
	}catch( YAML::TypedKeyNotFound<std::string> &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionHeridoProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		tipoper->animacionHeridoEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

		Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}catch( YAML::Exception &e) {
		ruta = RUTA_PASIVA;
		if (esCliente)
			ruta = headerTemp + ruta;
		tipoper->animacionHeridoProt=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		tipoper->animacionHeridoEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
		Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
	}

	AgregarAVector(ruta);



	try{
			animaciones["evoquieto"]["sprites"] >> ruta;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionPasivaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			AgregarAVector(ruta);
			animaciones["evoquieto"]["sonido"] >> ruta;
			if (ruta!="~"){

				if (esCliente) ruta=headerTemp+ruta;

				vistaSonora->agregarSonido(ruta, QUIETO);

			}

		}catch( YAML::TypedKeyNotFound<std::string> &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionPasivaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones quieto dentro del personaje, se cargan por defecto");
		}catch( YAML::Exception &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionPasivaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones quieto dentro del personaje, se cargan por defecto");
		}

		AgregarAVector(ruta);

		try{
			animaciones["evocaminar"]["sprites"] >> ruta;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionActivaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			AgregarAVector(ruta);
			animaciones["evocaminar"]["sonido"] >> ruta;
			if (ruta!="~"){

				if (esCliente) ruta=headerTemp+ruta;

				vistaSonora->agregarSonido(ruta, CAMINANDODER);
			}
		}catch( YAML::TypedKeyNotFound<std::string> &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionActivaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
		}catch( YAML::Exception &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionActivaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
		}

		AgregarAVector(ruta);

		try{
			animaciones["evosaltar"]["sprites"] >> ruta;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionSaltaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			AgregarAVector(ruta);
			animaciones["evosaltar"]["sonido"] >> ruta;
			if (ruta!="~"){

				if (esCliente) ruta=headerTemp+ruta;

				vistaSonora->agregarSonido(ruta, SALTAR);

			}
		}catch( YAML::TypedKeyNotFound<std::string> &e) {
			ruta = RUTA_SALTA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionSaltaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones saltar dentro del personaje, se cargan por defecto");
		}catch( YAML::Exception &e) {
			ruta = RUTA_SALTA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionSaltaEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones saltar dentro del personaje, se cargan por defecto");
		}

		AgregarAVector(ruta);


		try{
			animaciones["evoescalera"]["sprites"] >> ruta;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionEscaleraEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			AgregarAVector(ruta);
			animaciones["evoescalera"]["sonido"] >> ruta;
			if (ruta!="~"){

				if (esCliente) ruta=headerTemp+ruta;

				vistaSonora->agregarSonido(ruta, SUBIENDOQUIETO);
			}
		}catch( YAML::TypedKeyNotFound<std::string> &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionEscaleraEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
		}catch( YAML::Exception &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionEscaleraEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
		}

		AgregarAVector(ruta);

		try{
			animaciones["evoescalar"]["sprites"] >> ruta;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionEscalarEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			AgregarAVector(ruta);
			animaciones["evoescalar"]["sonido"] >> ruta;
			if (ruta!="~"){

				if (esCliente) ruta=headerTemp+ruta;

				vistaSonora->agregarSonido(ruta, SUBIENDOMOVIMIENTO);
			}
		}catch( YAML::TypedKeyNotFound<std::string> &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionEscalarEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));

			Log::getInstance()->writeToLogFile("ERROR","PARSER: No hay nodo animaciones caminar dentro del personaje, se cargan por defecto");
		}catch( YAML::Exception &e) {
			ruta = RUTA_PASIVA;
			if (esCliente)
				ruta = headerTemp + ruta;
			tipoper->animacionEscalarEvo=new Animacion(new HojaSprites(ruta,tipoper->ancho,tipoper->alto));
			Log::getInstance()->writeToLogFile("ERROR","PARSER: Problemas con nodo animaciones caminar dentro del personaje, se cargan por defecto");
		}

		AgregarAVector(ruta);



	tipoper->vistaSonora=vistaSonora;

	//debe copiarse luego tambien en la zona donde debe cargarse el default
	param->animaciones = new std::vector<Animacion*>();
	param->matrizEstados = new std::vector<vector<int>*>();

	vector<int>* aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionPasivaProt);
	aux->push_back(QUIETODER);
	aux->push_back(QUIETOIZQ);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionActivaProt);
	aux->push_back(CAMINANDODER);
	aux->push_back(CAMINANDOIZQ);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionSaltaProt);
	aux->push_back(SALTANDODER);
	aux->push_back(SALTANDOIZQ);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionEscaleraProt);
	aux->push_back(SUBIENDOQUIETO);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionEscalarProt);
	aux->push_back(SUBIENDOMOVIMIENTO);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionHeridoProt);
	aux->push_back(HERIDO);
	param->matrizEstados->push_back(aux);


	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionPasivaEvo);
	aux->push_back(EVOLUCION + QUIETODER);
	aux->push_back(EVOLUCION + QUIETOIZQ);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionActivaEvo);
	aux->push_back(EVOLUCION + CAMINANDODER);
	aux->push_back(EVOLUCION + CAMINANDOIZQ);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionSaltaEvo);
	aux->push_back(EVOLUCION + SALTANDODER);
	aux->push_back(EVOLUCION + SALTANDOIZQ);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionEscaleraEvo);
	aux->push_back(EVOLUCION + SUBIENDOQUIETO);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionEscalarEvo);
	aux->push_back(EVOLUCION + SUBIENDOMOVIMIENTO);
	param->matrizEstados->push_back(aux);

	aux = new vector<int>();
	param->animaciones->push_back(tipoper->animacionHeridoEvo);
	aux->push_back(EVOLUCION + HERIDO);
	param->matrizEstados->push_back(aux);


	std::string n = nombrecito;
	mapaParam->insert(pair<string, parametrosPersonaje*>(n, param));

	/*INTENTO DE LEVANTAR BOLAS DE FUEGO*/
	parametrosPersonaje *bola = (parametrosPersonaje*) malloc (sizeof(parametrosPersonaje));

	try{
		nodo["bolaDeFuego"]["ancho"] >> bola->ancho;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de ancho de la bola de fuego, se carga por defecto");
		bola->ancho = ANCHO_BOLA;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de ancho de la bola de fuego, se carga por defecto");
		bola->ancho = ANCHO_BOLA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de ancho de la bola de fuego, se carga por defecto");
		bola->ancho = ANCHO_BOLA;
	}

	try{
		nodo["bolaDeFuego"]["alto"] >> bola->alto;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de altura de la bola de fuego, se carga por defecto");
		bola->alto = ALTURA_BOLA;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de altura de la bola de fuego, se carga por defecto");
		bola->alto = ALTURA_BOLA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de altura de la bola de fuego, se carga por defecto");
		bola->alto = ALTURA_BOLA;
	}


	try{
		nodo["bolaDeFuego"]["salto"] >> bola->velocidad;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de salto de la bola de fuego, se carga por defecto");
		bola->velocidad = SALTO_BOLA;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de salto de la bola de fuego, se carga por defecto");
		bola->velocidad = SALTO_BOLA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de salto de la bola de fuego, se carga por defecto");
		bola->velocidad = SALTO_BOLA;
	}

	try{
		nodo["bolaDeFuego"]["animacion"] >> ruta;
	}catch(YAML::BadDereference &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de animacion de la bola de fuego, se carga por defecto");
		ruta = RUTA_BOLA;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de animacion de la bola de fuego, se carga por defecto");
		ruta = RUTA_BOLA;
	}catch(YAML::InvalidScalar &e){
		Log::getInstance()->writeToLogFile("ERROR","PARSER: no hay nodo de animacion de la bola de fuego, se carga por defecto");
		ruta = RUTA_BOLA;
	}
	if (esCliente)
		ruta = headerTemp + ruta;
	AgregarAVector(ruta);

	Animacion* animacionBola = new Animacion(new HojaSprites(ruta, bola->ancho, bola->alto));
	bola->animaciones = new std::vector<Animacion*>();
	bola->animaciones->push_back(animacionBola);
	bola->matrizEstados = new std::vector<vector<int>*>();
	aux = new std::vector<int>();
	aux->push_back(SALTANDODER);
	aux->push_back(SALTANDOIZQ);
	bola->matrizEstados->push_back(aux);
	std::string b = "bola";
	b += n;
	mapaParam->insert(pair<std::string, parametrosPersonaje*>(b,bola));


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

	int x = id * 100 + tipo->ancho;

	Posicion* pos = new Posicion (x,Posicion::obtenerPiso() - tipo->alto);

	Area* sup = new Area (	tipo->ancho, tipo->alto, pos );

	Manual* nuevoManual = new Manual(tipo->nombre, sup,tipo->velocidad, tipo->salto);
	manuales->agregarManual(nuevoManual, id);
	configNivel->actualizables.push_back(nuevoManual);
	nuevoManual->setearXInicial(x);

	nuevoManual->setearID(id);
	nuevoManual->agregarObservador(contCuerpos);

	if ( manuales->obtenerCantidad() == configNivel->players ){
		for (unsigned int i = 0; i < lasCajas->size() ; i++){
			configNivel->actualizables.push_back(lasCajas->at(i));
			lasCajas->at(i)->agregarObservador(lasVistaDeCajas->at(i));
			configNivel->vistas.push_back(lasVistaDeCajas->at(i));
		}

		contCuerpos->reinsertar();
//		for (unsigned int i = 0; i < camasElasticas->size() ; i++){
//			configNivel->actualizables.push_back(camasElasticas->at(i));
//			camasElasticas->at(i)->agregarObservador(vistasCamasElasticas->at(i));
//			configNivel->vistas.push_back(vistasCamasElasticas->at(i));
//		}
//		for (unsigned int i = 0; i < tuberias->size() ; i++){
//			configNivel->actualizables.push_back(tuberias->at(i));
//			tuberias->at(i)->agregarObservador(vistasTuberias->at(i));
//			configNivel->vistas.push_back(vistasTuberias->at(i));
//		}
	}

}

ContenedorManuales* GestorConfiguraciones::obtenerContenedorManuales(){
	return manuales;
}

ContenedorCuerpos* GestorConfiguraciones::obtenerContenedorCuerpos(){
	return contCuerpos;
}

std::string GestorConfiguraciones::rutaGanador(){
	if (quienGano != ObtenerPosiblesTiposProtagonistas()->size() )
		return ObtenerPosiblesTiposProtagonistas()->at(quienGano)->rutaGanador;
	else
		return "src/resources/cuerpos/GokuMono/poster.jpg";
}

std::vector<Superficie*>* GestorConfiguraciones::obtenerGanadores(){
	std::vector<Superficie*>* sups = new std::vector<Superficie*>();
	if (quienGano == ObtenerPosiblesTiposProtagonistas()->size() ){
		sups->push_back( new Superficie("src/resources/cuerpos/GokuMono/poster.jpg"));
		return sups;
	}
	if (quienGano < (ObtenerPosiblesTiposProtagonistas()->size()) ){
		sups->push_back( new Superficie(ObtenerPosiblesTiposProtagonistas()->at(quienGano)->rutaGanador));
		return sups;
	}

	for (unsigned int i = 0; i < this->ObtenerPosiblesTiposProtagonistas()->size(); i++){
		if (this->ObtenerPosiblesTiposProtagonistas()->at(i)->jugando)
			sups->push_back(new Superficie(this->ObtenerPosiblesTiposProtagonistas()->at(i)->rutaGanador));
	}
	return sups;
}
