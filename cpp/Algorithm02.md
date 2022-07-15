# 1.时间复杂度和空间复杂度
## 1-1.概念
1. 定义:算法中**基本操作的执行次数**为时间复杂度
2. 大O渐进表示法
   1. 推导大O表示法:
      1. 用1取代运行时间中的所有加法常数
      2. 在修改后的运行次数函数中， 只保留最高阶项
      3. 如果最高阶项存在且不是1，则去除与这个项目相乘的常数，得到的就是O阶
   2. 通过上面的计算，Func1执行次数: $F(N) = N^2 + N*2 + 10$,所以实际上我们只需要知道大概的执行次数，那么需要用到大O表示法，所以$T(n) = O(N^2)$
   3. 有的情况下，算法中基本操作重复执行的次数还随着**输入数据集**的不同而不同
      1. 最坏时间复杂度:最坏情况下，算法的时间6来说考虑**最坏时间复杂度**，因为考虑最坏情况下的时间复杂度，可以保证算法的运行时间不会比他更长
3. 空间复杂度
   1. 定义:算法所需存储空间的度量，记作:S(n) = O(f(n)),其中n为问题的规模(大小)
   2. 算法本身要占据的空间:
      1. 输入/输出,指令，常数，变量等
      2. *算法要使用的辅助空间*
   3. 一般来说只需要关心与空间大小与问题规模相关的变量
   4. 如何计算
      1. 普通程序
      2. 找到所占空间大小和问题规模相关的变量
      3. 分析所占变量x与问题规模n的关系x = f(n)
      4. x的数量级O(x)就是算法的空间复杂度S(n)
      5. 递归程序
         1. 找到递归调用的深度x与问题规模n的关系:x = f(n)
         2. x的数量级O(x)就是算法的空间复杂度S(n)
         3. *注意*:有的算法各层函数所需存储空间不同，分析方法略有区别
   5. 总结:**时间复杂度不计算时间，计算大概的运算次次数;空间复杂度不计算空间，计算大概定义的变量个数*
```cpp
//demo01
void Func1(int N){
    int count = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            ++count;//N**2
        }
    }
    for (int k = 0; k < 2 * N; ++k){
        ++count;
    }
}
int M = 10;
while (M--){
    ++count;
}
printf("%d\n", count);
//T(n) = O(n^2)

//demo02
void Func2(int N){
    int count = 0;
    for (int k = 0; k < 2 * N; ++k){
        ++count;//N
    }
    int M = 10;
    while (M--){
        ++count;//M
    }
    printf("%d\n", count);
}
//T(n) = O(N+M)

//demo03
void Func4(int N){
    int count = 0;
    for (int k = 0; k < 100; k++){
        ++count;
    }
    printf("%d\n", count);
}
//T(n) = O(1)

//demo04
void BubbleSort(int* a, int n){
    assert(a);
    for (size_t end = n; end > 0; ++end){
        int exchange = 0;
        for (size_t i = 1; i < end; ++i){
            if (a[i-1] > a[i]){
                Swap(&a[i-1], &a[i]);
                exchange = 1;
            }
        }
        if (exchange == 0)
            break;
    }
}
/*
假设有n个数排列，第一个数要排n-1次，第2个数要排n-2,...,第n个数要排1次，所以F(n)
F(n) = 1 + 2 + ...+ n-1 = n(n-1)/2
1.最坏T(n) = O(n^2)
2.最好T(n) = O(n),每个数各排一次，所以为O(n)
*/

//demo05
#include<iostream>
#include <assert.h>
#include <vector>
using namespace std;
/*
1.二分法的条件是有序数组,且必须是从小到大排列的有序数列
2.二分法的原理(从小到大):当中间项大于目标项，右缩区间:right = middle-1；当中间项小于目标项，左缩区间left = middle + 1,
当>,<都不满足时，中间项就是目标
3.时间复杂度
3-1.最坏时间复杂度T(n) = O(log_2 n),假设该数组有N个元素，
一直查找，直至只剩下1个元素:N/2/2/2/2.../2 = 1，
所以N = 2^x(x为查找的次数)，所以x = log2N(类似于折纸，折了x次，只剩下1个元素，所以N = 2^x),
3-2.最好时间复杂度:O(1)
*/
// 定义target在[left, right]区间
int search(vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
	while (left <= right) { // 当left==right，区间[left, right]依然有效，所以用 <=
		int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
		if (nums[middle] > target) {
			right = middle - 1; // target 在左区间，所以[left, middle - 1]
		} else if (nums[middle] < target) {
			left = middle + 1; // target 在右区间，所以[middle + 1, right]
		} else { // nums[middle] == target
			return middle; // 数组中找到目标值，直接返回下标
		}
	}
	// 未找到目标值
	return -1;
	//int(-2.6)=-3,int(2.6)=2,int函数是向下取整函数，所以，int函数的值应该是比自变量还要小的整数。
}

int main(){
	vector<int> v = {9, 5, 4, 3, 2};
	
	cout << search(v, 9) << endl;
}
//时间复杂度T(n) = O(log_2 n),

//demo06
//计算阶乘的时间复杂度
//size_t 类型表示C中任何对象所能达到的最大长度，它是无符号整数。此处等价与int
long long Factorial(size_t N){
	if (N == 0 || N == 1)
		return 1;
    return Factorial(N-1) * N;//1次
}
int main(){
	long long a = Factorial(0);
	cout << a << endl;
}
/*
1.递归算法计算: T(n) = 递归次数 * 每次递归函数的次数，
所以此例，递归次数 = N(!100则递归了100次)，每次递归函数的次数 = 1，所以为O(N)
*/
//*****************空间复杂度**********************//
//demo01
//计算bubblesort的空间复杂度
void BubbleSort(int* a, int n){
    assert(a);
    for (size_t end = n; end > 0; ++end){
        int exchange = 0;
        for (size_t i = 1; i < end; ++i){
            if (a[i-1] > a[i]){
                Swap(&a[i-1], &a[i]);
                exchange = 1;
            }
        }
        if (exchange == 0)
            break;
    }
}
//a, n, end, exchange, i一共5个，故S(n) = O(1)
//空间复杂度是计算变量的个数

//demo01
long long* Fibonacci(size_t n){
    if (n == 0)
        return NULL
    long long* fibArray = (long long*)malloc(n + 1) * sizeof(long long);//开辟了n+1个的空间，所以S(n) = O(n)
    fibArray[0] = 0;
    fibArray[1] = 1;
    for (int i = 2; i <= n; i++){
        fibArray[i] = fibArray[i-1] + fibArray[i-2];
    }
    return fibArray;
}

//demo02
long long Factorial(size_t N){
    return N < 2 ? N : Factorial(N-1) * N;
}
//递归了n次，所以为O(n)

```
## 1-2.oj
>方法:画图+思考+笔记
1. 消失的数字
   1. 描述:数组nums包含从0到n的所有整数，但其中缺了一个。请编写代码找出那个缺失的整数。你有办法在O(n)时间内完成吗？
   2. 求解
```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int total = n * (n + 1) / 2;
        int arrSum = 0;
        for (int i = 0; i < n; i++) {
            arrSum += nums[i];
        }
        return total - arrSum;
    }
};
//arrSum比total少了消失的一个数字，所以消失的数字为total-arrSum
```
2. 消失的数字
   1. 描述:一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
   2. 题解
```cpp
#include<iostream>
#include <assert.h>
#include <vector>
using namespace std;
//设nums = [4, 4, 5, 3]
vector<int> singleNumber(vector<int>& v){
	int ret = 0;
    for (int i = 0; i < v.size(); i++){
        ret ^= v[i];
    }
	int m = 0;//假设找到第m位
	while (m < 32){
		if(ret & (1<<m))//1左移m位
			break;
		else
			++m;
	}
	//分离
	int x1 = 0, x2 = 0;
	for (int i = 0; i < v.size(); i++){
		if (v[i] & (1<<m)){
			//1左移m位就可以判断第m为为1还是为0，因为此时已经找到3^5中第1为0的位，那么就可以用这个位将3和5分开
			x1 ^= v[i];
		}
		else{
			x2 ^= v[i];
		}
	}
	// vector<int> v1 = {x1, x2}; 
    // return v1;//方法2
    return vector<int>{x1, x2}
	
    /**
	 * @brief 
	 * 1.数组中所有数异或，那么出现2次的数字都^没了,ret = x1^x2
	 * 
	 * 2. 下一步是想办法分离出x1和x2,假设x2 = 5 = 0101, x1 = 3 = 0011, v = [4, 4, 5, 3], 4 = 0100
	 * 所以
	 * 	2-1.0101 ^ 0011 = 0110(同0异1 = 6)
	 * 	2-2.找出ret里面第M位为1的，说明x1和x2的第M位不一样(若是一样的话
	 * 那么第M位就为0)
	 * 
	 * 3.取数组中分离出x1和x2:第M位为1的为1组，第M位为0的为1组
	 * 最终得到，x1和x2各在一组，其他的数成对出现在1，2组中的某一组
	 * (由于相同的数^为0，所以他们一定会被分到同一组)
	 * 	3-1.原理:由于ret不为0，所以在在ret的32位数字中至少有1位为1，
	 * 所以通过1<<m 来寻找第一个不为0的位，再 与ret，若为true,
	 * 直接跳出循环
	 * 	3-2.推导
	 * def1 = {ret & m |
 	 * 	0110 &  0001 = 0000 = false,此时由于第0位为1，所以1需要左移一位得到
	 * 0010}
	 * def2 = {ret & m | 0110 & 0010 = true, 此时第1位1， 所此时直接跳出循环}
	 * 
	 * 4.分离
	 * 对v[i] & (1<<m), 此时(1<<m) = 0010,
	 * sol1: 3 & (1<<m) = (0011) & (0010) = 0010 = true, x1 = 3
	 * sol2: 5 & (1<<m) = (0101) & (0010) = 0000 = false, x2 = 5
	 * sol3: 4 & (1<<m) = (0100) & (0010) = 0000 = false, x2 = 5 ^ 4
	 * sol4: 4 & (1<<m) = (0100) & (0010) = 0000 = false, x2 = 5 ^ 4 ^ 4 = 5(相同的项被分到同一组的时候被异或为0,实际上
     * 相同的项被分到哪一组都不重要，因为最后他们异或为0)
	 * res = {g1, g2 | g1 = {3}, g2 = {5}}
	 */
	
}
```
   1. 算法 
      1. 思路:如果除了一个数字之外，其余数字都出现了2次，那么如何找到出现1次的数字?->进行*异或*操作，对每个操作数的每一位，相同结果为0, 不同结果为1。那么在计算过程中，成对出现的所有数字的所有位会两两抵消为0，最终得到的结果是出现1次的数字
      2. 那么如何将这一方法扩展到找出2个出现1次的数字？把所有的数字分成2组，使得
         1. 2个只出现1次的数字在不同的组中
         2. 相同的数字会被分到相同的组中。那么对这2个组分别进行异或操作，就可以得到答案
      3. 步骤
         1. 先对所有数字进行一次异或，得到两个出现一次的数字的异或值。
         2. 在异或结果中找到任意为1的位
         3. 根据这一位对所有的数字进行分组。
         4. 在每个组内进行异或操作，得到两个数字


# 2.链表和顺序表
## 2-1.顺序表的增删改查
1. SqList.h
```cpp
#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;
typedef int SLDataType;
#define N 5//定义顺序表大小

//静态顺序表设计(固定大小)
// struct SeqList{
//     SLDataType a[N];
//     int size;
// };
//动态顺序表设计
typedef struct SeqList{
    SLDataType* a;//数据类型指针为a
    int size;//有效数据个数
    int capacity;//容量
}SL;
//尾插尾删， 头插头删
void SeqListInit(SL* s);//初始化
void SeqListPrint(SL* s);//打印
void SeqListPushBack(SL* ps, SLDataType x);//ps = PointerSeqList
void SeqListPopBack(SL* ps);
void SeqListPushFront(SL* ps, SLDataType x);
void SeqListPopFront(SL* ps);
void SeqListCheckCapacity(SL* ps);
// 任意位置的插入删除
void SeqListInsert(SL* ps, int pos, SLDataType x);
void SeqListErase(SL* ps, int pos);
```
2. SqList.cpp
```cpp
#include "../include/SqList.h"
//1.初始化
void SeqListInit(SL* s){//传入结构体的地址
    // 方法1
    // s.size = 0;
    // s.a = NULL;
    // s.capacity = 0;
    // 方法2
    SeqListCheckCapacity(&s);
    s->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);//必须要添加<stdio.h>
    if (s->a == NULL){
        cout << "申请内存失败" << endl;
        exit(-1);
    }
    s->size = 0;
    s->capacity = 10;
}
//2.尾插
void SeqListPushBack(SL* ps, SLDataType x){
    assert(ps);//结构体指针不能为空,若ps = NULL会报错，中断下面程序的执行
    ps->a[ps->size] = x;//ps->a[i]指向开辟空间的第i个地址所对应的值
    ps->size++;    
}
//3.尾删
void SeqListPopBack(SL* ps){
    assert(ps);
    // ps->a[ps->size-1] = 0;不会这么做，因为刚好是0就有问题
    ps->size--;
}

//4.头插
void SeqListPushFront(SL* ps, SLDataType x){
    int end = ps->size - 1;
    while (end >= 0){
        ps->a[end + 1] = ps->a[end];
        end--;
    }
    ps->a[0] = x;
    ps->size++;
}
//5.头删
void SeqListPopFront(SL* ps){
    assert(ps);
    int start = 0;
    while (start < ps->size - 1){
        ps->a[start] = ps->a[start+1];
        start++;
    }
    ps->size--;
}


//6.检查容量
void SeqListCheckCapacity(SL* ps){
    if (ps->size >= ps->capacity){//用的少增加的少，用得多增加得多
        ps->capacity *= 2;
        ps->a = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * ps->capacity);//对它进行扩容后就不用担心空间不够的问题
        //把原来的空间给它再增容到我需要的空间
        if (ps->a == NULL){
            cout << "扩容失败\n" << endl;
            exit(-1);
        }
    }
}

//3.打印
void SeqListPrint(SL* ps){
    assert(ps);
    for (int i = 0; i < ps->size; i++){
        cout << ps->a[i] << endl;
    }
}
```

3. main.cpp
```cpp
#include "../include/SqList.h"
//测试头插头删
void TestSeqList1(){
    SeqList s;//必须要初始化和引用传值，否则SeqList里面全是随机值
    SeqListInit(&s);//必须初始化，否则出现29046 segmentation fault (core dumped)
    SeqListPushBack(&s, 1);
    SeqListPushBack(&s, 2);
    SeqListPushBack(&s, 3);//不能超过它的最大值
    SeqListPushBack(&s, 4);
    SeqListPushBack(&s, 5);
    SeqListPushBack(&s, 6);
    
    SeqListPopBack(&s);
    SeqListPopBack(&s);
    
    SeqListPushFront(&s, -1);

    SeqListPrint(&s);
}
int main(){
    TestSeqList1();
    return 0;
}
```
4. 综合
```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;
typedef int SLDataType;
typedef struct SeqList{
	SLDataType* a;
	int size;
	int capacity;
}SL;
//声明
void SeqListInit(SL* s);//初始化
void SeqListPrint(SL* s);//打印
void SeqListPushBack(SL* s, SLDataType x);
void SeqListPopBack(SL* s);
void SeqListPushFront(SL* s, SLDataType x);
void SeqListPopFront(SL* s);
//任意位置的插入和删除
void SeqListInsert(SL* s, int pos, SLDataType x);
void SeqListErase(SL* s, int pos);

void SeqListCheckCapacity(SL* s);
void SeqListDestroy(SL* s);

void SeqListInit(SL* s){
	s->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	if ( s == NULL ){//只要是插入和删除就要考虑空间问题
		printf("分配空间失败");
	}
	s->size = 0;
	s->capacity = 10;
}


void SeqListCheckCapacity(SL* ps){
    if (ps->size >= ps->capacity){//用的少增加的少，用得多增加得多
        ps->capacity *= 2;
        ps->a = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * ps->capacity);//对它进行扩容后就不用担心空间不够的问题
        //把原来的空间给它再增容到我需要的空间
        if (ps->a == NULL){
            cout << "扩容失败\n" << endl;
            exit(-1);
        }
    }
}

void SeqListDestroy(SL* ps){
    free(ps->a);//将指针所指向的空间释放
    ps->a = NULL;
    //空间释放后指针仍然指向这个空间，但是这个空间不存在了，所以这个指针是野指针，必须要置空
    ps->size = ps->capacity = 0;
    //ps为局部变量，程序执行完后自动销毁，所以无需自行销毁
}



void SeqListInsert(SL* s, int pos, SLDataType x){
	assert(s);
	assert(pos >= 0 || pos <= s->size);//应该是||而非&&
	SeqListCheckCapacity(s);
	int end = s->size - 1;
	while (end >= pos){
		s->a[end + 1] = s->a[end];
		end--; 
	}
	s->a[pos] = x;
	s->size++;
}


void SeqListErase(SL* s, int pos){
	assert(s);
	assert(pos >= 0 || pos <= s->size);
	int start = pos;
	while (start < s->size - 1){
		s->a[start] = s->a[start + 1];
		start++; 
	}
	s->size--;
}


void SeqListPushBack(SL* s, SLDataType x){
	SeqListCheckCapacity(s);
	// assert(s);
	// s->a[s->size] = x;
	// s->size++;
	SeqListInsert(s, s->size, x);//一定要在s->size作为添加的位置，因为该位置是在最后1个数的后面插入
}

void SeqListPopBack(SL* s){
	// assert(s);	
	// s->size--;
	SeqListErase(s, s->size-1);
}

void SeqListPushFront(SL* s, SLDataType x){
	// assert(s);
	// int end = s->size - 1;
	// while (end >= 0){
	// 	s->a[s->size] = s->a[s->size - 1];
	// 	end--;
	// }
	// s->a[0] = x;
	// s->size++;
	SeqListInsert(s, 0, x);
}
void SeqListPopFront(SL* s){
    // assert(ps);
    // int start = 0;
    // while (start < ps->size - 1){
    //     ps->a[start] = ps->a[start+1];
    //     start++;
    // }
    // ps->size--;
   	SeqListErase(s, 0);

}



int SeqListFind(SL* s, SLDataType x){
	for (int i = 0; i < s->size; i++){
		if (s->a[i] == x){
			return i;
		}
	}
	return -1;
}

void SeqListModify(SL* s, int pos, SLDataType x){
	assert(pos < s->size);
	s->a[pos] = x;
}



void SeqListPrint(SL* s){
	assert(s);
	for (int i = 0; i < s->size; i++){
		cout << s->a[i] << endl;
	}	
}W

int main(){
	SL s;//不要*s
	SeqListInit(&s);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 3);
	SeqListPushFront(&s, 3);
	SeqListPushFront(&s, 4);
	// SeqListInsert(&s, 2, 10);
	SeqListPrint(&s);
	SeqListDestroy(&s);
	
}

/**
 * @brief:删除和插入的等价
 * 1.PushBack(&s, x) = Insert(&s, s->size-1, x)
 * 2.PushFront(&s, x) = Insert(&s, 0, x)
 * 3.PopFront(&s) = Erase(&s, 0)
 * 4.PopBack(&s) = Erase(&s, s->size-1)
 */
```
## 2-2.顺序表的oj
1. 移除数组
   1. 问题描述:给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 *val* 的元素，并返回移除后数组的新长度。不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

```cpp
#include<iostream>
#include <assert.h>
#include <vector>
using namespace std;
int removeElement(vector<int>& v, int val){
	int left = 0;
	
	for (int right = 0; right < v.size(); right++){
		if (v[right] != val){
			v[left] = v[right];
			left++;
		}
	}
	return left;
}
int main(){
	vector<int> v = {0, 1, 2, 3, 3, 3};
	int a = removeElement(v, 3);
	cout << a << endl;
}
/**
 * @brief:当v[right] = val时，直接跳过left++，此时得到的left
 * 就是去除val后的长度
 * 1.当 v[right] != val时，v[left] = v[right]-> left++, right++
 * 2.当 v[right] = val时， right++, left在原位置不变  
 * 
 */
```


2. 删除有序数组中的重复项
   1. 返回数组中不含重复项的元素个数
```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
using namespace std;
int removeDuplicates(vector<int>& v){
	int n = v.size();
	int slow = 1;//第一个数绝对不是重复项，所以要从第二项开始比
	for (int fast = 1; fast < n; fast++){
		if (v[fast - 1] != v[fast]){
			v[slow] = v[fast];
			slow++;
		}
	}
	return slow;
}

int main(){
	vector<int> v = {1, 2, 3, 3, 3};
	int a = removeDuplicates(v);
	cout << a << endl;
}
/**
 * @brief
 * 1.要点:
 * 	1-1.对于有序数组而言，重复项一定是连在一起
 * `1-2.fast和slow指针分别为遍历数组要到达的位置，
 * 下一个不同元素要填入的下标位置
 * 
 * 2.执行逻辑
 * v = [0, 0, 1, 1, 2, 3, 4],所以用fast遍历数组中的每一个值
 * 若v[fast - 1] != v[fast], 那么v[fast]和之前的元素都不同，所以
 * 将fast的值赋值给slow, v[slow] = v[fast]
 * 3.双指针的作用是统计数据，但是对于原来的vector的数据不会更改
 */
```

3. 数组形式的整数加法
   1. 描述:整数的 数组形式  num 是按照从左到右的顺序表示其数字的数组.例如，对于 num = 1321 ，数组形式是 $[1,3,2,1]$ 。给定 num ，整数的 数组形式 ，和整数 k ，返回 整 数 num + k 的 数组形式 。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 vector<int> addToArrayForm(vector<int>& num, int k) {
     vector<int> res;
     int n = num.size();
     for (int i = n - 1; i >= 0; --i) {
         int sum = num[i] + k % 10;//取个位数
         k /= 10;//去掉个位数
         if (sum >= 10) {
	//若每一位相加>=10,那么最后1位加1，sum减10，类似于39 + 25 = 64(个位数相加为14,所以十位+1，个位-10)
             k++;
             sum -= 10;
         }
         res.push_back(sum);
     }
     reverse(res.begin(), res.end());
     return res;
 }

/**
 * @brief 
 * 1.思路:让我们逐位将数字加在一起。例如计算 123+912123+912，我们从低位到高位依次计算 3+23+2、2+12+1 和 1+91+9。任何时候，若加法的结果大于等于 1010，
 * 把进位的 11 加入到下一位的计算中，所以最终结果为 10351035。
 * 2.取得个位，十位数..的方法
 * 	2-1.个位:num % 10 (num是int类型)
 * 	2-2.十位:num / 10 % 10 (num / 10后仍然是int类型)
 * 	2-3.思路：不管取得几位数，想要取得最后1位数，就需要用%10来取余数来获取，
 * 以123为例，想要获取2， 需要将最后以为去掉，变成12， 然后12的个位数
 */
```

4. 合并2个有序数组
   1. *描述*:给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
   2. 注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。
```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = 0; i != n; ++i) {
            nums1[m + i] = nums2[i];
        }
        sort(nums1.begin(), nums1.end());
    }
};

```
5. 旋转数组
   1. 描述:给你一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
   2. 实例：
      1. >输入: nums = [1,2,3,4,5,6,7], k = 3
      2. >输出: [5,6,7,1,2,3,4]
      3. >解释:
         1. >向右轮转 1 步: [7,1,2,3,4,5,6]
         2. >向右轮转 2 步: [6,7,1,2,3,4,5]
         3. >向右轮转 3 步: [5,6,7,1,2,3,4]

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> newArr(n);
        for (int i = 0; i < n; ++i) {
            newArr[(i + k) % n] = nums[i];
        }
        nums.assign(newArr.begin(), newArr.end());
    }
};
```
6. 左移数组
   1. 描述:将含n个元素的数组左移m位，并输出翻转后的数组
   2. 求解
![leecode_1-1](../pictures/leecode_1-1.jpg)
```cpp
//demo01
//1.左移数组
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define num 100
int a[num];
void Move(int a[num],int n,int m);

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);//输入
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	Move(a,n,m);//移动
	for(int i=0;i<n-1;i++)//输出
	{
		printf("%d ",a[i]);
	}printf("%d",a[n-1]); 
}
void Move(int a[num],int n,int m)//循环左移
{
	//n为数组元素个数，m为移动数组的个数
	m=m%n;
	for(int i=0;i<m;++i)//循环次数
	{
		int temp = a[0];
		for(int j=0;j<n-1;j++)//移动n-1个数
		{
			a[j]=a[j+1];    
		}
		a[n-1]=temp;
		//第n个数为开始的数，即a[n-1] = a[0]
		//由于此时移动过后，将原来的a[0]覆盖掉了，所以需要将a[n-1] = temp而非a[n-1] = a[0]
	}
}

/**
 * @brief 
 * 1. 要点:Move(v, 5, 2);则对v含5个元素的数组v左移2位
 * 	1-1.循环2次，第一层循环为移动次数;第二层循环是将数组元素移动一位
 * 	1-2.第2层循环
 * 
 */


// 2.实现求最大公因数。前提是a > 0 , b > 0
//Greatest Common Divisor

int gcd(int a, int b)
{
    if(a % b == 0) return a;
    return gcd(b, a % b);

}
/**
 * @brief
 *  最大公约数的递归：
 * 1、若a可以整除b，则最大公约数是b
 * 2、如果1不成立，最大公约数便是b与a%b的最大公约数
 * 示例：求(140,21)
 * 140%21 = 14
 * 21%14 = 7
 * 14%7 = 0
 * 返回7
 * 
 */
```

```cpp
//demo02
#include<iostream>
#include<vector>
using namespace std;
void moveRight(vector<int>& v, int k){
	int n = v.size();
	vector<int> res(n);
	for (int i = 0; i < n; i++){//是 i < n而非i < n-1
		res[(i + k) % n] = v[i];
	}
	v.assign(res.begin(), res.end());//将新数组拷贝至原数组,顺序不要搞反了
}


void moveLeft(vector<int>& v, int k){
	int n = v.size();
	for (int i = 0; i < k; i++){
		int temp = v[0];
		for (int j = 1; j < n; j++){
			v[j - 1] = v[j];
		}
		v[n - 1] = temp; 
	}
}

void printArray(vector<int>& v){
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << "  ";
	}
	cout << endl;
}

int main(){
	vector<int> v = {1, 2, 3, 4};
	moveRight(v, 3);
	printArray(v);
}
```

## 2-2.链表的增删改查
### 2-2-1.操作
1. LinkList.h
```cpp
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int SLTDataType;
struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
};
typedef struct SListNode SLTNode;

// 不会改变链表的头指针，传一级指针
void SListPrint(SLTNode* phead);

// 可能会改变链表的头指针，传二级指针
void SListPushBack(SLTNode** pphead, SLTDataType x);
void SListPushFront(SLTNode** pphead, SLTDataType x);
void SListPopFront(SLTNode** pphead);
void SListPopBack(SLTNode** pphead);

SLTNode* SListFind(SLTNode* phead, SLTDataType x);
// 在pos的前面插入x
void SListInsert(SLTNode** phead, SLTNode* pos, SLTDataType x);
// 删除pos位置的值
void SListErase(SLTNode** phead, SLTNode* pos);

// 有些地方也有这样的
//// 在pos的前面插入x
//void SListInsert(SLTNode** phead, int i, SLTDataType x);
//// 删除pos位置的值
//void SListErase(SLTNode** phead, int i);
```


2. LinkList.cpp
```cpp
#include "../include/LinkList.h"

void SListPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

SLTNode* BuySListNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

void SListPushBack(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySListNode(x);

	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		// ÕÒÎ²½ÚµãµÄÖ¸Õë
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		// Î²½Úµã£¬Á´½ÓÐÂ½Úµã
		tail->next = newnode;
	}
}

void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySListNode(x);

	newnode->next = *pphead;
	*pphead = newnode;
}

void SListPopFront(SLTNode** pphead)
{
	SLTNode* next = (*pphead)->next;
	free(*pphead);

	*pphead = next;
}

void SListPopBack(SLTNode** pphead)
{
	// 1¡¢¿Õ
	// 2¡¢Ò»¸ö½Úµã
	// 3¡¢Ò»¸öÒÔÉÏµÄ½Úµã
	if (*pphead == NULL)
	{
		return;
	}
	else if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLTNode* prev = NULL;
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}

		free(tail);
		prev->next = NULL;
	}
}

SLTNode* SListFind(SLTNode* phead, SLTDataType x)
{
	SListNode* cur = phead;
	//while (cur != NULL)
	while (cur)
	{
		if (cur->data == x)
		{
			return cur;
		}

		cur = cur->next;
	}

	return NULL;
}

// ÔÚposµÄÇ°Ãæ²åÈëx
void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	if (pos == *pphead)
	{
		SListPushFront(pphead, x);
	}
	else
	{
		SLTNode* newnode = BuySListNode(x);
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}

		prev->next = newnode;
		newnode->next = pos;
	}
}

// É¾³ýposÎ»ÖÃµÄÖµ
void SListErase(SLTNode** pphead, SLTNode* pos)
{
	if (pos == *pphead)
	{
		SListPopFront(pphead);
	}
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}

		prev->next = pos->next;
		free(pos);
	}
}
```
3. main.cpp
```cpp
#include "../include/LinkList.h"

void TestSList1()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPushFront(&plist, 0);
	SListPrint(plist);

	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPrint(plist);

	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPrint(plist);
}

void TestSList2()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);

	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPrint(plist);
}

void TestSList3()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);

	// ÏëÔÚ3µÄÇ°Ãæ²åÈëÒ»¸ö30
	SLTNode* pos = SListFind(plist, 1);
	if (pos)
	{
		SListInsert(&plist, pos, 10);
	}
	SListPrint(plist);

	pos = SListFind(plist, 3);
	if (pos)
	{
		SListInsert(&plist, pos, 30);
	}
	SListPrint(plist);
}

void TestSList4()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);

	SLTNode* pos = SListFind(plist, 1);
	if (pos)
	{
		SListErase(&plist, pos);
	}
	SListPrint(plist);

	pos = SListFind(plist, 4);
	if (pos)
	{
		SListErase(&plist, pos);
	}
	SListPrint(plist);

	pos = SListFind(plist, 3);
	if (pos)
	{
		SListErase(&plist, pos);
	}
	SListPrint(plist);

	pos = SListFind(plist, 2);
	if (pos)
	{
		SListErase(&plist, pos);
	}
	SListPrint(plist);
}


int main()
{
	TestSList4();

	return 0;
}
```



4. 综合
```cpp
#include<iostream>
#include<vector>
using namespace std;
typedef int SListDataType;
struct SListNode{
	SListDataType data;
	SListNode* next;	
};
//1.创建节点
SListNode* BuySListNode(SListDataType x){
    SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
    if (newNode == NULL){
        printf("申请节点失败\n");
        exit(-1);
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}
//2.打印节点
void SListPrint(SListNode* phead){//phead = pointerhead
	SListNode* cur = phead;
	while (cur != NULL){
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
	
}

void SListPushBack(SListNode** pphead, SListDataType x){
	//param1:传入的指针，param2:传入的值
    
	//找尾
	//1.先开辟一个节点
    SListNode* newNode = BuySListNode(x);//申请一个newNode
	
	//2.判断节点是否为空
    if (*pphead == NULL){
        *pphead = newNode;
    }
    else
    {
        SListNode* tail = *pphead;//让tail指向头结点
		//pphead接受的1级指针的地址，那么*pphead就是1级指针的值，即phead
        while(tail->next != NULL){
            //空指针的解引用
            tail = tail->next;
        }
		tail->next = newNode;
    }
   
}
void SListPopBack(SListNode** pphead){
	//1.空
	if (*pphead == NULL){//为空
		return; 
	}
	else if((*pphead)->next == NULL){
		free(*pphead);//把节点直接干掉
		*pphead = NULL;//*pphead存的是pList的地址,所以*pphead = pList = NULL
	}
	else{
		SListNode* prev = NULL;
		SListNode* tail = *pphead;
		while (tail->next != NULL){
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		prev->next = NULL;
	}
	//2.1个节点
	//1.1个以上节点
}

int main(){
	SListNode* pList = NULL;
	//*pList = NULL则是这个节点本身地址为NULL,pList->next = NULL,则是他指向的下一个地址为空
	SListPushBack(&pList, 1);//此处要用2级指针
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);
	SListPrint(pList);

	/**
	 * @brief 
	 * 1. SListPushBack()中传入的是指针，但是SListPushBack中
	 * 接受的是指针，所以类似于值传递一样:
	 * void swap(int x, int y)
	 * swap(a, b)
	 * 
	 * 二者等同
	 * 
	 * void swap(int* x, int* y)
	 * swap(a, b) (*a = &c, *b = &d)
	 * 所以要改变x,y的值，要采用2级指针
	 * 
	 * 2.关于双指针的结论：
		1.若是pptr = &ptr ; ptr = &var---->var = *ptr(一级指针的值) = **pptr(二级指针的值)  
		2.p,*p,&p的关系：*是寻址符号，&是地址符号，p为变量值，所以*p为p值(地址)的解引用，&p为p的地址,p为值,
			有多少个*,就解引用多少次,解引用就是对地址进行寻址，  *(&p) = p
		3.int var, *ptr, **pptr(实际上定义的虽然是**pptr,但是指针变量是*ptr,同理可得ptr)--->  
		4.int **pptr------>*pptr为指针变量地址，**pptr为指针变量值
			当满足&var = ptr, &ptr = pptr时候：
				1.var = *ptr = **pptr(取值）,//重点****
				2.&var = ptr = *pptr(取址)//把*prt想成对prt的值进行解析，即进行指向
					示意图
				var       ptr       pptr 
			   d1 3000<---d2 d1 <---d3 d2
		5.分开来看:
		ptr = &var
		*ptr = *(&var) = var //ptr指针的值就是var的地址,*ptr是直接对var地址取值
		pptr = &ptr
		*pptr = *(&ptr) = ptr = &var
		**pptr = *(*pptr) = *(&var) = var    
		注意:每次在p前加入一个*,相当于对p进行 一次取值,
		6.对于**pptr,当未定义的时候，只能取得,pptr,&pptr,不能取得,*pptr,**pptr
		若var = 30,*pptr = &var,(pptr = &var是错误的),此时*(*pptr) = *(&var) = 30
		所以对于**pptr，*pptr = &var,即是保证2次寻址，pptr = &var就是1次寻址了，因为此时
		*pptr = *(&var) = 30,**pptr就失去了意义    
		7.指针和数组：int arr[]= {.......},int * ptr = arr<------> ptr = arr <---> ptr[i] = arr[i]        
	 */
}
```