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
