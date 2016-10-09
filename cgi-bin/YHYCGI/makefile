#def makefile
CC=gcc
all:main.o cgic.o
	$(CC) -o TestMain.cgi $^
clean:
	rm *.cgi *.o
main.o:TestMain.c
	$(CC) -c -o $@ $^
cgic.o:cgic.c
	$(CC) -c -o $@ $^