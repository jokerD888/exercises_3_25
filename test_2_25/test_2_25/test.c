#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
//�ڶ�������
//malloc(),���ڷ��������ֽڿռ䣬����һ��ָ��ô�������ַ��ָ�룬�����ܳɹ������򷵻�NULL
//int main(void)
//{
//	//���ڴ�����10�����͵Ŀռ�
//	int* p = (int*)malloc(10 * sizeof(int));
//	if (p == NULL)
//	{
//		//��ӡ����ԭ���һ����ʽ
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		//���ٳɹ�
//		int i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ",*(p+i));
//		}
//		 
//	}
//
//	//�ͷŷ����ռ�
//	free(p);
//	p = NULL;
//	return 0;
//}


//callo���������ӳ�ʼ��������ռ�ÿ���ֽ�Ϊ0 
//����Ҫ��ʼ����callo,������Ҫ��ʼ������malloc(Ч�ʽ�calloc���Щ)
//int main(void)
//{
////	int* p = (int*)malloc(10 * sizeof(int));
//	int* p = (int*)calloc(10, sizeof(int));
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		int i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p + i));
//		}
//	}
//	//�ͷŶ�̬���ٿռ�
//	free(p);
//	p = NULL;
//	return 0;
//}


//realloc,��������̬�ڴ濪�ٵĴ�С
int main(void)
{
	int i = 0;
	int*p= (int*)malloc(20);
	if (p == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	else
	{
		for (i = 0; i < 5; i++)
		{
			*(p + i) = i;
		}
	}
	//reallocʹ��ע��
	//1.��pָ��Ŀռ�֮�����㹻��Ŀռ����׷�ӣ���ֱ��׷�ӣ�����p
	//2.��pָ��Ŀռ�֮��û���㹻��Ŀռ����׷�ӣ���realloc������������һ���µ�����Ҫ����ڴ�����
	//����ԭ���ڴ��е����ݿ����������ͷžɵĿռ䣬�����¿��ٵ��ڴ�ռ��ַ
	//3.����һ���µñ��������ܷ���ֵ�����⿪��ʧ�ܣ�����������ʧ��
	int* ptr = realloc(p, 4000	);
	if(ptr!=NULL)
	{
		p = ptr;
		for (i = 5; i < 10; i++)
		{
			*(p + i) = i;
		}
		for (i = 0; i < 10; i++)
		{
			printf("%d ", *(p + i));
		}
	}
	free(p);
	p = NULL;
	return 0;
}
