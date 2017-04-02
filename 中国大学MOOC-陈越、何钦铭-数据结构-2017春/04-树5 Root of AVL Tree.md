## 题目

- An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.
Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.
## Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer NN (\le 20≤20) which is the total number of keys to be inserted. Then NN distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

## Output Specification:

For each test case, print the root of the resulting AVL tree in one line.

**Sample Input 1：**
```
5
88 70 61 96 120
```
**Sample Output 1:**
```
70
```
## AC测试代码：
```C
/*!
 * \file 04-树5 Root of AVL Tree.cpp
 *
 * \author ranjiewen
 * \date 2017/04/01 18:54
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode *Position;
typedef Position AVLTree;
typedef int ElementType;
struct AVLNode{
	ElementType Data;
	AVLTree Left;
	AVLTree Right;
	int Height;  //树高
};

int Max(int a, int b)
{
	return a > b ? a : b;
}

//可将程序中用到的GetTreeHeight()替换掉
int GetHeight(Position p)
{
	if (!p)
		return -1;
	return p->Height;
}

int GetTreeHeight(AVLTree T)
{
	int HL = 0, HR = 0;
	int Max_H = 0;
	if (T)
	{
		if (T->Left)
		{
			HL = GetTreeHeight(T->Left);
		}
		if (T->Right)
		{
			HR = GetTreeHeight(T->Right);
		}
		Max_H = (HL > HR) ? (HL + 1) : (HR + 1);
	}
	return  Max_H;
}

AVLTree SingleLeftRotation(AVLTree A)
{
	//A必须有一个左子结点B
	//将A与B做左单旋，更新A,B的高度，返回新的根节点B
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetTreeHeight(A->Left), GetTreeHeight(A->Right)) + 1;
	B->Height = Max(GetTreeHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
	//A必须有一个右子节点B
	//将A，B做右单旋，更新A，B的高度，返回新的根节点B
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetTreeHeight(A->Left),GetTreeHeight(A->Right))+1;
	B->Height = Max(GetTreeHeight(B->Right), A->Height) + 1;

	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
	//A必须有一个左子节点B，且B必须有一个右子节点C
	//将A,B与C做两次单旋，返回新的根节点C
	
	//将B,C做右单旋，C被返回
	A->Left = SingleRightRotation(A->Left);
	//将A与C做左单旋，C被返回
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
	//A必须有一个右子节点B,且B必须有一个左子节点C
	
	//将B，C做左单旋，C被返回
	A->Right = SingleLeftRotation(A->Right);
	//将A，C做右单旋，C被返回
	return SingleRightRotation(A);
}

//将x插入到AVL树中，并且返回调整后的AVL树
AVLTree Insert(AVLTree T, ElementType x)
{
	if (!T)
	{
		//若为空树，则新建包含一个结点的树
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = x;
		T->Left = T->Right = NULL;
		T->Height = 0;
	}
	else if (x<T->Data)
	{
		//插入T的左子树
		T->Left = Insert(T->Left,x);
		//如果需要左旋
		if (GetTreeHeight(T->Left)-GetTreeHeight(T->Right)==2)
		{
			if (x < T->Left->Data) //需要左单旋
			{
				T = SingleLeftRotation(T);
			}
			else
				T = DoubleLeftRightRotation(T); //左-右双旋
		}
	}
	else if (x>T->Data)
	{
		T->Right = Insert(T->Right,x);
		//如果需要右旋
		if (GetTreeHeight(T->Left)-GetTreeHeight(T->Right)==-2)
		{
			if (x>T->Right->Data) //右单旋
			{
				T = SingleRightRotation(T);
			}
			else
			{
				T = DoubleRightLeftRotation(T); //右-左双旋
			}
		}
	}
	// else x==T->Data 无需插入
	
	//别忘了更新树高
	T->Height = Max(GetTreeHeight(T->Left), GetTreeHeight(T->Right)) + 1;
	return T;
}

static int FindMin(AVLTree T){
	if (T == NULL){
		return -1;
	}
	while (T->Left != NULL){
		T = T->Left;
	}
	return T->Data;
}

//返回-1表示，树中没有该数据，删除失败，
int Delete(AVLTree *T, ElementType D){ //指针的指针
	static Position tmp;
	if (*T == NULL){
		return -1;
	}
	else{
		//找到要删除的节点
		if (D == (*T)->Data){
			//删除的节点左右子支都不为空，一定存在前驱节点
			if ((*T)->Left != NULL && (*T)->Right != NULL){

				D = FindMin((*T)->Right);//找后继替换
				(*T)->Data = D;
				Delete(&(*T)->Right, D);//然后删除后继节点，一定成功

				//在右子支中删除，删除后有可能左子支比右子支高度大2
				if (GetHeight((*T)->Left) - GetHeight((*T)->Left) == 2){
					//判断哪一个左子支的的两个子支哪个比较高
					if (GetHeight((*T)->Left->Left) >= GetHeight((*T)->Left->Right)){
						*T=SingleRightRotation(*T);
					}
					else{
						*T = DoubleLeftRightRotation(*T);
						/*LeftRotate(&(*T)->left);
						RightRotate(T);*/
					}
				}
			}
			else
			if ((*T)->Left == NULL){//左子支为空
				tmp = (*T);
				(*T) = tmp->Right;
				free(tmp);
				return 0;
			}
			else
			if ((*T)->Right == NULL){//右子支为空
				tmp = (*T);
				(*T) = tmp->Right;
				free(tmp);
				return 0;
			}
		}
		else
		if (D > (*T)->Data){//在右子支中寻找待删除的节点
			if (Delete(&(*T)->Right, D) == -1){
				return -1;//删除失败，不需要调整，直接返回
			}
			if (GetHeight((*T)->Left) - GetHeight((*T)->Right) == 2){
				if (GetHeight((*T)->Left->Left) >= GetHeight((*T)->Left->Right)){
					*T=SingleRightRotation(*T);
				}
				else{
					*T = DoubleLeftRightRotation(*T);
					/*LeftRotate(&(*T)->left);
					RightRotate(T);*/
				}
			}
		}
		else
		if (D < (*T)->Data){//在左子支中寻找待删除的节点
			if (Delete(&(*T)->Left, D) == -1){
				return -1;
			}
			if (GetHeight((*T)->Right) - GetHeight((*T)->Right) == 2){
				if (GetHeight((*T)->Right->Right) >= GetHeight((*T)->Right->Left)){
					*T=SingleLeftRotation(*T);
				}
				else{
					*T = DoubleRightLeftRotation(*T);
					/*RightRotate(&(*T)->right);
					LeftRotate(T);*/
				}
			}
		}
	}
	//更新当前节点的高度
	(*T)->Height = Max(GetHeight((*T)->Left), GetHeight((*T)->Right)) + 1;
	//printf("%d\n", (*T)->Data);
	return 0;
}

int main()
{
	int N,data;
	AVLTree root=nullptr;
	scanf("%d", &N);
	for (int i = 0; i < N;i++)
	{
		scanf("%d", &data);
		root = Insert(root, data);
	}
	printf("%d\n",root->Data);

	Delete(&root, 70);
	printf("%d\n", root->Data);

	return 0;
}


```
## 题目来源[04-树5 Root of AVL Tree](https://pta.patest.cn/pta/test/3512/exam/4/question/73454)
## 参考[04-树5 Root of AVL Tree + AVL树操作集](http://www.cnblogs.com/ranjiewen/p/6657964.html)
