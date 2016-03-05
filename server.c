#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "nodeopr.h"
#include "execstore.h"
#include "c2java.h"
//extern struct headpoint endpoint_head;

int main()
{
	int sfp, nfp, num = 0;
	struct sockaddr_in s_add,c_add;
	int sin_size;
	unsigned short portnum=0x8888;
	MYSQL my_connection,*conn_ptr;    
   	MYSQL_RES *res_ptr;  
   	MYSQL_ROW sqlrow;
	char buffer[100] = {0};
	printf("Hello,welcome to my server !\r\n");
    c2java_init();
    node_list_init(&endpoint_head);
	conn_ptr = mysql_init(&my_connection);
	if( !conn_ptr )  
   	{  
         printf("mysql_init failed ! \n");  
         return EXIT_FAILURE;  
   	}  	
	conn_ptr = mysql_real_connect(&my_connection,"localhost","root","1992",NULL,0,NULL,0);
	sfp = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfp)
	{
		printf("socket fail ! \r\n");
		return -1;
	}
	printf("socket ok !\r\n");
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr=htonl(INADDR_ANY);
	s_add.sin_port=htons(portnum);
	if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
			printf("bind fail !\r\n");
			return -1;
	}

	printf("bind ok !\r\n");
	if(-1 == listen(sfp,5))
	{
			printf("listen fail !\r\n");
			return -1;
	}

	printf("listen ok\r\n");
	sin_size = sizeof(struct sockaddr_in);
	while(1)
	{
	     nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
	     if(-1 == nfp)
	     {
		printf("accept fail !\r\n");
		return -1;
	     }
	    pid_t pid = fork();
	    switch(pid)
	    {
		case 0:
		    close(sfp);
		    exec_custom_store(nfp,conn_ptr,"temp",NULL);
		case -1:
		  break;
		default:
		 close(nfp);
         insert_end_point("zhang",&c_add,pid);
		 break;			
	    }
        printf("insert\n");
	}
	close(sfp);
	return 0;
}
