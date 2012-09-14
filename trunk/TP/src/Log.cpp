#include "Log.h"

// Puntero estatico para controlar la instanciacion.
Log* Log::m_pInstance = NULL;
const string Log::INFORMATIVO="INFO"; // Tipo de severidad
const string Log::ADVERTENCIA="WARN"; // Tipo de severidad
const string Log::ERROR="ERROR";      // Tipo de severidad
const string Log::RUTA="logDK.txt";

Log* Log::Instance() {
   if (!m_pInstance)
      m_pInstance = new Log;
   return m_pInstance;
}

void writeToLogFile(string severity, string description) {
	// TODO Usar un prefijo Date y setear un registro en el archivo.
}

