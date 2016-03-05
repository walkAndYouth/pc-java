#include "nodeopr.h"
#include "json.h"
void node_list_init(struct headpoint *head)
{
    head->total = 0;
    head->head = NULL;
}

void insert_end_point(char *name,struct sockaddr_in *addr,pid_t pid)
{
    int i;
    ENDPOINT p = endpoint_head.head,s;
    s = (ENDPOINT)malloc(sizeof(endpoint));
    memcpy(&s->addr,addr,sizeof(struct sockaddr_in));
    strcpy(s->name,name);
    if(!p)
    {
        s->num = 1;
        endpoint_head.head = s;
    }
    else
    {
        for(i = 1; i < endpoint_head.total;i++)
        p = p->next;
        s->num = i+1;
        p->next = s;
    }
    endpoint_head.total++;
    s->next = NULL;
    s->pid = pid;
}

void  display_endpoint(char *buf)
{
    ENDPOINT s = endpoint_head.head;

    struct json_object * json_point = json_object_new_object();
    json_object_object_add(json_point,"opr",json_object_new_string("word"));
    
    struct json_object * json_array = json_object_new_array();

    while(s)
    {
        struct json_object *json_temp = json_object_new_object();
        json_object_object_add(json_temp,"name",json_object_new_string(s->name));
        json_object_array_add(json_array,json_temp);
        json_object_put(json_temp);
        s = s->next;
    }
    json_object_object_add(json_point,"set",json_array);
    buf = json_object_to_json_string(json_point);
    printf("display:%s\n",buf);
    json_object_put(json_point);
}
