#define makefile
	
CC=gcc
all:main.o cgic.o ctemplate.o
	@echo "=========================     Start Compile      =============================="
	$(CC) -o InterfaceCfg.cgi $^ -I/usr/install/mysql/include/mysql -L/usr/install/mysql/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm
	@echo "=========================     End Compile        =============================="
clean:
	rm *.o
main.o:InterfaceCfg.c
	$(CC) -c -o $@ $^ -I/usr/install/mysql/include/mysql -L/usr/install/mysql/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm
cgic.o:cgic.c
	$(CC) -c -o $@ $^ 
ctemplate.o:ctemplate.c
	$(CC) -c -o $@ $^