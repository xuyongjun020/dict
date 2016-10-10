#include "cn_en.h"


int main(int argc, char *args[]){
	long start_ms = 0;//统计开始时间
	long end_ms = 0;  //统计结束时间

	if (argc < 2){
		printf("Usage : %s dict_filename\n",args[0]); //使用的格式错误
		return;
	}

	PDict pdict = NULL;

	start_ms = clock(); //文件打开的时间
	int size = open_dict(&pdict, args[1]);
	if (size == 0){
		return 0;//文件打开失败
	}
	end_ms = clock();  //文件关闭的开始时间
	printf("open_dict used : %ld \n",end_ms - start_ms);  //计算出文件打开的时间

	while (1){
		char key[50] = { 0 }; //用户输入的关键字
		char content[200] = { 0 };	//返回翻译结果
		printf("请你输入检索关键字：");
		scanf("%s", key);

		if (strncmp(key, "cmd:exit", 8) == 0){
			break;//退出检索程序
		}

		start_ms = clock(); //文件检索的开始时间
		if (search_dict(pdict,key,content)){
			printf("%s\n",content);
		}
		else{
			printf("dict no found..\n");
		}
		end_ms = clock();  //文件检索的结束时间
		printf("search_dict used : %ld \n", end_ms - start_ms);  //计算出检索的时间
	}

	start_ms = clock(); //关闭程序的开始时间
	free_dict(pdict);
	end_ms = clock();  //关闭程序的结束时间
	printf("free_dict used : %ld \n", end_ms - start_ms);  //计算出关闭程序的时间

	return 0;
}