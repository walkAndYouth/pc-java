#include "execstore.h"
#include "gettemp.h"
#include "include/config.h"
#include <string.h>
#include <stdio.h>
#define STORE_NUM 1
struct exec_store store_task[1]=
{
	{
		.name="temp",
		.func = do_storetemp,
	},

};

void exec_custom_store(int cfd,MYSQL * sql,char *name,char **arg)
{
	for(int i = 0; i < STORE_NUM;i++)
	{
		if(!strcmp(name,store_task[i].name))
		{
			store_task[i].func(cfd,sql,arg);
			printf("execstore fucn is execd!\n");
		}
	}
}
