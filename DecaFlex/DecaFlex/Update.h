/*
 * Update.h
 *
 * Created: 12/7/2012 6:29:26 PM
 *  Author: Anthony
 */ 


#ifndef UPDATE_H_
#define UPDATE_H_

#include <stdbool.h>
#include "Protocol.h"


void initUpdate();

bool updateReady();

void performUpdate(DECAFLEX_RAWUpdate_EP1_t* pState);

void updateOrientation();


#endif /* UPDATE_H_ */