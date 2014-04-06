/*
 * liblogin.c
 *
 *  Created on: 15. 2. 2014
 *      Author: jonny
 */

#include "liblogin.h"
/**
 *
 * @param filename
 * @return
 */
int __setUserFile(const char * filename){
	pUSERSFILE = fopen(filename,"a");
	if(!pUSERSFILE){
		error_message("Users file not found or error with openning");
		return -1;
	}
	fseek(pUSERSFILE,0L,SEEK_END);
	lUsersfileSize = ftell(pUSERSFILE);
	fseek(pUSERSFILE,0L,SEEK_SET);
	return 0;
}
/**
 * Loading userfile
 * @return 0 OK
 * -1 ERROR
 */
int __loadUserFile(){
	long read_size = 0;
	users = (struct TUSERPASSWD * ) malloc(sizeof(struct TUSERPASSWD) * iUsersSize);
	szUsersFileStream = malloc(lUsersfileSize);
	read_size = fread(szUsersFileStream,1,lUsersfileSize,pUSERSFILE);
	if(read_size < lUsersfileSize){
		error_message("Error reading users file.");
		return -1;
	}

	__parseUserFile();

	return 0;
}
/**
 * Resizing users if needed
 */
void __resizeUser(){
	struct TUSERPASSWD * ptrtmpusers = NULL;
	if(iUsersCurrentSize >= iUsersSize){
		iUsersSize *= 2;
		ptrtmpusers = malloc(sizeof(struct TUSERPASSWD) * iUsersSize);
		memcpy(ptrtmpusers,users,sizeof(struct TUSERPASSWD) * iUsersSize / 2);
		free(users);
		users = ptrtmpusers;
	}
}

/**
 *
 * @return 0 - OK
 * -1 ERROR
 */
int __parseUserFile(){

	char * ptrLast = szUsersFileStream;
	int i = 0;

	for(i=0; i < lUsersfileSize; i++){

		if(szUsersFileStream[i] == ':'){
			szUsersFileStream[i] = 0;
			users[iUsersCurrentSize].user = ptrLast;
		}
		if(szUsersFileStream[i] == '\n'){
			szUsersFileStream[i] = 0;
			users[iUsersCurrentSize].passwd = ptrLast;
			iUsersCurrentSize++;
		}
		ptrLast = &(szUsersFileStream[i]) + 1;
	}

	return 0;
}
/**
 * Generation salt for MD5 hashing
 *
 * @return salt
 */
char * __generateSalt(){
	char salt[6];
	char min = 0x30,max=0x7E,r=0;
	int i=0;

	srand(0x46a196b1);
	for( i=0 ; i < 6 ; i++){
		while(1){
			r= (char)(rand() % 0x7E);
			if(r >= 0x30 ){
				break;
			}
		}
		salt[i] = r;
	}
	return salt;
}


/**
 * Adding user - same structure as /etc/shadow
 * username:crypted(password)\n
 * @param username plain
 * @param password crypted
 */
int __addUser(const char * username, const char * password){
	char * salt=NULL,*pw_hash = NULL;

	salt = __generateSalt();

	pw_hash = crypt(password,salt);

	__resizeUser();

	users[iUsersCurrentSize].user = username;
	users[iUsersCurrentSize].passwd = pw_hash;

	iUsersCurrentSize++;

	__appendUserFile();

	return 0;
}
/**
 * Deleting users via username
 * @param username plain
 */
int __delUser(const char * username){
	int i = 0;
	for(i=0 ; i < iUsersCurrentSize; i++){
		if(strncmp(users[i].user,username,strlen(users[i].user))){
			break;
		}
	}
	--iUsersCurrentSize;
	if(i != iUsersCurrentSize){
		users[i].user = users[iUsersCurrentSize].user;
		users[i].passwd = users[iUsersCurrentSize].passwd;
	}

	return 0;
}

/**
 *
 * @param username
 * @return password string
 */
char *   __getUserPassword(const char * username){
	int i = 0;
	char * pstrpw = NULL;
	for(i=0 ; i < iUsersSize; i++ ){
		if(strncmp(users[i].user,username,strlen(users[i].user)) == 0){
			pstrpw = users[i].passwd;
			break;
		}
	}
	return pstrpw;
}

/**
 * uses password from file as a salt and then compare result hashes
 * @param username plain
 * @param password plain
 * @return 0 when will be sucessfull
 */
int __login(const char * username,const char * password){
	char *result = NULL ,* ppw_hash = __getUserPassword(username);
	result = crypt(password,ppw_hash);
	if(strcmp(result,ppw_hash) != 0){
		return 1;
	}
	return 0;
}

/**
 *
 */
void __writeUsersFile(){
	int i=0;
	fseek(pUSERSFILE,0,SEEK_SET);
	for(i=0 ; i < iUsersCurrentSize; i++){
		fprintf(pUSERSFILE,"%s:%s\n",users[i].user,users[i].passwd);
	}
}
/**
 *
 * @param pos
 */
void __appendUserFile(){
	fseek(pUSERSFILE,0,SEEK_END);
	fprintf(pUSERSFILE,"%s:%s\n",users[iUsersCurrentSize-1].user,users[iUsersCurrentSize-1].passwd);
}
/**
 * Sending request and waiting for response
 * @return
 */
int login(){
	printf("{ \"type\" : \"login\" , \"action\" : \"ws.login();\" }");

	/*
	 * Reading response
	 */



	return 0;
}


/**
 *
 * @param cookie
 * @param SESSIONID
 * @return
 */
int __isLogged(const char * cookie,int * SESSIONID){
	char * param, * value;
	while(!parseCOOKIE(&cookie,&param,&value)){
		if(strcmp(param,"SESSION")){
			*SESSIONID = atoi(value);
		}
	}
	if(*SESSIONID < 0){
		if(login()){
			return 1;
		}
	}
	return 0;
}

