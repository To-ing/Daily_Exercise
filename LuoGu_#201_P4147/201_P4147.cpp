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
