/*
 * libserial.h
 *
 *  Created on: 15. 2. 2014
 *      Author: jonny
 */

#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

#ifndef LIBSERIAL_H_
#define LIBSERIAL_H_


#define SERIAL_STATUS_READING 1
#define SERIAL_STATUS_WRITING 2
#define SERIAL_STATUS_ERROR -1
#define SERIAL_STATUS_READY 0

static char SERIAL_BUFFER_RECEIVED = FALSE;
static char SERIAL_BUFFER_READY_TO_WRITE = FALSE;
static char SERIAL_BUFFER_READY_TO_RECEIVE = FALSE;

static int SERIAL = 0;

const static int SERIAL_BUFFER_SIZE = 9600;
static int SERIAL_CURRENT_BUFFER_SIZE = 0;
static char * SERIAL_BUFFER;
static int SERIAL_BUFFER_READ = 0;
static int SERIAL_STATUS = SERIAL_STATUS_ERROR;
static int LIB_SERIAL_STATUS = 0;


#endif /* LIBSERIAL_H_ */
