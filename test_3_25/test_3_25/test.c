#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<stdio.h>
//88. �ϲ�������������
//�������������������� nums1 �� nums2�����㽫 nums2 �ϲ��� nums1 �У�ʹ nums1 ��Ϊһ���������顣
//��ʼ�� nums1 �� nums2 ��Ԫ�������ֱ�Ϊ m �� n ��
//����Լ��� nums1 �Ŀռ��С���� m + n�������������㹻�Ŀռ䱣������ nums2 ��Ԫ�ء�

//��һ���Ƚ�nums2����ЧԪ�ظ��Ƶ�nums1�����һ����ЧԪ�صĺ��棬�ٽ���ð������
//��Ȼ����Ҳ���ԣ������������ӶȱȽϸߣ������˷�����Ŀ���ġ����������������
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) 
{
	int i = 0;
	int j = 0;
	int Size = n + m;
	//�Ƚ�nums2����ЧԪ�ظ��Ƶ�nums1�����һ����ЧԪ�صĺ���

	for (j = 0; j < n; j++)
	{
		nums1[m + j] = nums2[j];
	}
	//�ٽ���ð������
	for (i = 0; i < Size - 1; i++)
	{
		for (j = 0; j < Size - 1 - i; j++)
		{
			if (nums1[j] > nums1[j + 1])
			{

				int tmp = nums1[j];
				nums1[j] = nums1[j + 1];
				nums1[j + 1] = tmp;
			}
		}
	}
}

//�������������鱾���������ģ����������������ʡȥ����Ĳ�������num1���±�m+n-1��ʼ�����αȽ���������������Ԫ�أ��ϴ�ֵ������ǰ����nums1��
//ʱ�临�Ӷ�ΪO(N)
void merge1(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
	int Size = m + n - 1;
	int i = m - 1;//nums1���Ԫ���±�
	int j = n - 1;//nums2���Ԫ���±�
	while (j >= 0 && i >= 0)
	{
		if (nums2[j] > nums1[i])
		{
			nums1[Size] = nums2[j];
			j--;
		}
		else
		{
			nums1[Size] = nums1[i];
			i--;
		}
		Size--;
	}
	//��j>=0��˵��nums2�е�Ԫ�ػ�û��ȫ������nums1�У���nums2��ʣ��Ԫ�ض�������ģ����е����ֵ���Ѿ����кõ�Ԫ����Сֵ��ҪС��
	//��ʱ������бȽϣ�ֱ�Ӱ�nums2��ʣ��Ԫ��һһ����nums1�м���
	//��i>=0,�����κβ�����nums1�䱾���������ģ��ң���i>=0����ôj<0,�ſ�����ѭ�������������whileѭ����)
	//��Ϊnums��Ԫ�ض��ѱȽ������������nums1�У�֮�����κβ������Ѿ�������������
	while (j >= 0)
	{
		nums1[Size] = nums2[j];
		Size--;
		j--;
	}
}
//������ʱ�临�Ӷ�ΪO(N+M),�ռ临�Ӷ�ΪO(M+N),�Կռ任ʱ�䣬�뷨������
void merge2(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
	int* tmp = (int*)malloc(sizeof(int)*(m+n));

	int i1 = 0, i2 = 0;
	int i = 0;
	while (i1 < m && i2 < n)
	{
		if (nums1[i1] < nums2[i2])
		{
			tmp[i] = nums1[i1];
			++i;
			++i1;
		}
		else
		{
			tmp[i] = nums2[i2];
			++i;
			++i2;
		}
	}

	while (i1 < m)
	{
		tmp[i] = nums1[i1];
		++i;
		++i1;
	}
	while (i2 < n)
	{
		tmp[i] = nums2[i2];
		++i;
		++i2;
	}
	memcpy(nums1, tmp, sizeof(int) * (m + n));
	free(tmp);
}

int main(void)
{
	//main������Ϊ���ԣ���Ҫ�ύLeetCode,���ύ��������뼴��
	int nums1[6] = { 1,2,3,0,0,0};
	int nums2[3] = { 2,5,6 };

	merge2(nums1, 6, 3, nums2, 3, 3);
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", nums1[i]);
	}
	return 0;
}


//989. ������ʽ�������ӷ�
//���ڷǸ����� X ���ԣ�X ��������ʽ��ÿλ���ְ������ҵ�˳���γɵ����顣���磬��� X = 1231����ô��������ʽΪ[1, 2, 3, 1]��
//�����Ǹ����� X ��������ʽ A���������� X + K ��������ʽ��
int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
	int KSize = K;
	int Knum = 0;
	//����K��λ��
	while (KSize)
	{
		Knum++;
		KSize /= 10;
	}
	
	//lenΪX��K��λ�����,��Ϊ��֪��K��X˭����
	int len = Knum > ASize ? Knum : ASize;
	//����һ����len+1��*��int)�Ŀռ䣬Ϊ9999999999 + 1 = 10000000000�����λ���������
	//���ܷŵ��¶�һλ�������飬��len�ĳ����ϼ�һ����ȷ���ܷŵ��������ֿ��ܵ���ϣ�X��һ����K��
	int* retArr = (int*)malloc(sizeof(int) * (len + 1));

	//��Ϊ��֪��������Ӻ󵽵׻᲻���һλ��������������ѡ���ŷ���retArr"����"�У��Ӹ�λ����λ���η��룩,֮���ٽ���������
	int Ai = ASize - 1;//����A���±�
	int i = 0;
	int nextNum = 0;//��λ��־
	while (len--)
	{
		int sum = 0;
		int a = 0;
		//if (Ai>=0)
		//{
		//	sum = A[Ai] + K % 10+nextNum;
		//	Ai--;
		//	K /= 10;
		//}
		//else
		//{
		//	sum = K % 10+nextNum;//3 
		//	K /= 10;
		//}
		//��Ϊ
		if (Ai >= 0)
		{
			a = A[Ai];
			Ai--;
		}
		sum = a + K % 10 + nextNum;
		K /= 10;

		/*if (sum > 9)
		{
			*(retArr + i) = sum%10;
			nextNum = 1;
			i++;
		}
		else
		{
			*(retArr + i) = sum ;
			i++;
			nextNum = 0;
		}*/
		//����Ϊ
		if (sum > 9)
		{
			sum -= 10;
			nextNum = 1;
		}
		else
		{
			nextNum = 0;
		}

		*(retArr + i) = sum;
		++i;	

	}
	//��nextNum==1,˵������1λû�н�
	if (nextNum == 1)
	{
		*(retArr + i) = 1;
		++i;
	}
	//i��ʱΪretArr�����Ԫ�ظ���
	*returnSize = i;

	//����ظ�
	int left = 0;
	int right = i-1;
	while (left < right)
	{
		int tmp = retArr[left];
		retArr[left] = retArr[right];
		retArr[right] = tmp;
		left++;
		right--;
	}
	return retArr;


}
//int main(void)
//{
//	int A[4] = { 1,2,0,0 };
//	int k = 34;
//	int returnSize = 0;
//	int i = 0;
//	int *pr=addToArrayForm(A, 4, k, &returnSize);
//	for (i = 0; i < returnSize; i++)
//	{
//		printf("%d ", *(pr+i));
//	}
//	return 0;
//}
