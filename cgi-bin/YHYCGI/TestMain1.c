#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char * argv[] ) 
{
	//获取请求参数
	char * qs = getenv("QUERY_STRING");
	char username[256]={0};
	//从username=tpx&pwd=123,取出username,使用sscanf函数
	 sscanf(qs,"username=%s",username);
	//打印Content-Type
	printf("Content-Type:text/html;charset=gbk\r\n\r\n");
	printf("<html><body><font color='blue' size='10'>");
	if(strcmp(username,"root") == 0) {
		printf("root用户登录成功");
	}
	else 
	{
		printf("不是root用户，登录失败！");
	}
	printf("</font></body></html>");
	return 0 ;
}