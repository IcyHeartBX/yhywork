#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"

int cgiMain()
{
	char name[256] = {0};
	char pwd[256] = {0} ;
	int isSuccess = 0;
	//ȡ�����������name��pwd
	cgiFormString("name",name,256);
	cgiFormString("pwd",pwd,256) ;
	if(strcmp(name,"root")== 0 && strcmp(pwd,"123456")==0) 
	{
		isSuccess = 1 ;
	}

	if(isSuccess) 
	{
		cgiHeaderLocation("../../success.html");
	}
	else {
		cgiHeaderContentType("text/html;charset=gbk");
		fprintf(cgiOut,"<html><body>");
		fprintf(cgiOut,"��¼ʧ�ܣ�����������!");
		fprintf(cgiOut,"</body></html>");
	}
	return 0 ;
}