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
#define  ID_BUFF_LEN        16


int cgiMain(void)
{
	int				ret = 0 ;
	
	cgiHeaderContentType("text/html;charset=utf-8");
	fprintf(cgiOut,"<html><head></head><body>");
	if(cgiFormSubmitClicked("modifyBtn") == cgiFormSuccess)
	{
		//TMPL_write("ModifyInterface.htm",0,0,0,cgiOut,cgiOut);
	}
	else if(cgiFormSubmitClicked("btnAdd")!= cgiFormSuccess)
	{
		TMPL_write("CommonInterface.htm",0,0,0,cgiOut,cgiOut);
		return ret ;
	}
	PrintUserInfo();
	fprintf(cgiOut,"</body></html>");
	return ret ;
	
}

int PrintUserInfo(){
	int				ret = 0 ;						//返回结果
	MYSQL			* mysql = NULL ;				//数据库连接指针
	MYSQL_RES		* pRs = NULL ;					//查询结果集指针
	MYSQL_ROW		row = NULL ;					//结果集行数据
	char			sqlBuff[2048] = {0} ;			//执行SQL缓冲区
	char			nickName[64] = {0} ;
	char			retContentTmp[RETURN_CONTENT_LEN] = {0} ;
	char			returnContent[RETURN_CONTENT_LEN] = {0} ;
	char			idBuff[ID_BUFF_LEN] = {0} ;     //id的buff
	int             id = -1 ;						//修改的ID
	
	if(cgiFormSubmitClicked("modifyBtn") == cgiFormSuccess) //
	{
		if(cgiFormString("id",idBuff,sizeof(idBuff)) != cgiFormSuccess) 
		{
			fprintf(cgiOut,"<font color='#f00' size='20'>请输入ID</font>");
			//fprintf(cgiOut,"alert(\"返回内容为NULL,请输入返回内容\");");
			TMPL_write("ModifyInterface.htm",0,0,0,cgiOut,cgiOut);
			goto END ;
		}
		if(cgiFormString("returnContent",retContentTmp,sizeof(retContentTmp)) != cgiFormSuccess) 
		{
			fprintf(cgiOut,"<font color='#f00' size='20'>请输入返回内容</font>");
			//fprintf(cgiOut,"alert(\"返回内容为NULL,请输入返回内容\");");
			TMPL_write("ModifyInterface.htm",0,0,0,cgiOut,cgiOut);
			goto END ;
		}
	
	}
	else		//是增加内容
	{
		if(cgiFormString("returnContent",retContentTmp,sizeof(retContentTmp)) != cgiFormSuccess) 
		{
			fprintf(cgiOut,"<font color='#f00' size='20'>请输入返回内容</font>");
			//fprintf(cgiOut,"alert(\"返回内容为NULL,请输入返回内容\");");
			TMPL_write("CommonInterface.htm",0,0,0,cgiOut,cgiOut);
			goto END ;
		}
	}
	//转换id
	id = atoi(idBuff);
	//初始化数据库
	mysql = mysql_init(0);
	if(mysql == NULL)
	{
		ret = -1 ;
		printf("Func main() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}
	
	//连接数据库
	if(!mysql_real_connect(mysql,DB_IP,DB_USER,DB_PASSWORD,DB_NAME,0,0,0)) //连接失败
	{
		ret = -2 ;
		printf("Func mysql_real_connect() err:%d,(无法连接数据库:%s)\n",ret,mysql_error(mysql));
		goto END ;
	}
	
	//设置编码方式
	ret = ExecuteNonQuery(mysql,"set names utf8");
	if(ret != 0)
	{
		printf("Func ExecuteNonQuery() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}
	
	//将输入内容中的"转换为\"

	ret = ReplaceString(retContentTmp,returnContent,"\"","\\\"");
	if(ret != 0)
	{
		printf("Func RepalceString() err:%d\n",ret);
		goto END ;
	}

	if(id <= 0)		//增加数据
	{
		//向数据库中插入一条数据
		sprintf(sqlBuff,"insert into T_CommonInterface (ReturnContent) values(\"%s\")",returnContent);
		ret = ExecuteNonQuery(mysql,sqlBuff);
		if(ret != 0)
		{
			printf("Func mysql_query() err:%d,msg:%s\n",ret,mysql_error(mysql));
			goto END ;
		}	
	}
	else	//修改数据
	{
		//向数据库中插入一条数据
		//sprintf(sqlBuff,"insert into T_CommonInterface (ReturnContent) values(\"%s\")",returnContent);
		sprintf(sqlBuff,"UPDATE T_CommonInterface SET ReturnContent=\"%s\" WHERE id = %d ;",returnContent,id);
		ret = ExecuteNonQuery(mysql,sqlBuff);
		if(ret != 0)
		{
			printf("Func mysql_query() err:%d,msg:%s\n",ret,mysql_error(mysql));
			goto END ;
		}	
	
	}
	//MessageBoxA(0,"debug","ok",0);
	
	
	//查询接口信息
	memset(sqlBuff,0,sizeof(sqlBuff));
	sprintf(sqlBuff,"SELECT id FROM T_CommonInterface WHERE ReturnContent = '%s'",returnContent);
	//查询数据库数据
	ret = ExecuteQuery(mysql,sqlBuff,&pRs);
	if(ret != 0)
	{
		printf("Func ExecuteQuery() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}
	//遍历打印数据
	if(row = mysql_fetch_row(pRs))
	{
		char * pId = row[0];
		if(id <= 0)
		{
			fprintf(cgiOut,"<h2>增加接口成功(27网段访问):<a href='http://192.168.27.170:803/cgi-bin/CommonInterface.cgi?id=%s'>http://192.168.27.170:803/cgi-bin/CommonInterface.cgi?id=%s</a></h2></br>",pId,pId);
			fprintf(cgiOut,"<h2>增加接口成功(50网段访问(qiqiDev)):<a href='http://192.168.50.180/cgi-bin/CommonInterface.cgi?id=%s'>http://192.168.50.180/cgi-bin/CommonInterface.cgi?id=%s</a></h2></br>",pId,pId);
		}
		else
		{
			fprintf(cgiOut,"<h2>修改接口成功(27网段访问):<a href='http://192.168.27.170:803/cgi-bin/CommonInterface.cgi?id=%s'>http://192.168.27.170:803/cgi-bin/CommonInterface.cgi?id=%s</a></h2></br>",pId,pId);
			fprintf(cgiOut,"<h2>修改接口成功(50网段访问(qiqiDev)):<a href='http://192.168.50.180/cgi-bin/CommonInterface.cgi?id=%s'>http://192.168.50.180/cgi-bin/CommonInterface.cgi?id=%s</a></h2></br>",pId,pId);
		}
		
	}
	//

	//查询数据库数据
	ret = ExecuteQuery(mysql,"select Id,NickName,ReturnContent from T_CommonInterface",&pRs);
	if(ret != 0)
	{
		printf("Func ExecuteQuery() err:%d,msg:%s\n",ret,mysql_error(mysql));
		goto END ;
	}
	fprintf(cgiOut,"<table border='0.5'>");
	fprintf(cgiOut,"<tr bgcolor='#f0c465'>");
	fprintf(cgiOut,"<td>Id<td><td>ReturnContent</td>");
	fprintf(cgiOut,"</tr>");
	//遍历打印数据
	while(row = mysql_fetch_row(pRs))
	{
		char * pId = row[0];
		char * pRC = row[2];
		fprintf(cgiOut,"<tr bgcolor='#fefcc0'>");
		fprintf(cgiOut,"<td bgcolor='#a9fff6'>%s<td><td>%s</td>",pId,pRC) ;
		fprintf(cgiOut,"</tr>");
	}
	
END:
	//释放结果集
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
	//安全检查
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

/*
	替换字符串的方法
	src:源字符串指针
	buff:目标字符串缓冲区
	rpStr:被替换的字符串
	rpdStr:被换成的字符串
*/
int ReplaceString(char * src,char * buff,char * rpStr,char * rpdStr)
{
	int ret = 0 ;
	char * pSrc = NULL ;
	char * pBuff = NULL ;
	char * pIndex = NULL ;
	int index = 0 ;

	//进行安全检查
	if(src ==NULL || buff == NULL)
	{
		ret = -1 ;
		printf("Func ReplaceString() err:%d,(src ==NULL || buff == NULL)\n",ret);
		return ret ;
	}
	//建立关联
	pSrc = src ;
	pBuff = buff ;
	pIndex = src ;

	//查找字符串
	while(pSrc = strstr(pSrc,rpStr))
	{
		//判断开头是否我们要找的字符串
		if(pSrc == src)
		{
			memcpy(pBuff,rpdStr,strlen(rpdStr));
			index += strlen(rpdStr);
			
		}
		else
		{
			//先将找的字符串前面的字符串拷入
			memcpy(pBuff+index,pIndex,pSrc-pIndex);
			index += (pSrc - pIndex);

			//再把要替换的字符串拷如
			memcpy(pBuff+index,rpdStr,strlen(rpdStr));
			index += strlen(rpdStr);
			
		}
		pSrc+=strlen(rpStr);
		pIndex = pSrc ;
		

		//判断是否到结尾跳出
		if(*pSrc == '\0')
		{
			break ;
		}
	}
	//没到最后
	if(pIndex != src + strlen(src))
	{
		memcpy(pBuff+index,pIndex,src+strlen(src) - pIndex);
		index + src+strlen(src) - pSrc;
	}


	return ret ;
}