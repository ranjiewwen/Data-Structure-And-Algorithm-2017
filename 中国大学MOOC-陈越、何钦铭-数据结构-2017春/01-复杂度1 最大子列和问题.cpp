

//01 - 复杂度1 最大子列和问题(20分)
//例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。
//
//本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：
//
//数据1：与样例等价，测试基本正确性；
//数据2：10^2个随机整数；
//数据3：10^3个随机整数；
//数据4：10^4个随机整数；
//数据5：10^5个随机整数；
//输入格式 :
//
//输入第1行给出正整数KK(\le 100000≤100000)；第2行给出KK个整数，其间以空格分隔。
//
//输出格式 :
//
//在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。
//
//输入样例 :
//
//6
//- 2 11 - 4 13 - 5 - 2
//输出样例 :
//
//	 20

#include <iostream>
using namespace std;
#include <vector>

#define max(a,b)    (((a) > (b)) ? (a) : (b))

int GetMaxSubsum(vector<int> vec_);

int main()
{
	int k;
	int num;
	int ret = 0;
	vector<int> vec;
	while (cin>>k)
	{
		for (int i = 0; i < k;i++)
		{
			cin >> num;
			vec.push_back(num);
		}
		
		ret = GetMaxSubsum(vec);
		cout << ret << endl;
		vec.clear();
	}
	return 0;
}

int GetMaxSubsum(vector<int> vec_)
{
	int tempSum = 0;
	int ret_sum = 0;
	if (vec_.size()<=0)
	{
		return 0;
	}
	else
	{
		tempSum = vec_[0];
		ret_sum = vec_[0];
		for (int i = 1; i < vec_.size();i++)
		{
			tempSum = (tempSum < 0) ? vec_[i] : (tempSum + vec_[i]);
			ret_sum = max(tempSum,ret_sum);
		}
		return ret_sum;
	}
	return ret_sum;
}