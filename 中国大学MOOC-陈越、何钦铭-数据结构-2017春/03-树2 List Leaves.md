## 题目
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer NN (\le 10≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N-1N−1. Then NN lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

**Output Specification:**

For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

**Sample Input:**

8
```
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
```
**Sample Output:**
```
4 1 5
```
## 测试程序：
* 主要思想运用层次遍历的过程，判断是否为叶子结点，即可输出。关键点在对树的创建

```C++
#include <iostream>
#include <queue>

using namespace std;

#define  MaxTree 10
#define  ElementType int
#define  Tree int 
#define  Null -1

typedef struct TreeNode
{
    ElementType Data;
    Tree Left;
    Tree Right;
}TreeNode;

TreeNode T[MaxTree];

Tree BuildTree(TreeNode T[])
{
    int N = 0;
    bool Check[MaxTree];
    Tree ret_root = Null;
    char cl, cr;
    cin >> N;

    if (N)
    {
        for (int i = 0; i < N;i++)
        {
            Check[i] = false;
        }
        for (int i = 0; i < N;i++)
        {
            T[i].Data = i;
            cin >> cl >> cr;
            if (cl!='-')
            {
                T[i].Left = cl - '0';
                Check[T[i].Left] = true;
            }
            else
            {
                T[i].Left = Null;
            }
            if (cr!='-')
            {
                T[i].Right = cr - '0';
                Check[T[i].Right] = true;
            }
            else
            {
                T[i].Right = Null;
            }
        }
        for (int i = 0; i < N;i++)
        {
            if (!Check[i])
            {
                ret_root = i;
                break;
            }
        }
    }
    return ret_root;
}

void PrintLeaves(Tree  root)
{
    if (root==Null)
    {
        return;
    }
    queue<int> Q;
    Q.push(root);
    int flag = 1;//输出标志
    Tree temp;
    while (!Q.empty())
    {
        temp = Q.front();
        Q.pop();
        if (T[temp].Left==Null&&T[temp].Right==Null)
        {
            if (flag)
            {
                cout << T[temp].Data;
                flag = 0;
            }
            else
            {
                cout << " " << T[temp].Data;
            }
        
        }
        else
        {
            if (T[temp].Left!=Null)
            {
                Q.push(T[temp].Left);
            }
            if (T[temp].Right!=Null)
            {
                Q.push(T[temp].Right);
            }
        }
    }
}

int main()
{
    Tree root = Null;
    root = BuildTree(T);
    PrintLeaves(root);
    cout << endl;
    return 0;
}

```
