#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct dict
{
	char *key; //�û�����ļ����ؼ���
	char *content; //�������������
	struct dict *pNext;	//��һ���ڵ�
}Dict,*PDict;

int open_dict(PDict * p, const char * dict_filename); //���ش��ֵ��ļ�

int search_dict(const PDict p, const char * key, char *content);  //����

void free_dict(PDict p);//����ڴ�
