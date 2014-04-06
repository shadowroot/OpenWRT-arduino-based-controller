/*
 * webcontrol.c
 *
 *
 *Web Controller

- RC Car controller and others
-

 *  Created on: 4. 2. 2014
 *      Author: jonny
 */

#include "webcontrol.h"

// TODO login parse




//
//int parseGET(char * buffer_in){
//	char * value, * param;
//	while(!parseREQUEST(&buffer_in,&param,&value)){
//
//	}
//	return 0;
//}
//
//int parsePOST(char * buffer_in){
//	char * value, * param;
//	while(!parseREQUEST(&buffer_in,&param,&value)){
//
//	}
//	return 0;
//}
/**
 *
 * @return
 */

void sendHeader(char * cookie){
	fputs("HTTP/1.0 200 OK\r\n",stdout);
	fputs("Content-type: text/plain\r\n",stdout);
	fputs("Set-Cookie:",stdout);
	fputs(cookie,stdout);
	fputs("\r\n\r\n",stdout);
}


int writeStream(char * buffer_out){
	fputs(buffer_out,stdin);
	return 0;
}




/**
 * Entry point to application
 *
 * @return
 */

int main(int argc,char * argv[]){


	/*
	 * initializing variables
	 */
	char add = FALSE,del=FALSE;
	char * action = NULL;
	char * data_in = NULL;
	char * cookie = NULL;
	int data_lenght_in = 0;
	char * w_content_data_length = NULL;
	char * buffer_in = NULL;
	char * buffer_out = NULL;
	char * token = NULL, *user=NULL, *passwd=NULL;
	int SESSIONID = -1,c=0;
	const char * help = "webcontrol [-ad] [-u username] [-p password]\r\n "
			"Usage:\r\n"
			"-a Adding user\r\n"
			"-d Deleting user\r\n"
			"-h Showing help\r\n";

	struct TRequest * GETrequests = NULL;
	struct TRequest * POSTrequests = NULL;



	if(argc > 1){
		while((c = getopt(argc,argv,"aduph")) != -1){
			switch(c){
			case 'a':
				add = TRUE;
				break;
			case 'd':
				del = TRUE;
				break;
			case 'u':
				user = optarg;
				break;
			case 'p':
				passwd = optarg;
				break;
			case 'h':
				fputs(help,stdout);
				return 0;
			}
		}
		if(add && del){
			return 1;
		}
		else if(add){
			if(__addUser(user,passwd)){
				error_message("User add unsucessfull");
				return 1;
			}
		}
		else if(del){
			if(__delUser(user)){
				error_message("User delete unsucessfull");
				return 1;
			}
		}
		return 0;
	}


//parse /etc/passwd data for accounts and shadow for passwords
//	buffer_out = (char*) malloc(PACKET_SIZE);


	//	get method string
	action = getenv("QUERY_STRING");
/*
 * There come sonly context of commands inside requests
 * Example:
 * ?login
 * ?command
 * ?action
 *
 */
	/*
	 *SESSID WILL be around here.
	 */
	cookie = getenv("HTTP_COOKIE");
	w_content_data_length = getenv("CONTENT_LENGTH");

	/*
	 * Parsing cookie phase
	 */
	if(__isLogged(cookie,&SESSIONID)){
		login();
	}

	/*
	 * Checking if session is good
	 */


	data_lenght_in = atoi(w_content_data_length);
	/*
	 * Getting data via POST data from stdin to buffer_in
	 */

	buffer_in = (char*) malloc(data_lenght_in);
	fread(buffer_in,1,data_lenght_in,stdin);
	/*
	 * process data
	 */

	sendHeader(cookie);

	free(buffer_in);
	free(buffer_out);
	return 0;
}


