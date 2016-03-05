#include "c2java.h"
#include "json.h"
static int c2java_socket;


static void * recv_start(void*arg)
{
    struct sockaddr_in addr;
    char buffer[100];
    char *buf  = (char*)malloc(1000);
    if(!buf)
    {
        printf("malloc fialed!\n");
        return;
    }
    socklen_t addrlen;
    struct json_object * jsonobj;
    
    while(1)
    {
        struct json_object *json_opr;
        recvfrom(c2java_socket,&buffer,1000,0,(struct sockaddr*)(&addr),&addrlen);
        jsonobj = json_tokener_parse((const char*)&buffer);
        json_object_object_get_ex(jsonobj,"opr",&json_opr);
        char *opr = json_object_get_string(json_opr);
        if(is_error(jsonobj))
        {
            printf("json failed!\n");
        }
        if(!strcmp(opr,"start"))
        {
		printf("json_string:%s\n",opr);
            display_endpoint(buf);
            sendto(c2java_socket,buf,strlen(buf),0,(struct sockaddr*)(&addr),sizeof(struct sockaddr));
        }
        else if(!strcmp(opr,"put"))
        {
            
        }
        

        json_object_put(jsonobj);

        display_endpoint(buf);
        printf("name:%s\n",buf);
        *buf = '\0';
    }
}


void c2java_init(void)
{
    struct sockaddr_in addr;
    pthread_t tread;
    memset(&addr,0,sizeof(struct sockaddr_in));
    c2java_socket = socket(AF_INET,SOCK_DGRAM,0);
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(0x9999);
    addr.sin_addr.s_addr   = htonl(INADDR_ANY);

    int res = bind(c2java_socket,(struct sockaddr*)(&addr),sizeof(struct sockaddr));
    if(res)
    {
        printf("datagram bind failed!\n");
        return;
    }
       
    int s = pthread_create(&tread,NULL,recv_start,NULL);
    if(s)
    {
        printf("pthread create failed!\n");
        return;
    }
}
