#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"

int cgiMain() 
{
	char name[256] = {0};
	char pwd[256] = {0};
	cgiHeaderContentType("text/html;charset=gbk");
	cgiFormString("name",name,256);
	cgiFormString("pwd",pwd,256) ;
	fprintf(cgiOut,"name=%s,age=%s",name,pwd) ;
}