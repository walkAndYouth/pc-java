#include "getopt.h"
#include <string.h>


int getCommod(char *buf,char *argv[])
{
    int i = 0;
    char *str;
    str = strtok(buf,":");
    while(str)
    {
      argv[i] = str;
      str = strtok(NULL,":");
      i++;
    }
    return i;
}
