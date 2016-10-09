#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "cgic.h"
#include "ctemplate.h"


#define  DB_IP				"localhost"
#define  DB_USER			"root"
#define	 DB_PASSWORD		"123456"
#define	 DB_NAME			"yhy"
#define  RETURN_CONTENT_LEN 10240


int cgiMain()
{
	int ret = 0 ;
	cgiHeaderContentType("text/html;charset=utf-8");
	ReturnContent();
	return ret ;

}


int ExecuteNonQuery(MYSQL * mysql ,char * sql);
int ExecuteQuery(MYSQL * mysql ,char * sql,MYSQL_RES ** rs);

int ReturnContent(void)
{
	int				ret = 0 ;						//���ؽ��
	MYSQL			* mysql = NULL ;				//���ݿ�����ָ��
	MYSQL_RES		* pRs = NULL ;					//��ѯ�����ָ��
	MYSQL_ROW		row = NULL ;					//�����������
	char			idBuff[64] = {0};				//id
	char			sqlBuff[RETURN_CONTENT_LEN] = {0};			//sql���
	if(cgiFormString("id",idBuff,sizeof(idBuff)) != cgiFormSuccess) 
	{
		fprintf(cgiOut,"id is NULL");
		goto END ;
	}
	//��ʼ�����ݿ�
	mysql = mysql_init(0);
	if(mysql == NULL)
	{
		ret = -1 ;
		printf("Func mian() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}
	//�������ݿ�
	if(!mysql_real_connect(mysql,DB_IP,DB_USER,DB_PASSWORD,DB_NAME,0,0,0)) //����ʧ��
	{
		ret = -2 ;
		printf("Func mysql_real_connect() err:%d,(�޷��������ݿ�:%s)\n",ret,mysql_error(mysql));
		goto END ;
	}
	//���ñ��뷽ʽ
	ret = ExecuteNonQuery(mysql,"set names utf8");
	if(ret != 0)
	{
		printf("Func ExecuteNonQuery() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}
	
	//��ѯ���ݿ�����
	sprintf(sqlBuff,"SELECT ReturnContent FROM T_CommonInterface WHERE id = %s",idBuff);
	ret = ExecuteQuery(mysql,sqlBuff,&pRs);
	if(ret != 0)
	{
		printf("Func ExecuteQuery() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}

	//������ӡ����
	while(row = mysql_fetch_row(pRs))
	{
		char * pReturnContent = row[0];
		fprintf(cgiOut,"%s",pReturnContent);
	}
	
END:
	//�ͷŽ����
	if(pRs != NULL)
	{
		mysql_free_result(pRs);
	}
	if(mysql != NULL)
	{
		mysql_close(mysql);
	}
	return ret ;
}


int ExecuteNonQuery(MYSQL * mysql,char * sql)
{
	int ret = 0 ;
	if(mysql == NULL || sql == NULL)
	{
		ret = -1 ;
		printf("Func ExecuteNonQuery(),(mysql == NULL || sql == NULL),err:%d\n",ret);
		return ret ;
	}
	if(mysql_query(mysql,sql) != 0)
	{
		ret = -2 ;
		printf("Func ExecuteNonQuery(),(mysql_query(mysql,sql) != 0),err:%d,msg:%s\n",ret,mysql_error(mysql));
		return ret ;
	}
	return ret ;
}

int ExecuteQuery(MYSQL * mysql,char * sql,MYSQL_RES ** rs)
{
	MYSQL_RES * pRs = NULL;
	int ret = 0;
	//��ȫ���
	if(mysql == NULL || sql == NULL || rs == NULL)
	{
		ret = -1 ;
		printf("Func ExecuteQuery() err:%d,(mysql == NULL || sql == NULL || rs == NULL)\n",ret);
		return ret ;
	}
	if(mysql_query(mysql,sql) !=0 )
	{
		ret = -2 ;
		printf("Func ExecuteQuery() err:%d,msg:%s\n",ret,mysql_error(mysql));
		return ret ;
	}

	pRs = mysql_store_result(mysql);
	if(pRs == NULL)
	{
		ret = -2 ;
		printf("Func ExecuteQuery(),(pRs == NULL) ,err:%d,msg:%s\n",ret,mysql_error(mysql));
		return ret ;
	}

	*rs = pRs;
	return ret ;
}
