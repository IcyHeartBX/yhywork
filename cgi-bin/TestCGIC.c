#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"

int cgiMain()
{
	cgiHeaderContentType("text/html;charset=utf-8\n\n");
	fprintf(cgiOut,"<html><head></head><body>哈哈哈哈</body></html>");
	return 0 ;
}
