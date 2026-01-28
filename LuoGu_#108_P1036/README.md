<!--translate="no"-->
<h1 align="center">
  <span style="background: linear-gradient(to right, #007cf0, #00dfd8); -webkit-background-clip: text; color: transparent;">
    洛谷 #108_P1036 题解
  </span>
</h1>
<h3 align="center" style="color: #6e7c7c;">
  NOIP 2002 普及组 | 组合数生成算法
</h3>

 <h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🧩 一、题目描述:  
   
这道题要求从 n 个数字中选 k 个并且这 k 个数字的和是素数。问选法共有几种？  
 </h2>
   
对于第一段代码，我选择用DFS和埃氏筛，这是很容易想到的:  
  
 <h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🚀 代码实现（C++）
</h2>

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int Max = 1e8;

int n, k;
int cnt = 0;
bool is_Prime[Max + 1];

void sieve() {
    is_Prime[0] = is_Prime[1] = true;
    for (int i = 2; i * i < Max; i++) {
        if (!is_Prime[i]) {
            for (int j = i * i; j < Max; j += i) {
                is_Prime[j] = true;
            }
        }
    }
}

void dfs(int id, int cnt_k, ll sum, vector<int>& x) {
    if (cnt_k == k) {
        if (!is_Prime[sum]) cnt++;
        return;
    }
    for (int i = id; i < n; i++) {
        dfs(i + 1, cnt_k + 1, sum + x[i], x);
    }
}

int main() {
    sieve();
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    dfs(0, 0, 0, x);
    cout << cnt;
    return 0;
}
```
但是再仔细观察这题可以发现是从 n 个数中选出 k 个数，所以我们也可以想到高德纳提出的位运算算法--组合数生成:  
<h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  💡三、组合数生成算法:
</h2>

```cpp
int n, k; //在n位二进制数中选择k位位1;
cin >> n >> k; 
int x = (1 << k) - 1; //满足要求的最小值;
int y = 1 << n; //x的上限;
while (x < y) {
  int c = x & (-x); //先求出x的最低位1在哪;
  int r = x + c; //进位操作;
  x = ((r ^ x) >> 2) / c | r;
  //这一步可以拆开解释先是内层（r ^ x) 这一步实际在进行标记,标记出有哪些位置的数字进位了;
  //然后把 (r ^ x) >> 2实际是先把移动后的最高一位进位的1去除,然后因为进位后和原先相比只少了t - 1个 1 所以还要再右移一位减少一个1;
  //再此基础上把整体/c实际就是把这些少的1全部右移至最低位；
  //最后把这些最低位的 1 和进位后的数字 r 按位或进行合并即可得出下一个数;
}
```

所以我们可以发现这个算法刚好可以实现选数的操作最后只需要结合类似二进制枚举的操作就可以完成这道题；  

<h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🚀 代码实现（C++）
</h2>

```cpp
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int x) {
	if (x < 2) return 0;
	if (x == 2) return 1;
	if (x % 2 == 0) return 0;
	for (int i = 3; i * i <= x; i += 2) {
		if (x % i == 0) return 0;
	}
	return 1;
}

int n, k, c, a, r, y, sum, ans;

int main() {
	cin >> n >> k;
	vector<int> x(n);
	for (int i = 0; i < n; i++) cin >> x[i];
	a = (1 << k) - 1;
	y = 1 << n;
	while (a < y) {
		sum = 0;
		for (int i = 0; i < n; i++) { //一定要把for循环求和放在开头这样才可以保证每次的 a < y;
			if (a & (1 << i)) sum += x[i];
		}
		if (isPrime(sum)) ans++;
		c = a & (-a);
		r = a + c;
		a = ((r ^ a) >> 2) / c | r;
	}
	cout << ans;
	return 0;
}
```
