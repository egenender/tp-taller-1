#include "Log.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "string.h"

// Puntero estatico para controlar la instanciacion.
Log Log::instance;

const string Log::INFORMATIVO="INFO"; // Tipo de severidad
const string Log::ADVERTENCIA="WARN"; // Tipo de severidad
const string Log::ERROR="ERROR";      // Tipo de severidad
const char* Log::RUTA="logDK.txt";

Log::Log() {}

Log* Log::getInstance() {
   return &instance;
}


/**
 * Parametros:
 * 	Descripcion: Debe tener maximo 247 caracteres.
 * 	Severity: Usar las constantes definidas en la clase para seleccionar su tipo.
 */
void Log::writeToLogFile(string severity, string description) {
	ofstream handlerWriteFile;
	time_t rawtime;
	time ( &rawtime );
	string tiempo = ctime (&rawtime);
	string registro = severity + " - " + description + " - " + tiempo;

	handlerWriteFile.open(Log::RUTA, handlerWriteFile.app);

	if (handlerWriteFile.good()) {
		// Si esta ok al crear o abrir el archivo de log
		// escupe por consola y al log.
		handlerWriteFile << registro;
		cout << registro << endl;
	} else {
		cout << "Error al crear/abrir el archivo de sistema LogDK.txt" << endl;
	}
}

