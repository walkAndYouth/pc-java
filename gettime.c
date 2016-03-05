#include <time.h>
#include "gettime.h"
#include <stdio.h>

const char * time_style= "%y_%m";

void cgetdate(char buf[])
{
   time_t curtime;
   struct tm *tm;
   curtime = time(NULL);
   tm = gmtime(&curtime);
   strftime(buf,10,time_style,tm);
}

void cgettime(char buf[])
{
    time_t curtime;
    struct tm *tm;
    curtime = time(NULL);
    tm = localtime(&curtime);
    strftime(buf,10,"%H:%M:%S",tm);
}
