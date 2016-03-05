#ifndef _EXECSTORE_H
#define _EXECSTORE_H
#include <mysql/mysql.h>

struct exec_store
{
	char *name;
	void (*func)(int cfd,MYSQL *sql,char**arg);
};

void exec_custom_store(int cfd,MYSQL*sql,char *name,char **arg);
#endif
