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
#include "../view/TipoProtagonista.h"
#include "../view/ConfiguracionPantalla.h"
#include "../view/ConfiguracionNivel.h"
#include "../model/ContenedorDummy.h"
#include "../model/Dummy.h"
#include "../model/Personajes/VigaInclinada.h"
#include "../model/ContenedorManuales.h"
#include "../model/Personajes/Manual.h"
#include "../log/Log.h"
#include "../gui/model/Ventana.h"
#include <map>

#include "yaml-cpp/yaml.h"

#include "SDL/SDL_mixer.h"
#include "../view/VistaSonora.h"

#define ESCALERA 0
#define PLATAFORMA 1

typedef std::map <std::string,std::string> mapa_tex;
typedef std::map <std::string,TipoProtagonista*> mapa_prot;
typedef std::map <std::string,TipoPersonaje*> mapa_auto;

typedef std::map <std::string,string> mapa_niveles;

typedef struct _parametrosTuberia{

	int ancho;
	int alto;
	std::vector<int>* probabilidades;
	std::map<int, Superficie*>* superficies;
	std::vector<std::vector<int>* >* matrizEstados;

}parametrosTuberia;

typedef struct _parametrosCajas{

	int ancho;
	int alto;
	std::vector<int>* probabilidades;
	Animacion* quieto;
	Animacion* lanzando;

}parametrosCaja;

typedef struct _parametrosPersonaje{

	int ancho;
	int alto;
	int velocidad;
	std::vector<Animacion*>* animaciones;
	std::vector<std::vector<int>* >* matrizEstados;

}parametrosPersonaje;

typedef std::map <std::string,parametrosPersonaje*> mapa_parametrosPersonaje;
typedef std::map <std::string,parametrosTuberia*> mapa_parametrosTuberia;
typedef std::map <std::string,parametrosCaja*> mapa_parametrosCaja;

class GestorConfiguraciones{
	private:
		static GestorConfiguraciones* instancia;
		GestorConfiguraciones();
		int margen_scroll;
		ConfiguracionPantalla* configPantalla;
		mapa_prot* tiposProtagonista;
		mapa_auto* tiposAutomatico;
		mapa_tex* texturas;
		ConfiguracionNivel* configNivel;
		std::vector<string>* vectorRutas;

		std::vector<string>* posiblesNiveles;

		std::vector<TipoProtagonista*>* posiblesTiposProt;
		std::vector<string>* nombresProt;

		bool esCliente;

		int nivelElegido;
		ContenedorDummy* contenedor;
		Dummy* dummy;
		ContenedorManuales* manuales;

		string headerTemp;
		string rutaYaml;
		string rutaYamlDefecto;
		mapa_parametrosPersonaje* mapaParam;
		mapa_parametrosTuberia* mapaTub;
		mapa_parametrosCaja* mapaCajas;

		bool destruir;
	public:
		static GestorConfiguraciones* getInstance();
		void acabarGestor();
		void destruirGestor();
		parametrosPersonaje* crearParametrosPersonaje(const YAML::Node&, string);
		void CargarPersonajes(const YAML::Node&);

		parametrosTuberia* crearParametrosTuberia(const YAML::Node&, string);
		void CargarTuberias(const YAML::Node&);

		parametrosCaja* crearParametrosCaja(const YAML::Node&, string);
		void CargarCajas(const YAML::Node&);

		//GestorConfiguraciones();
		ConfiguracionPantalla* CargarConfiguracionPantalla(const YAML::Node&);
		ConfiguracionPantalla* CargarConfiguracionPantalla(int, int);
		void CargarTiposProtagonista(const YAML::Node&, const YAML::Node&);
		void CargarTiposAutomaticos(const YAML::Node&);
		TipoProtagonista* _CargarTipoProtagonista(const YAML::Node&, const char*);
		TipoPersonaje* _CargarTipoAutomatico(const YAML::Node&, const char*);
		void CargarTexturas(const YAML::Node& nodo);
		Ventana* CrearPantalla();
		void CargarConfiguracionNivel(const YAML::Node&,const YAML::Node&,const YAML::Node&,const YAML::Node&);
		void CargarPersonajesNivel(const YAML::Node&);
		void CargarEstaticosNivel(const YAML::Node&, bool, bool, int);

		void CargarElementosNivel(const YAML::Node& , int);
		void CargarTuberiasNivel(const YAML::Node& );
		void CargarCajasNivel(const YAML::Node& );

		Automatico* CrearAutomaticoDefecto(const char* ,int, int);
		VistaAutomatico* CrearVistaAutomaticaDefecto(Automatico*);

		void crearVistaElemento(Observable*,string, bool esCuerpo = true);
		void crearVistaTuberia(Cuerpo*,string, int);
		void crearVistaCaja(Cuerpo*,string );

		parametrosPersonaje* obtenerParametrosPersonaje(string);
		//void CargarPantalla();
		bool Entra(int , int , int , int );
		int ObtenerAnchoNivel();
		int ObtenerAltoNivel();
		int ObtenerPisoNivel();
		Mix_Music* ObtenerMusica();
		int ObtenerAltoPantalla();
		int ObtenerAnchoPantalla();
		int ObtenerMargenScroll();
		Superficie* ObtenerFondo();
		void AgregarAVector(string ruta);
		void setEsCliente ();

		unsigned int obtenerCantidadDeJugadores();

		void setNivelElegido(int);
		int ObtenerNivelElegido();
		void inicioCarga();
		void CargaRestante();

		void setPosiblesNiveles();
		std::vector<string>* ObtenerPosiblesNiveles();
		void setPosiblesTiposProtagonistas();
		std::vector<TipoProtagonista*>* ObtenerPosiblesTiposProtagonistas();
		std::vector<string>* obtenerNombresProtagonistas();

		std::vector<string>* devolverVectorRutas();

		Manual* ObtenerManual();
		VistaProtagonista* ObtenerVistaManual();

		void setProtagonista(string nombre);
		Dummy* obtenerDummyMio();
		void crearManual(unsigned int);
		ContenedorManuales* obtenerContenedorManuales();

		vector<Actualizable*>* ObtenerActualizables();
		vector<VistaCuerpo*>* ObtenerVistas();

		Cuerpo* instanciarCuerpo(std::string, int, int );
		Cuerpo* instanciarTuberia(std::string, int, int, float, int );
		Cuerpo* instanciarCaja(std::string, int, int );

	private:
		void destruirParametrosPersonaje(parametrosPersonaje*);
};

