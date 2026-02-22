<!--translate="no"-->
<h1 align="center">
  <span style="background: linear-gradient(to right, #007cf0, #00dfd8); -webkit-background-clip: text; color: transparent;">
    蓝桥杯 16届(2025) 第6题
  </span>
</h1>
<h3 align="center" style="color: #6e7c7c;">
  01-BFS(deque优化)
</h3>

 <h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🧩 一、题目描述:  

   [水质检测](https://www.lanqiao.cn/problems/20525/learning/)  
这道题很明显可以用BFS解决，只要从最开始的'#'开始入队遍历每一格,最后就可以扫描出每个'#'距离起点的最小dist，然后再寻找这些'#'中最大的dist即为答案;
 </h2>
   
对于第一段代码，我用了普通的BFS实现，每次只要对比从A->B时B点在A点的基础上会不会让起点到达B的距离变小，会的话则入队: 
  
 <h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🚀 代码实现（C++）
</h2>

```cpp
#include <bits/stdc++.h>
using namespace std;
const int m = 1e6 + 10;

string s[2];
int dist[2][m]; // 表示到达当前这一步时要加多少个水位监测仪
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
int ans, n, sx, sy;

struct node {
    int x, y;
};

void bfs() {
    memset(dist, 0x3f3f3f3f, sizeof dist);
    queue<node>q;
    q.push({ sx, sy });
    dist[sx][sy] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= 2 || ny < 0 || ny >= n) continue;
            int w = (s[nx][ny] == '#' ? 0 : 1); // 如果下一步是'#'则不需要继续搭建新的水质检测仪则此时w就为0,否则为1;
            if (dist[x][y] + w < dist[nx][ny]) { // 如果下一步在当前基础上 +w 比原先下一步的水位监测仪数量更少则更新入队;
                dist[nx][ny] = dist[x][y] + w;
                q.push({ nx, ny });
            }
        }
    }
}

int main() {
    cin >> s[0] >> s[1];
    n = s[0].size();
    for (int j = 0; j < n; j++) {
        if (s[0][j] == '#') {
            sx = 0, sy = j;
            bfs();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 2; j++) {
                    if (s[j][i] == '#') ans = max(ans, dist[j][i]);
                }
            }
            cout << ans;
            return 0;
        }
        if (s[1][j] == '#') {
            sx = 1, sy = j;
            bfs();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 2; j++) {
                    if (s[j][i] == '#') ans = max(ans, dist[j][i]);
                }
            }
            cout << ans;
            return 0;
        }
    }
    cout << 0;
    return 0;
}

```
但是提交之后除了test1过了，其他全部超时，所以我们需要对这个BFS进行优化;  
<h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  💡二、 优化原理
</h2>
  
在普通BFS中我们一般用queue进行入队出队操作，但是在这题中这样会对同一格重复入队造成浪费(有点像朴素Dijkstra)，所以我们需要把queue换成deque  
BFS的本质是层序遍历，也就是每次处理同一层的东西，这题我们可以发现当下一步是'#'时他们的dist是相同的，所以他们也因该是同一层的，这时我们不应该把他放入队尾和下一层一起操作而是因该加入队头和本层统一操作；
```cpp
deque<node>q;
    q.push_back({ sx, sy });
    dist[sx][sy] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop_front();
        vis[x][y] = 1;
        if (s[x][y] == '#') ans = max(ans, dist[x][y]); //因为每个格子都只访问一次直接得到最优解，所以直接在每次更新时更新最大dist得到答案;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= 2 || ny < 0 || ny >= n || vis[nx][ny]) continue;
            int w = (s[nx][ny] == '#' ? 0 : 1);
            if (dist[x][y] + w < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + w;
                if (w) q.push_back({ nx, ny }); //如果下一步是'.'则dist +1 与当前操作不在同一层所以加入队尾;
                else q.push_front({ nx,ny }); //如果下一步是'#'则dist不变与当前操作在同一层所以加入队头;
            }
        }
    }
}
```

优化后即可通过此题，完整代码如下:

<h2 style="border: 2px solid #007bff; border-radius: 10px; padding: 10px; background-color: #e6f7ff; color: #00509e;">
  🚀 代码实现（C++）
</h2>

```cpp
#include <bits/stdc++.h>
using namespace std;
const int m = 1e6 + 10;

string s[2];
int dist[2][m];
bool vis[2][m];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
int ans, n, sx, sy;

struct node {
    int x, y;
};

int bfs() {
    memset(dist, 0x3f3f3f3f, sizeof dist);
    deque<node>q;
    q.push_back({ sx, sy });
    dist[sx][sy] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop_front();
        vis[x][y] = 1;
        if (s[x][y] == '#') ans = max(ans, dist[x][y]);
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= 2 || ny < 0 || ny >= n || vis[nx][ny]) continue;
            int w = (s[nx][ny] == '#' ? 0 : 1);
            if (dist[x][y] + w < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + w;
                if (w) q.push_back({ nx, ny });
                else q.push_front({ nx,ny });
            }
        }
    }
    return ans;
}

int main() {
    cin >> s[0] >> s[1];
    n = s[0].size();
    for (int j = 0; j < n; j++) {
        if (s[0][j] == '#') {
            sx = 0, sy = j;
            cout << bfs();
            return 0;
        }
        if (s[1][j] == '#') {
            sx = 1, sy = j;
            cout << bfs();
            return 0;
        }
    }
    cout << 0;
    return 0;
}
```
