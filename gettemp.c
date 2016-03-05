#include "gettemp.h"
#include <stdio.h>
#include <sys/socket.h>
#include "gettime.h"
#include <string.h>

void do_storetemp(int cfd,MYSQL *con,char **arg)
{
    MYSQL_RES * res;
    MYSQL_ROW row;
	printf("do_storetemp is execed!\n");
	unsigned char databuf[200] = {0};
    unsigned char sql[50] = "insert into ";
	int count = 0;	
    char timebuf[10];
    unsigned short value = 0;
    mysql_select_db(con,"temp");
	while(1)
	{
        cgetdate(timebuf);
        res = mysql_list_tables(con,timebuf);
        row = mysql_fetch_row(res);
        if(!row)
        {
            char csql[50] = "create table ";
            strcat(csql,timebuf);
            strcat(csql,"(time time,value int)");
            mysql_query(con,csql);      
        }
        recv(cfd,databuf,7,0);
		count = databuf[6];
		count <<= 8;
		count |= databuf[5];
		printf("count:%d\n",count);
        recv(cfd,databuf,200,0);	
        printf("recv!\n");
        for(int ii = 0; ii < count*2; ii+=2)
        {
            value = databuf[ii+1];
            value <<= 8;
            value |= databuf[ii];
            value %= 100;

            printf("pos:%d\n",ii);
            printf("value:%d\n",value);
            strcat(sql,timebuf);
            strcat(sql," values(now(),  ");
            sql[32] = value %10+0x30;
            sql[31] = value /10+0x30;
            sql[33] = ')';
            sql[34] = '\0';
            printf("sql:%s\n",sql);
            mysql_query(con,sql);           
        }
        
        printf("\n\n\n");
	}

}

