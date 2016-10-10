#include "cn_en.h"

int open_dict(PDict * p, const char * dict_filename){

	FILE *pfr = fopen(dict_filename, "r"); //以只读的方式打开数据字典
	if (pfr == NULL){
		printf("open_dict方法中，数据字典打开失败\n");
		return 0;
	}
	
	*p = malloc(sizeof(Dict)); //在堆是开辟内容空间
	memset(*p, 0, sizeof(Dict));//初始化数据

	char buf[1024] = { 0 };//定义一个临时变量，用于保存数据字典中的每一行数据
	int i = 0;//统计有多少条词条
	size_t length = 0; //用于判断数据的长度是否为空

	PDict pd = *p;

	while (!feof(pfr)){
		memset(buf, 0, strlen(buf));
		fgets(buf, 1024, pfr); //取得第一条数据
		length = strlen(buf);//取得第一条数据长度
		if (length > 0){  //长度为0的不执行操作
			pd->key =malloc(sizeof(char)*length);
			memset(pd->key, 0, sizeof(char)*length);
			strcpy(pd->key, &buf[1]);//数据格式为：#abaft  所以只取：abaft 
		}

		memset(buf, 0, strlen(buf));
		fgets(buf, 1024, pfr); //取得第二条数据
		length = strlen(buf);//取得第二条数据长度
		if (length > 0){
			pd->content = malloc(sizeof(char)*length);
			memset(pd->content, 0, sizeof(char)*length);
			strcpy(pd->content, &buf[6]);		 //Trans:ad. 向船尾@prep. 在...后
		}

		pd->pNext = malloc(sizeof(Dict)); //为下一个节点分配内存空间
		memset(pd->pNext, 0, sizeof(Dict));
		pd = pd->pNext;	   //将pD指向下一个节点位置

		i++; //每读取2条数据统计为一次
	}

	fclose(pfr); //关闭数据字典

	return i;//返回词条数

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

