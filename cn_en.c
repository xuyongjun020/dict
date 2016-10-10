#include "cn_en.h"

int open_dict(PDict * p, const char * dict_filename){

	FILE *pfr = fopen(dict_filename, "r"); //��ֻ���ķ�ʽ�������ֵ�
	if (pfr == NULL){
		printf("open_dict�����У������ֵ��ʧ��\n");
		return 0;
	}
	
	*p = malloc(sizeof(Dict)); //�ڶ��ǿ������ݿռ�
	memset(*p, 0, sizeof(Dict));//��ʼ������

	char buf[1024] = { 0 };//����һ����ʱ���������ڱ��������ֵ��е�ÿһ������
	int i = 0;//ͳ���ж���������
	size_t length = 0; //�����ж����ݵĳ����Ƿ�Ϊ��

	PDict pd = *p;

	while (!feof(pfr)){
		memset(buf, 0, strlen(buf));
		fgets(buf, 1024, pfr); //ȡ�õ�һ������
		length = strlen(buf);//ȡ�õ�һ�����ݳ���
		if (length > 0){  //����Ϊ0�Ĳ�ִ�в���
			pd->key =malloc(sizeof(char)*length);
			memset(pd->key, 0, sizeof(char)*length);
			strcpy(pd->key, &buf[1]);//���ݸ�ʽΪ��#abaft  ����ֻȡ��abaft 
		}

		memset(buf, 0, strlen(buf));
		fgets(buf, 1024, pfr); //ȡ�õڶ�������
		length = strlen(buf);//ȡ�õڶ������ݳ���
		if (length > 0){
			pd->content = malloc(sizeof(char)*length);
			memset(pd->content, 0, sizeof(char)*length);
			strcpy(pd->content, &buf[6]);		 //Trans:ad. ��β@prep. ��...��
		}

		pd->pNext = malloc(sizeof(Dict)); //Ϊ��һ���ڵ�����ڴ�ռ�
		memset(pd->pNext, 0, sizeof(Dict));
		pd = pd->pNext;	   //��pDָ����һ���ڵ�λ��

		i++; //ÿ��ȡ2������ͳ��Ϊһ��
	}

	fclose(pfr); //�ر������ֵ�

	return i;//���ش�����

}

int search_dict(const PDict p, const char * key, char *content){
	for (PDict pd = p; pd != NULL; pd = pd->pNext){

		if (pd->key == NULL || pd->content == NULL){
			continue;
		}
		if (strncmp(pd->key, key, strlen(key)) == 0){
			strcpy(content, pd->content);
			return 1;
		}
	}
	return 0;
}

void free_dict(PDict p){
	PDict pd = p;
	while (pd){
		if (pd->key){
			free(pd->key);
		}
		if (pd->content){
			free(pd->content);
		}
	}
	PDict ptemp = pd->pNext;
	free(pd);
	pd = ptemp;
}

