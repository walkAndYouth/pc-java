#ifndef C2JAVA_H
#define C2JAVA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "nodeopr.h"
#include "bits.h"
void c2java_init(void);

void c_to_java(int size,char *data);

void c_from_java(int size,char *data);

#endif
