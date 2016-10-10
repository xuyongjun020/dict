#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct dict
{
	char *key; //用户输入的检索关键字
	char *content; //翻译出来的内容
	struct dict *pNext;	//下一个节点
}Dict,*PDict;

int open_dict(PDict * p, const char * dict_filename); //加载打开字典文件

int search_dict(const PDict p, const char * key, char *content);  //检索

void free_dict(PDict p);//清空内存
