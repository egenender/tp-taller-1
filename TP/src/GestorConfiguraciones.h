/*
 * GestorConfiguraciones.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include <map>
#include "yaml-cpp/yaml.h"
#include "Superficie.h"
#include "TipoPersonaje.h"
#include "ConfiguracionPantalla.h"

typedef std::map <std::string,TipoPersonaje*> mapa_per;
typedef std::map <std::string,Superficie*> mapa_tex;

class GestorConfiguraciones{


	private:
		int vel_personaje;
		int margen_scroll;
		ConfiguracionPantalla* configPantalla;
		mapa_per* tiposPersonajes;
		mapa_tex* texturas;

	public:
		GestorConfiguraciones();
		ConfiguracionPantalla* CargarConfiguracionPantalla(const YAML::Node&);
		void CargarTiposPersonajes(const YAML::Node&);
		TipoPersonaje* _CargarTipoPersonaje(const YAML::Node&);
		void CargarTexturas(const YAML::Node& nodo);
		SDL_Surface* CrearPantalla();

};


