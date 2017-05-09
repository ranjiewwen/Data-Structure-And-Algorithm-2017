## 题目

- According to Wikipedia:

- Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

- Merge sort works as follows: Divide the unsorted list into N sublists, each containing 1 element (a list of 1 element is considered sorted). Then repeatedly merge two adjacent sublists to produce new sorted sublists until there is only 1 sublist remaining.

- Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

### Input Specification:

- Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the NN numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

### Output Specification:

- For each test case, print in the first line either "Insertion Sort" or "Merge Sort" to indicate the method used to obtain the partial result. Then run this method for one more iteration and output in the second line the resuling sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

### Sample Input 1:

```
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
```

### Sample Output 1:

```
Insertion Sort
1 2 3 5 7 8 9 4 6 0
```

### Sample Input 2:

```
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
```
### Sample Output 2:

```
Merge Sort
1 2 3 8 4 5 7 9 0 6
```
### 中文题目：

```
根据维基百科的定义：

插入排序是迭代算法，逐一获得输入数据，逐步产生有序的输出序列。每步迭代中，算法从输入序列中取出一元素，将之插入有序序列中正确的位置。如此迭代直到全部元素有序。

归并排序进行如下迭代操作：首先将原始序列看成N个只包含1个元素的有序子序列，然后每次迭代归并两个相邻的有序子序列，直到最后只剩下1个有序的序列。

现给定原始序列和由某排序算法产生的中间序列，请你判断该算法究竟是哪种排序算法？

输入格式：

输入在第一行给出正整数N (<=100)；随后一行给出原始序列的N个整数；最后一行给出由某排序算法产生的中间序列。这里假设排序的目标序列是升序。数字间以空格分隔。

输出格式：

首先在第1行中输出“Insertion Sort”表示插入排序、或“Merge Sort”表示归并排序；然后在第2行中输出用该排序算法再迭代一轮的结果序列。题目保证每组测试的结果是唯一的。数字间以空格分隔，且行末不得有多余空格。

```
## 代码

```C++

#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

typedef int ElementType;

//判断两个数组是否一样
bool JudgeTheSame(int origin[],int changed[],int len) 
{
    for(int i=0;i<len;i++)
    {
        if(origin[i]!=changed[i])
            return false;
    }
    return true;
}

//进行一次插入排序，参数：待排序数组，数组长度，当前排序次数，已有序元素Nums-1个
void InsertSort(ElementType origin[],int N,int Nums)
{
    int i;
    ElementType temp=origin[Nums]; //取出未排序列中的第一个元素
    for(i=Nums;i>0&&origin[i-1]>temp;i--)
    {
        origin[i]=origin[i-1];   //从小到大排序，未找到插入位置，元素依次向后移动
    }
    origin[i]=temp;
}

void Insert_Sort(int origin[],int N,int changed[])
{
    for(int i=1;i<N;i++) //从第二个元素开始插入排序
    {
        InsertSort(origin,N,i);
        if(JudgeTheSame(origin,changed,N)) //一轮插入排序后判断结果
        {
            cout<<"Insertion Sort"<<endl;
            InsertSort(origin,N,i+1);
            for(int j=0;j<N-1;j++)
                cout<<origin[j]<<" ";
            cout<<origin[N-1]<<endl;
            return;
        }
    }
}

/*L=左边的起始位置，R=右边起始位置，RightEnd=右边终点位置*/
void Merge(ElementType A[],ElementType TempA[],int L,int R,int RightEnd)
{
    /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd=R-1;
    int temp=L; //有序序列的起始位置
    int NumElements=RightEnd-L+1;
    
    while(L<=LeftEnd&&R<=RightEnd)
    {
        if(A[L]<=A[R])
            TempA[temp++]=A[L++]; /*注意下标的使用temp*/
        else 
            TempA[temp++]=A[R++];
    }
    while(L<=LeftEnd)
        TempA[temp++]=A[L++];
    while(R<=RightEnd)
        TempA[temp++]=A[R++];
    
    //for(int i=0;i<NumElements;i++,RightEnd--) //由于L，R等数组下标已经改变，RightEnd没有变
    //    A[RightEnd]=TempA[RightEnd]; //拷贝数据到原始数组中
}

/*length = 当前有序子列的长度，两两归并相邻有序子列*/
void Merge_pass(ElementType A[],ElementType TempA[],int N,int length)
{
    int i,j;
    for(i=0;i<=N-2*length;i+=2*length)
        Merge(A,TempA,i,i+length,i+2*length-1);
    if(i+length<N)  //归并最后2个子列
        Merge(A,TempA,i,i+length,N-1);
    else  //最后只剩一个子列
    {
        for(j=i;j<N;j++)
            TempA[j]=A[j];
    }
}

void Merge_Sort(ElementType A[],int N,int changed[])
{
    int length=1; //初始化子序列长度
    ElementType *TempA;
    TempA=(ElementType*)malloc(N*sizeof(ElementType)); //提前分配好空间
    
    if(TempA!=NULL)
    {
        while(length<N)
        {
            Merge_pass(A,TempA,N,length);
            if(JudgeTheSame(TempA,changed,N)) //归并排序后的结果
            {
                cout<<"Merge Sort\n";
                length*=2;
                Merge_pass(TempA,A,N,length); //再归并一次,交换了顺序,节约空间，反复利用A,TempA
                for(int i=0;i<N-1;i++)
                    cout<<A[i]<<" ";
                cout<<A[N-1]<<endl;
                return;
            }
            
            length*=2;
            Merge_pass(TempA,A,N,length);
            if(JudgeTheSame(TempA,changed,N)) //归并排序后的结果
            {
                cout<<"Merge Sort\n";
                length*=2;
                Merge_pass(A,TempA,N,length); //再归并一次,交换了顺序
                for(int i=0;i<N-1;i++)
					cout << TempA[i] << " ";
				cout << TempA[N - 1] << endl;
                return;
            }
            
            length*=2;
        }
        free(TempA);
    }
    else
    {
        cout<<"空间不足"<<endl;
    }
}

int main()
{
    int N;
    int origin[105],origin_copy[105],changed[105];
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>origin[i];
        origin_copy[i]=origin[i];
    }
    
    for(int i=0;i<N;i++)  //中间排序结果
        cin>>changed[i];
    
    Insert_Sort(origin,N,changed);
    Merge_Sort(origin_copy,N,changed);
    
    return 0;
}

```

## Reference

- [题目来源](https://pta.patest.cn/pta/test/3512/exam/4/question/88697)

- [09-排序2 Insert or Merge](http://www.cnblogs.com/kuotian/p/5460312.html)
