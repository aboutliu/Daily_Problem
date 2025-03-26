$[1,n]$ 以内的数因子最多的 $128$ 。考虑枚举 $k$ ，相对应的数要同余，那么合法的 $m$ 是其差值的因子，遍历 $[1,n]$ 得出所有的差值，求他们的 $gcd$ 。检查大于等于 $2$ 即可，全相等 $gcd$ 等于 $0$ 。

时间复杂度 $O(max(d_{1...n})\cdot n),d_x$ 表示 $x$ 因子数量。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
	int n;
	std::cin >> n;

	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<int> fac;
	for (int i = 1; i <= n / i; ++i) {
		if (n % i == 0) {
			fac.emplace_back(i);
			if (n / i != i) {
				fac.emplace_back(n / i);
			}
		}
	}

	int ans = 0;
	for (auto k : fac) {
		if (k == n) {
			ans++;
			continue;
		}
		std::vector<int> g;
		for (int i = k; i < n; i += k) {
			std::vector<int> ord;
			for (int j = i - k; j < i; ++j) {
				ord.emplace_back(std::abs(a[j] - a[j + k]));
			}
			int gcd = 0;
			for (int j = 0; j < ord.size(); ++j) {
				gcd = std::gcd(gcd, ord[j]);
			}
			g.emplace_back(gcd);
		}
		int gcd = 0;
		for (auto j : g) {
			gcd = std::gcd(gcd, j);
		}
		ans += gcd > 1 | !gcd;
	}
	std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```

