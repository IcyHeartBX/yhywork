#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"

int cgiMain(int argc ,char * argv[]) 
{
	cgiHeaderContentType("text/html;charset=gbk");
	fprintf(cgiOut,"<html><body><h3>��Һ�</br>" \
		"Query_string�ǣ�%s </br>" 				\
		"����������UserAgent�ǣ�%s </br>" 		\
		"���IP��ַ�ǣ�%s</br>"					\
		"��ǰ��CGI��ַ��:%s</h3></body></html>",cgiQueryString,cgiUserAgent,cgiRemoteAddr,cgiScriptName);
	return 0 ;
}