cc=gcc

IDIR= -I/home/mydata/work/adc_work/server/include -std=gnu99

OBJS= server.o execstore.o gettemp.o gettime.o nodeopr.o c2java.o
server:$(OBJS)
	$(cc) -o server $^   -L/usr/local/lib -lmysqlclient -lpthread -ljson-c

server.o:server.c 
	$(cc) -c -o server.o server.c 	$(IDIR) -I/usr/local/include/json-c

execstore.o:execstore.c
	$(cc) -c -o execstore.o execstore.c 	$(IDIR)

gettime.o:gettime.c
	cc -c -o gettime.o gettime.c $(IDIR)

gettemp.o:gettemp.c gettime.h
	cc -c -o gettemp.o gettemp.c $(IDIR)
nodeopr.o:nodeopr.c nodeopr.h
	cc -c -o nodeopr.o nodeopr.c $(IDIR) -I/usr/local/include/json-c
c2java.o:c2java.c c2java.h
	cc -c -o c2java.o c2java.c $(IDIR)  -I/usr/local/include/json-c -Wall
clean:
	rm *.o
