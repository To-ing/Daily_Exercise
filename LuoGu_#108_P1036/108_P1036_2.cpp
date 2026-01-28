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
		for (int i = 0; i < n; i++) {
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
