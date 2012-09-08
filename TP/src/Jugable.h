/*
 * Jugable.h
 *
 *  Created on: 08/09/2012
 *      Author: martin
 */

#ifndef JUGABLE_H_
#define JUGABLE_H_

class Jugable {
public:
	virtual void jugar()=0;
	Jugable();
	virtual ~Jugable();
};

#endif /* JUGABLE_H_ */
