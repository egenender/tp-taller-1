#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>

using namespace std;

class Log{
	public:
		static const string INFORMATIVO; // Tipo de severidad
		static const string ADVERTENCIA; // Tipo de severidad
		static const string ERROR;      // Tipo de severidad
		static const string RUTA;

		static Log* Instance();
		void writeToLogFile(string severity, string description);

	private:
		Log(){};  // Constructor privado para que no lo puedan llamar
		Log(Log const&){};  // Copia del const.
		Log& operator=(Log const&);  // Asignacion tambien privada.
		static Log* m_pInstance;
};


#endif /* LOG_H_ */
