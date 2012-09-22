/*
 * GestorConfiguraciones.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "Animacion.h"
#include "HojaSprites.h"
#include "VistaProtagonista.h"
#include "VistaAnimada.h"
#include "VistaImagen.h"
#include "VistaAutomatico.h"
#include "TipoPersonaje.h"
#include "ConfiguracionPantalla.h"
#include "ConfiguracionNivel.h"
#include "Log.h"
#include <map>

#include "yaml-cpp/yaml.h"


typedef std::map <std::string,Superficie*> mapa_tex;
typedef std::map <std::string,TipoPersonaje*> mapa_per;

class GestorConfiguraciones{
	private:
		static GestorConfiguraciones instancia;
		GestorConfiguraciones();
		int vel_personaje;
		int margen_scroll;
		ConfiguracionPantalla* configPantalla;
		mapa_per* tiposPersonajes;
		mapa_tex* texturas;
		ConfiguracionNivel* configNivel;

	public:
		static GestorConfiguraciones* getInstance();

		//GestorConfiguraciones();
		ConfiguracionPantalla* CargarConfiguracionPantalla(const YAML::Node&);
		ConfiguracionPantalla* CargarConfiguracionPantalla(int, int, string);
		void CargarTiposPersonajes(const YAML::Node&, const YAML::Node&);
		TipoPersonaje* _CargarTipoPersonaje(const YAML::Node&, const char*);
		void CargarTexturas(const YAML::Node& nodo);
		SDL_Surface* CrearPantalla();
		ConfiguracionNivel* CargarConfiguracionNivel(const YAML::Node&);
		int ObtenerAltoNivel();
		int ObtenerAnchoNivel();

		Manual* ObtenerManual();
		VistaProtagonista* ObtenerVistaManual();

		vector<Cuerpo*>* ObtenerCuerpos();
		vector<VistaCuerpo*>* ObtenerVistas();

};


