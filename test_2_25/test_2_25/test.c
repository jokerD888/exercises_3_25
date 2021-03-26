#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
//于堆区开辟
//malloc(),用于分配若干字节空间，返回一个指向该储存区地址的指针，若不能成功开辟则返回NULL
//int main(void)
//{
//	//向内存申请10个整型的空间
//	int* p = (int*)malloc(10 * sizeof(int));
//	if (p == NULL)
//	{
//		//打印错误原因的一个方式
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		//开辟成功
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
//	//释放返还空间
//	free(p);
//	p = NULL;
//	return 0;
//}


//callo（），增加初始化，申请空间每个字节为0 
//若需要初始化用callo,若不需要初始化可用malloc(效率较calloc会高些)
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
//	//释放动态开辟空间
//	free(p);
//	p = NULL;
//	return 0;
//}


//realloc,灵活调整动态内存开辟的大小
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
	//realloc使用注意
	//1.若p指向的空间之后有足够大的空间可以追加，则直接追加，返回p
	//2.若p指向的空间之后没有足够大的空间可以追加，则realloc函数会重新找一个新的满足要求的内存区域，
	//并把原来内存中的数据拷贝回来，释放旧的空间，返回新开辟的内存空间地址
	//3.得用一个新得变量来接受返回值（避免开辟失败，导致数据消失）
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
