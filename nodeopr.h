#ifndef NODEOPR_H
#define NODEOPR_H
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct endpoint
{
    char name[20];
    int  num;
    pid_t pid;
    struct sockaddr_in addr;  
    struct endpoint *next;

}*ENDPOINT,endpoint;

struct headpoint
{
    int total;
    ENDPOINT  head;
};

//建立空链表
static struct headpoint endpoint_head;
//初始化链表

void node_list_init(struct headpoint *head);

//插入节点

void insert_end_point(char *name,struct sockaddr_in *addr,pid_t pid);

//查找节点
ENDPOINT get_node_by_name(char *name);
ENDPOINT get_node_by_num(int num);

//删除节点
void del_node_by_name(char *name);
void del_node_by_num(char *num);
//
void display_endpoint();
//
//
//
//
//
//
#endif
