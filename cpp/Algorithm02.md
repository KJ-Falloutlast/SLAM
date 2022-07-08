# 1.时间复杂度和空间复杂度
1. 定义:算法中**基本操作的执行次数**为时间复杂度
2. 大O渐进表示法
   1. 推导大O表示法:
      1. 用1取代运行时间中的所有加法常数
      2. 在修改后的运行次数函数中， 只保留最高阶项
      3. 如果最高阶项存在且不是1，则去除与这个项目相乘的常数，得到的就是O阶
   2. 通过上面的计算，Func1执行次数: $F(N) = N^2 + N*2 + 10$,所以实际上我们只需要知道大概的执行次数，那么需要用到大O表示法，所以$T(n) = O(N^2)$
   3. 有的情况下，算法中基本操作重复执行的次数还随着**输入数据集**的不同而不同
      1. 最坏时间复杂度:最坏情况下，算法的时间复杂度
      2. 平均时间复杂度:所有可能输入实例在等概率出现的情下，算法的期望运行时间
      3. 最好时间复杂度:最好情况下， 算法的时间复杂度
      4. 例如:在长度为N的数组中搜索一个数x,*最好情况*:1次找到，*最坏情况*:N次找到，平均情况:N/2次找到
      5. 总结：一般来说考虑**最坏时间复杂度**，因为考虑最坏情况下的时间复杂度，可以保证算法的运行时间不会比他更长
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
    return Factorial(N-1) * N;
}
int main(){
	long long a = Factorial(0);
	cout << a << endl;
}
/*
1.递归算法计算: T(n) = 递归次数 * 每次递归函数的次数
*/

```

