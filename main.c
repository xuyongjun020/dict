#include "cn_en.h"


int main(int argc, char *args[]){
	long start_ms = 0;//ͳ�ƿ�ʼʱ��
	long end_ms = 0;  //ͳ�ƽ���ʱ��

	if (argc < 2){
		printf("Usage : %s dict_filename\n",args[0]); //ʹ�õĸ�ʽ����
		return;
	}

	PDict pdict = NULL;

	start_ms = clock(); //�ļ��򿪵�ʱ��
	int size = open_dict(&pdict, args[1]);
	if (size == 0){
		return 0;//�ļ���ʧ��
	}
	end_ms = clock();  //�ļ��رյĿ�ʼʱ��
	printf("open_dict used : %ld \n",end_ms - start_ms);  //������ļ��򿪵�ʱ��

	while (1){
		char key[50] = { 0 }; //�û�����Ĺؼ���
		char content[200] = { 0 };	//���ط�����
		printf("������������ؼ��֣�");
		scanf("%s", key);

		if (strncmp(key, "cmd:exit", 8) == 0){
			break;//�˳���������
		}

		start_ms = clock(); //�ļ������Ŀ�ʼʱ��
		if (search_dict(pdict,key,content)){
			printf("%s\n",content);
		}
		else{
			printf("dict no found..\n");
		}
		end_ms = clock();  //�ļ������Ľ���ʱ��
		printf("search_dict used : %ld \n", end_ms - start_ms);  //�����������ʱ��
	}

	start_ms = clock(); //�رճ���Ŀ�ʼʱ��
	free_dict(pdict);
	end_ms = clock();  //�رճ���Ľ���ʱ��
	printf("free_dict used : %ld \n", end_ms - start_ms);  //������رճ����ʱ��

	return 0;
}