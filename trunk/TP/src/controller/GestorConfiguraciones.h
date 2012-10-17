/*
 * GestorConfiguraciones.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "../view/Animacion.h"
#include "../view/HojaSprites.h"
#include "../view/VistaProtagonista.h"
#include "../view/VistaAnimada.h"
#include "../view/VistaImagen.h"
#include "../view/VistaAutomatico.h"
#include "../view/TipoPersonaje.h"
#include "../view/ConfiguracionPantalla.h"
#include "../view/ConfiguracionNivel.h"
#include "../log/Log.h"
#include "../gui/model/Ventana.h"
#include <map>

#include "yaml-cpp/yaml.h"


typedef std::map <std::string,std::string> mapa_tex;
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
		std::vector<string>* vectorRutas;

	public:
		static GestorConfiguraciones* getInstance();

		//GestorConfiguraciones();
		ConfiguracionPantalla* CargarConfiguracionPantalla(const YAML::Node&);
		ConfiguracionPantalla* CargarConfiguracionPantalla(int, int, string);
		void CargarTiposPersonajes(const YAML::Node&, const YAML::Node&);
		TipoPersonaje* _CargarTipoPersonaje(const YAML::Node&, const char*);
		void CargarTexturas(const YAML::Node& nodo);
		Ventana* CrearPantalla();
		void CargarConfiguracionNivel(const YAML::Node&,const YAML::Node&,const YAML::Node&,const YAML::Node&);
		void CargarPersonajesNivel(const YAML::Node&);
		void CargarEstaticosNivel(const YAML::Node&, bool, bool);
		Automatico* CrearAutomaticoDefecto(const char* ,int, int);
		VistaAutomatico* CrearVistaAutomaticaDefecto(Automatico*);
		bool Entra(int , int , int , int );
		int ObtenerAltoNivel();
		int ObtenerAnchoNivel();
		int ObtenerAltoPantalla();
		int ObtenerAnchoPantalla();
		int ObtenerMargenScroll();
		Superficie* ObtenerFondo();
		void AgregarAVector(string ruta);

		std::vector<string>* devolverVectorRutas();

		Manual* ObtenerManual();
		VistaProtagonista* ObtenerVistaManual();

		vector<Actualizable*>* ObtenerActualizables();
		vector<VistaCuerpo*>* ObtenerVistas();

};


