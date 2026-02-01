<!--translate="no"-->
<h1 align="center">
  <span style="background: linear-gradient(to right, #007cf0, #00dfd8); -webkit-background-clip: text; color: transparent;">
    洛谷 #201_P4147 题解
  </span>
</h1>
<h3 align="center" style="color: #6e7c7c;">
  dp-悬线法
</h3>

 <h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🧩 一、题目描述:  

   [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)  
这道题要求从 N × M 的地图中找到最大矩形
 </h2>
  我们可以使用悬线法解决这道题；  
<h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  💡二、悬线法:
</h2>

  顾名思义就是有一条左线和右线分别是每个矩形的最大左边界和右边界；  
  
  1.先确定左右边界:  
  利用dp从左向右依次更新每一个格子的最左值，从右向左依次更新每一个格子的最右值，得到如图效果:  
    
  <img width="335" height="232" alt="image" src="https://github.com/user-attachments/assets/851b0666-a1fd-4ea0-82be-7f5c1a5b5877" />  
    
  2.从上到下确定格子高度，再根据左右边界就可确定一个矩形:  
    
  <img width="400" height="150" alt="image" src="https://github.com/user-attachments/assets/824c15f0-df2f-4ea9-9355-228cee256314" />    
    
  左图就是悬线法最后做出的矩形，而右图因为包含了障碍点所以是错误的做法  

  悬线法模板如下:  
```cpp
char G[m][m];
int h[m][m], l[m][m], r[m][m]; // 每个格子的高度h要初始化为1，左右边界也要初始化 l[i][j] = r[i][j] = j;
int N, M, ans;

for (int i = 1; i <= N; i++) {
    for (int j = 2; j <= M; j++) {
		if (G[i][j] == 'F' && G[i][j - 1] == 'F') l[i][j] = l[i][j - 1]; // 左边一格如果也是通路那么当前格子的左边界应该与左边一格的左边界相同；
    }
    for (int j = M - 1; j >= 1; j--) {
		if (G[i][j] == 'F' && G[i][j + 1] == 'F') r[i][j] = r[i][j + 1]; // 右边一格如果也是通路那么当前格子的右边界应该与右边一格的右边界相同；
    }
}
for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
        if (G[i][j] == 'F' && G[i - 1][j] == 'F') {
            h[i][j] = h[i - 1][j] + 1; // 上边一格如果也是通路那么当前格子的高度为上面格子的高度 + 1；
            l[i][j] = max(l[i][j], l[i - 1][j]); //每条线的左边界应该是这条线上每一格左边界的最右值；
            r[i][j] = min(r[i][j], r[i - 1][j]); //每条线的右边界应该是这条线上每一格右边界的最左值；
        }
        if (G[i][j] == 'F') ans = max(ans, h[i][j] * (r[i][j] - l[i][j] + 1));
    }
}
```
结合上面的悬线法就可以做出这道题；

<h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🚀 代码实现（C++）
</h2>

```cpp
#include <bits/stdc++.h>
using namespace std;
const int m = 1010;

char G[m][m];
int h[m][m], l[m][m], r[m][m];
int N, M, ans;

void init_G() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> G[i][j];
			h[i][j] = 1;
			l[i][j] = r[i][j] = j;
		}
	}
}

int main() {
	init_G();
	for (int i = 1; i <= N; i++) {
		for (int j = 2; j <= M; j++) {
			if (G[i][j] == 'F' && G[i][j - 1] == 'F') l[i][j] = l[i][j - 1];
		}
		for (int j = M - 1; j >= 1; j--) {
			if (G[i][j] == 'F' && G[i][j + 1] == 'F') r[i][j] = r[i][j + 1];
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (G[i][j] == 'F' && G[i - 1][j] == 'F') {
				h[i][j] = h[i - 1][j] + 1;
				l[i][j] = max(l[i][j], l[i - 1][j]);
				r[i][j] = min(r[i][j], r[i - 1][j]);
			}
			if (G[i][j] == 'F') ans = max(ans, h[i][j] * (r[i][j] - l[i][j] + 1));
		}
	}
	cout << ans * 3;
	return 0;
}

```
