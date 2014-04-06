/*
 * utils.c
 *
 *  Created on: 15. 2. 2014
 *      Author: jonny
 */


#include "utils.h"
/**
 * Error message
 * @param msg
 * @param err
 */
void error_message(const char * msg){
	fprintf(stderr,msg,errno);
}

/**
 * Initializing utils
 * session file
 * log file
 *
 * @return -1 error
 * 0 OK
 */
int __init_utils(){
	if(!LOG_FILE){

		LOG_FILE = fopen(LOG_PATH,"a+");
		SESSION_FILE= fopen(SESSION_PATH,"a+");

		if(!LOG_FILE){
			error_message("Log file cannot be created");
			return 1;
		}
		if(!SESSION_FILE){
			error_message("Session file cannot be created");
			return 1;
		}
	}
	if(!SESSIONS){
		SESSIONS = (char **)malloc(sizeof(*SESSIONS) * 2);
	}
	return 0;
}

/**
 * Closing utils
 * @return 0 - OK
 * 1 - FAIL
 */
int __close_utils(){
	if(fclose(SESSION_FILE) == EOF){
		error_message("Session file cannot be closed");
		return 1;
	}
	if(fclose(LOG_FILE) == EOF){
		error_message("Log file cannot be closed");
		return 1;
	}
	return 0;
}


/**
 * Logging
 * @param level
 * @param msg
 */
void log(int level,const char * msg){
	time_t now;
	char * str_log_level = NULL;
	time(&now);
	__init_utils();

	switch(level){
		case LOG_E:
			str_log_level = "ERROR";
			break;
		case LOG_I:
			str_log_level = "INFO";
			break;
		case LOG_W:
			str_log_level = "WARN";
			break;
	}

	fprintf(LOG_FILE,"[ %s ] [ %s ]  %s ",ctime(&now),str_log_level,msg);
}
/**
 *
 * @param buffer_in
 * @param param
 * @param value
 * @return
 */
int parseCOOKIE(char ** buffer_in,char ** param,char ** value){
		*param = strtok(*buffer_in,"=");
		if(!*param){
			return 1;
		}
		*value = strtok(NULL,";");
		if(!*value){
			return 1;
		}
	return 0;
}

/**
 *
 * @param buffer_in
 * @param param
 * @param value
 * @return
 */

int parseREQUEST(char ** buffer_in,char ** param,char ** value){
	char * token = NULL;
		token = strtok(*buffer_in,"&");
		if(!token){
			return -1;
		}
		*value = token;
		*param = strtok(*value,"=");

	return 0;
}
/**
 * Adding session to table.
 * @param str
 */
void session_add(const char * str){
	char ** tmp_table = NULL;
	if(SESSION_CURRENT_SIZE >= SESSION_SIZE){
		SESSION_SIZE *= 2;
		tmp_table = malloc(sizeof(*SESSIONS) * SESSION_SIZE);
		memcpy(tmp_table,SESSIONS,sizeof(*SESSIONS) * SESSION_CURRENT_SIZE);
		free(SESSIONS);
		SESSIONS = tmp_table;
	}
	SESSIONS[SESSION_CURRENT_SIZE] = str;
	SESSION_CURRENT_SIZE++;
	fwrite(str,sizeof(*str),strlen(str),SESSION_FILE);
}
/**
 * Checking if user is logged.
 * @param str COOKIE SESSID
 * @return 0 - OK
 * 1 - FAIL
 */
int session_check(const char * str){
	int idx = 0;
	for(idx=0; idx < SESSION_CURRENT_SIZE; idx++){
		if(strncmp(SESSIONS[idx],str,strlen(SESSIONS[idx])) == 0){
			return 0;
		}
	}
	return 1;
}
