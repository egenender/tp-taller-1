#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>

using namespace std;

class Log{
	private:
		static Log instance;
		Log();

	public:
		static const string INFORMATIVO; // Tipo de severidad
		static const string ADVERTENCIA; // Tipo de severidad
		static const string ERROR;      // Tipo de severidad
		static const char* RUTA;

		static Log* getInstance();
		void writeToLogFile(string severity, string description);
};


#endif /* LOG_H_ */
