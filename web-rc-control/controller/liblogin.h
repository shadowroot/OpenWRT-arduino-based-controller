/*
 * liblogin.h

 *
 *  Created on: 15. 2. 2014
 *      Author: jonny
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <crypt.h>
#include "utils.h"


#ifndef LIBLOGIN_H_
#define LIBLOGIN_H_

struct TUSERPASSWD{
	char * user;
	char * passwd;
};

static FILE * pUSERSFILE = NULL;
static long int lUsersfileSize = 0;
static char * szUsersFileStream = NULL;
static int iUsersSize = 2;
static int iUsersCurrentSize=0;
static struct TUSERPASSWD * users;

#endif /* LIBLOGIN_H_ */
