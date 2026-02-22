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
