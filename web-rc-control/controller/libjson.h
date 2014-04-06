/*
 * libjson.h
 *
 *  Created on: 7. 2. 2014
 *      Author: jonny
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifndef LIBJSON_H_
#define LIBJSON_H_

#define TYPE_OBJECT 0
#define TYPE_STRING 1
#define TYPE_INT 2
#define TYPE_BOOL 3
#define TYPE_ARRAY 4


/**
 * Values union it means it's acting as one type
 */
union TVALUE{
	STRING * string;
	int integer;
	struct TObject * object;
	union TVALUE * array;
	char bool;
};

/**
 * Tokens of params and values with one direction linked list
 */
struct TToken{
	char * param;
	char type;
	union TVALUE value;
	struct TToken * next;
	char type_array;
	int array_size;
};

/**
 * Describing JSON Object with tokenizer. Each token describes parama and value pair.
 */


struct TObject{
	struct TToken* tokens;
};

#endif /* LIBJSON_H_ */
