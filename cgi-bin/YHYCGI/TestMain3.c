#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"

int cgiMain(int argc ,char * argv[]) 
{
	cgiHeaderContentType("text/html;charset=gbk");
	fprintf(cgiOut,"<html><body><h3>大家好</br>" \
		"Query_string是：%s </br>" 				\
		"你的浏览器的UserAgent是：%s </br>" 		\
		"你的IP地址是：%s</br>"					\
		"当前的CGI地址是:%s</h3></body></html>",cgiQueryString,cgiUserAgent,cgiRemoteAddr,cgiScriptName);
	return 0 ;
}