/*
 * ManejadorCheckbox.h
 *
 *  Created on: 08/11/2012
 *      Author: nicolas
 */

#ifndef MANEJADORCHECKBOX_H_
#define MANEJADORCHECKBOX_H_

#include "ManejadorBoton.h"

class ManejadorCheckbox : public ManejadorBoton{
private:
	bool estadoCambio;
public:
	ManejadorCheckbox(int);
	virtual ~ManejadorCheckbox();
	void manejarClic();
};


#endif /* MANEJADORCHECKBOX_H_ */
