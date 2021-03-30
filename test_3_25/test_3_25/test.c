#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<stdio.h>
//88. 合并两个有序数组
//给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
//初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
//你可以假设 nums1 的空间大小等于 m + n，这样它就有足够的空间保存来自 nums2 的元素。

//法一：先将nums2中有效元素复制到nums1中最后一个有效元素的后面，再进行冒泡排序
//虽然这样也可以，但这样做复杂度比较高，而且浪费了题目给的“有序”数组这个条件
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) 
{
	int i = 0;
	int j = 0;
	int Size = n + m;
	//先将nums2中有效元素复制到nums1中最后一个有效元素的后面

	for (j = 0; j < n; j++)
	{
		nums1[m + j] = nums2[j];
	}
	//再进行冒泡排序
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

//法二：两个数组本身就是有序的，可以利用这个条件省去排序的操作，从num1的下标m+n-1开始，依次比较两个数组最后面的元素，较大值依次往前放入nums1中
//时间复杂度为O(N)
void merge1(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
	int Size = m + n - 1;
	int i = m - 1;//nums1最后元素下标
	int j = n - 1;//nums2最后元素下标
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
	//若j>=0，说明nums2中的元素还没有全部放入nums1中，且nums2中剩余元素都是有序的（其中的最大值比已经排列好的元素最小值还要小）
	//此时不需进行比较，直接把nums2中剩余元素一一放入nums1中即可
	//若i>=0,无需任何操作，nums1其本身就是有序的，且（若i>=0，那么j<0,才可跳出循环，进入下面的while循环中)
	//因为nums中元素都已比较完且有序放入nums1中，之后不需任何操作，已经是有序排列了
	while (j >= 0)
	{
		nums1[Size] = nums2[j];
		Size--;
		j--;
	}
}
//法三，时间复杂度为O(N+M),空间复杂度为O(M+N),以空间换时间，与法二类似
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
	//main函数仅为测试，若要提交LeetCode,仅提交函数块代码即可
	int nums1[6] = { 1,2,3,0,0,0};
	int nums2[3] = { 2,5,6 };

	merge2(nums1, 6, 3, nums2, 3, 3);
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", nums1[i]);
	}
	return 0;
}


//989. 数组形式的整数加法
//对于非负整数 X 而言，X 的数组形式是每位数字按从左到右的顺序形成的数组。例如，如果 X = 1231，那么其数组形式为[1, 2, 3, 1]。
//给定非负整数 X 的数组形式 A，返回整数 X + K 的数组形式。
int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
	int KSize = K;
	int Knum = 0;
	//计算K的位数
	while (KSize)
	{
		Knum++;
		KSize /= 10;
	}
	
	//len为X和K中位数最高,因为不知道K和X谁更大，
	int len = Knum > ASize ? Knum : ASize;
	//开辟一个（len+1）*（int)的空间，为9999999999 + 1 = 10000000000这类进位的情况考虑
	//才能放得下多一位数的数组，在len的长度上加一，可确保能放得下所有种可能的组合（X不一定比K大）
	int* retArr = (int*)malloc(sizeof(int) * (len + 1));

	//因为不知道两数相加后到底会不会多一位数，所以在这里选择倒着放入retArr"数组"中（从个位到高位依次放入）,之后再将数组逆序
	int Ai = ASize - 1;//数组A右下标
	int i = 0;
	int nextNum = 0;//进位标志
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
		//简化为
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
		//化简为
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
	//当nextNum==1,说明还有1位没有进
	if (nextNum == 1)
	{
		*(retArr + i) = 1;
		++i;
	}
	//i此时为retArr数组的元素个数
	*returnSize = i;

	//逆序回复
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
