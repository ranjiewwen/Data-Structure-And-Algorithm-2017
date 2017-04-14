## 题目

- This time let us consider the situation in the movie "Live and Let Die" in which James Bond, the world's most famous spy, was captured by a group of drug dealers. He was sent to a small piece of land at the center of a lake filled with crocodiles. There he performed the most daring action to escape -- he jumped onto the head of the nearest crocodile! Before the animal realized what was happening, James jumped again onto the next big head... Finally he reached the bank before the last crocodile could bite him (actually the stunt man was caught by the big mouth and barely escaped with his extra thick boot).

- Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) and the northeast corner at (50,50). The central island is a disk centered at (0,0) with the diameter of 15. A number of crocodiles are in the lake at various positions. Given the coordinates of each crocodile and the distance that James could jump, you must tell him whether or not he can escape.

### Input Specification:

- Each input file contains one test case. Each case starts with a line containing two positive integers NN (\le 100≤100), the number of crocodiles, and DD, the maximum distance that James could jump. Then NN lines follow, each containing the (x, y)(x,y) location of a crocodile. Note that no two crocodiles are staying at the same position.

### Output Specification:

- For each test case, print in a line "Yes" if James can escape, or "No" if not.

### Sample Input 1:

```
14 20
25 -15
-25 28
8 49
29 15
-35 -2
5 28
27 -29
-8 -28
-20 -35
-25 -20
-13 29
-30 15
-35 40
12 12
```

### Sample Output 1:
```
Yes
```
### Sample Input 2:
```
4 13
-12 12
12 12
-12 -12
12 -12
```
### Sample Output 2:
```
No
```
### 思路

- 采用深度优先遍历的思想，针对每一跳进行判断，并返回相应的信息

## AC代码

```C++
/*!
 * \file 06-图2 Saving James Bond - Easy Version.cpp
 *
 * \author ranjiewen
 * \date 2017/04/14 22:46
 *
 * 
 */

#include<iostream>
using namespace std;
#define MaxSize 100

int N, D; //顶点个数，007能跳的距离

struct coordinate_
{
	int x;
	int y;
}coordinate[MaxSize];

bool Visited[MaxSize] = { false };

bool firstJump(int x,int y)
{
	if (x*x+y*y<=(7.5+D)*(7.5+D))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Jump(int V,int i) //非第一跳
{
	int x1 = coordinate[V].x;
	int y1 = coordinate[V].y;
	int x2 = coordinate[i].x;
	int y2 = coordinate[i].y;
	if ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)<=D*D)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isSave(int V)
{
	if (coordinate[V].x+D>=50||coordinate[V].y+D>=50||(coordinate[V].x-D)<=-50||(coordinate[V].y-D)<=-50)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DFS(int V)
{
	bool answer = false;
	Visited[V] = true;
	//首先判断是否可以达到陆地
	if (isSave(V))
	{
		return true;
	}
	else
	{
		for (int i = 0; i < N;i++)
		{
			if (!Visited[i]&&Jump(V,i))
			{
				answer = DFS(i);
				if (answer==true)
				{
					break;
				}
			}
		}
	}
	return answer;
}

void Svave007()
{
	bool answer = false;
	for (int i = 0; i < N; i++)
	{
		if (!Visited[i]&&firstJump(coordinate[i].x,coordinate[i].y))
		{
			answer = DFS(i);
			if (answer==true)
			{
				break;
			}
		}
	}
	if (answer==true)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
}

int main()
{
	scanf("%d %d", &N, &D);
	
	for (int i = 0; i < N;i++)
	{
		scanf("%d %d", &coordinate[i].x, &coordinate[i].y);
	}

	Svave007();

	return 0;
}



```

