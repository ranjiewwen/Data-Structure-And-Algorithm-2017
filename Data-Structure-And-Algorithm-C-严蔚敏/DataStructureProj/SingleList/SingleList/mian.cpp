#include "common.h"
#include "SingleList.h"


Status comp(ElemType c1, ElemType c2)
{
    //数据元素判定函数（相等为True,否则为FALSE）
	if (c1 == c2)
	{
		return TRUE;
	}
	else
		return FALSE;
}
void visit(ElemType c)
{
	printf("%d", c);
}

int main()
{
	LinkList L;
	ElemType e, e0;
	Status i;
	int  k;
	SingleList s;
	i = s.InitList(&L);
	for (int j = 1; j <= 5;j++)
	{
		i = s.ListInsert(L, 1, j);
	}
	printf("在L的表头依次插入1~5后：L=");
	s.ListTraverse(L, visit);
	i = s.ListEmpty(L);
	printf("L是否空：i=%d(1:是 0：否)\n", i);
	for (int j = 1; j <= 10;j++)
	{
		s.ListInsert(L,j+5,j);
	}
	printf("在L的表尾依次插入1~10后：L=");
	s.ListTraverse(L,visit);
	s.GetElem(L,5,&e);
	printf("第5个元素的值为：%d\n", e);
	for (int j = 0; j <= 1; j++)
	{
		k = s.LocateElem(L, j, comp);
		if (k)
			printf("第%d个元素的值为%d\n", k, j);
		else
			printf("没有值为%d的元素\n", j);
	}
	for (int j = 1; j <= 2; j++) /* 测试头两个数据 */
	{
		s.GetElem(L, j, &e0); /* 把第j个数据赋给e0 */
		i = s.PriorElem(L, e0, &e); /* 求e0的前驱 */
		if (i == INFEASIBLE)
			printf("元素%d无前驱\n", e0);
		else
			printf("元素%d的前驱为：%d\n", e0, e);
	}
	for (int j = s.ListLength(L) - 1; j <= s.ListLength(L); j++)/*最后两个数据 */
	{
		s.GetElem(L, j, &e0); /* 把第j个数据赋给e0 */
		i = s.NextElem(L, e0, &e); /* 求e0的后继 */
		if (i == INFEASIBLE)
			printf("元素%d无后继\n", e0);
		else
			printf("元素%d的后继为：%d\n", e0, e);
	}
	k = s.ListLength(L); /* k为表长 */
	for (int j = k + 1; j >= k; j--)
	{
		i = s.ListDelete(L, j, &e); /* 删除第j个数据 */
		if (i == ERROR)
			printf("删除第%d个数据失败\n", j);
		else
			printf("删除的元素为：%d\n", e);
	}
	printf("依次输出L的元素：");
	s.ListTraverse(L, visit);
	s.DestroyList(&L);
	printf("销毁L后：L=%u\n", L);

	return 0;
}