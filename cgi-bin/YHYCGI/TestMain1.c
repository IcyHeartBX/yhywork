#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char * argv[] ) 
{
	//��ȡ�������
	char * qs = getenv("QUERY_STRING");
	char username[256]={0};
	//��username=tpx&pwd=123,ȡ��username,ʹ��sscanf����
	 sscanf(qs,"username=%s",username);
	//��ӡContent-Type
	printf("Content-Type:text/html;charset=gbk\r\n\r\n");
	printf("<html><body><font color='blue' size='10'>");
	if(strcmp(username,"root") == 0) {
		printf("root�û���¼�ɹ�");
	}
	else 
	{
		printf("����root�û�����¼ʧ�ܣ�");
	}
	printf("</font></body></html>");
	return 0 ;
}