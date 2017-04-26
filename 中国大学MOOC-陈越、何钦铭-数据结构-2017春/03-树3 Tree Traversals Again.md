## 题目

- An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.

### Input Specification:

- Each input file contains one test case. For each case, the first line contains a positive integer N(≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

### Output Specification:

- For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

### Sample Input:
```
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
```
### Sample Output:
```
3 4 2 6 5 1
```
## AC代码
```C++
/*!
 * \file 03-树3 Tree Traversals Again.cpp
 *
 * \author ranjiewen
 * \date 2017/04/25 23:51
 *
 * 
 */

#include <iostream>
#include <cstdio>
#include <stack>
#include <string>

using namespace std;

#define MaxSive 30
#define OK 0
#define ERROR -1

int preOrder[MaxSive];
int inOrder[MaxSive];
int postOrder[MaxSive];

void postOrderTraversal(int preNum,int inNum,int postNum,int Num);

int main()
{
	stack<int> s;
	int N; //树的结点数
	cin >> N;
	string str;
	int data;
	int preNum = 0, inNum = 0, postNum = 0;
	for (int i = 0; i < N * 2;i++)  //push+pop=N*2 
	{
		cin >> str;
		if (str=="Push") //Push为前序序列
		{
			cin >> data;
			preOrder[preNum++] = data;
			s.push(data);
		}
		else  //Pop为中序序列
		{
			inOrder[inNum++] = s.top();
			s.pop();  //移除栈顶元素（不会返回栈顶元素的值）
		}
	}

	postOrderTraversal(0,0,0,N); //每棵子树前，中，后序数组的开始下标，N为子树的结点个数

	for (int i = 0; i < N;i++)  //输出后序遍历序列
	{
		if (i==0)   //输出格式控制
		{
			printf("%d", postOrder[i]);
		}
		else
		{
			printf(" %d", postOrder[i]);
		}
	}
	printf("\n");

	return 0;
}

void postOrderTraversal(int preNum, int inNum, int postNum, int Num)
{
	if (Num==0)
	{
		return;
	}
	if (Num==1)
	{
		postOrder[postNum] = preOrder[preNum];
		return;
	}

	int L=0, R=0; //递归左右子树的结点个数
	int root = preOrder[preNum]; //先序遍历的第一个节点为根节点
	postOrder[postNum + Num - 1] = root; //填后序遍历的坑

	for (int i = 0; i < Num;i++)
	{
		if (inOrder[i+inNum] == root)//不要掉了preNum //在中序遍历中找到根节点，分为左右子树递归
		{
			L = i;  //左子树结点个数
			break;
		}
	}
	R = Num- L - 1; //右子树结点个数
	postOrderTraversal(preNum+1,inNum,postNum,L);
	postOrderTraversal(preNum + L + 1, inNum + L + 1, postNum + L, R); //右子树递归调用，注意开始下标

}


```
### [题目来源](https://pta.patest.cn/pta/test/3512/exam/4/question/69052)
