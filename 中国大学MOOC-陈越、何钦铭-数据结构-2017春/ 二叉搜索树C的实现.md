## 二叉搜索树C的实现

二叉搜索树本身就是递归的定义，其查找，插入，删除操作尤为重要，主要理解其思路，学会创建和输出二叉树。

- **递归和非递归的转换**
- **不可以typedef;然后再次typedef**
- **考虑怎么将节点传出来； 1.根据返回值   2.用传指针的方式，所有函数形参改为指针的指针&root**
```C
/*!
 * \file 二叉搜索树的实现.cpp
 *
 * \author ranjiewen
 * \date 2017/03/29 17:13
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ELementType;
typedef struct BSTreeNode* BSTree;

struct BSTreeNode  //不可以typedef;然后再次typedef;
{
	ELementType Data;
	BSTree Left;
	BSTree Right;
};

//typedef BSTreeNode* Position;
typedef BSTree Position;

Position Find(ELementType x, BSTree BST); //返回所在节点的地址
Position FindMin(BSTree BST);
Position FinMax(BSTree BST);
BSTree Insert(ELementType x, BSTree BST);
BSTree Delete(ELementType x, BSTree BST);

//查找的效率取决于树的高度，和树的组织方法有关
Position Find(ELementType x, BSTree BST)
{
	if (!BST)
	{
		return NULL;
	}
	if (x > BST->Data)
	{
		return Find(x, BST->Right);  //尾递归都可以用循环的实现
	}
	else if (x < BST->Data)
	{
		return Find(x, BST->Left);
	}
	else  //x==BST->Data
	{
		return BST;
	}
}

//非递归的执行效率高，可将“尾递归”函数改为迭代函数实现
Position IterFinde(ELementType x, BSTree BST)
{
	while (BST)
	{
		if (x > BST->Data)
		{
			BST = BST->Right;
		}
		else if (x < BST->Data)
		{
			BST = BST->Left;
		}
		else
		{
			return BST;
		}
	}
	return NULL;
}

//递归实现
Position FindMin(BSTree BST)
{
	if (!BST)
	{
		return NULL;
	}
	else if (!BST->Left)
	{
		return BST;    //找到最左叶节点并返回
	}
	else
	{
		return FindMin(BST->Left);
	}
}

Position FinMax(BSTree	BST)
{
	if (!BST)
	{
		return NULL;
	}
	while (BST->Right)
	{
		BST = BST->Right;  //沿右分支继续查找，直到最右节点
	}
	return BST;
}

//关键是要找到元素应该插入的位置，可以采用与Find类似的方法
BSTree Insert(ELementType x, BSTree BST)
{
	if (!BST)
	{
		BST = (BSTree)malloc(sizeof(BSTreeNode));
		BST->Data = x;
		BST->Left = NULL;
		BST->Right = NULL;
	}
	else  //开始找到要插入元素的位置
	{
		if (x < BST->Data)
		{
			BST->Left = Insert(x, BST->Left);  //将子树的根节点挂在父节点下
		}
		else if (x > BST->Data)
		{
			BST->Right = Insert(x, BST->Right);
		}
		//else x已经存在
	}
	return BST;
}

//删除节点的三种情况： 
//     1.要删除的是叶节点：直接删除，并修改其父节点为NULL
//     2.要删除的结点只有一个孩子结点: 将其父结点的指针指向要删除结点的孩子结点
//     3.要删除的结点有左、右两棵子树： 用另一结点替代被删除结点：右子树的最小元素 或者 左子树的最大元素

BSTree Delete(ELementType x, BSTree BST)
{
	Position temp;
	if (!BST)
	{
		printf("要删除的元素未找到...\n");
	}
	else if (x < BST->Data)
	{
		BST->Left = Delete(x, BST->Left);
	}
	else if (x > BST->Data)
	{
		BST->Right = Delete(x, BST->Right);
	}
	else  //找到要删除的节点
	{
		if (BST->Left&&BST->Right) /*被删除的节点有左右两个子节点*/
		{
			temp = FindMin(BST->Right);

			BST->Data = temp->Data;
			BST->Right = Delete(BST->Data, BST->Right);
		}
		else   //被删除节点有一个或者无子节点 //这里的理解：已经到尾节点了，只有一个元素了
		{
			temp = BST;
			if (!BST->Left) //有右孩子
			{
				BST = BST->Right;
			}
			else if (!BST->Right)
			{
				BST = BST->Left;
			}
			free(temp);
		}
	}
	return BST;
}


BSTree CreateBST(BSTree BST)
{
	int N = 0;
	printf("请输入创建二叉搜索树的元素个数：\n");
	scanf("%d", &N);
	int data = 0;
	for (int i = 0; i < N; i++)
	{
		//scanf("%d", data);
		BST=Insert(i + 10, BST);//
	}
	return BST;
}

void PrintBST(BSTree BST)  //考虑怎么可视化的输出
{
	if (BST) //中序打印
	{
		PrintBST(BST->Left);
		printf("%3d", BST->Data);
		PrintBST(BST->Right);
	}
}

int main()
{
	BSTree root = NULL;
	//CreateBST(root);void 不行，要考虑怎么将节点传出来； 1.根据返回值   2.用传指针的方式，所有函数形参改为指针的指针&root

	root = CreateBST(root);
	PrintBST(root);
	printf("\n");

	BSTree temp;
	temp = Find(12, root);
	if (temp)
	{
		printf("search success!,search data is %d.\n", temp->Data);
	}
	else
	{
		printf("search failed!\n");
	}

	temp = IterFinde(12, root);
	if (temp)
	{
		printf("search success!,search data is %d.\n", temp->Data);
	}
	else
	{
		printf("search failed!\n");
	}

	root=Insert(8, root);
	PrintBST(root);
	printf("\n");

	root=Delete(12, root);
	PrintBST(root);
	printf("\n");

	return 0;
}
```
