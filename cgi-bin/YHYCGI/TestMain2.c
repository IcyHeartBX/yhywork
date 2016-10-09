#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
 
int cgiMain(int argc ,char * argv[]) 
{
cgiHeaderContentType("text/html;charset=gbk");
fprintf(cgiOut,"<html><body><h3>´ó¼ÒºÃ</h3></body></html>");
return 0 ;
}