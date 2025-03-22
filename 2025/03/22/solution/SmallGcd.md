易得排序并不影响答案，升序之后可以简化为 $ans = \sum_{i=1}^n \sum_{j=1}^{i-1} gcd(a_i, a_j) \times (n - i)$ 。这类题有点套路，一般可以枚举因子。

设 $f_x$ 为 $a_j$ 为 $x$ 的倍数的个数，$g_x$ 为 $gcd(a_i, a_j) = x$ 的个数，$j \in [1, i)$ 。用调和级数预处理出每个数的因子，枚举 $i$ 的时候我们从大到小枚举 $a_i$ 的因子 $d$ ，我们先让 $g[d] = f[d]$ ，此时，如果有一个数 $t$ 且 $d|t$ ，那么 $g[d]$ 应该减去 $g[t]$ ，所以我们还应该枚举 $d$ 的因子进行容斥。

复杂度是 $O(VlogmaxV + n \; maxd^2(V)$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

constexpr int N = 1E5;

std::vector<std::vector<int>> fac(N + 1);

void init() {
	for (int i = 1; i <= N; ++i) {
		for (int j = i; j <= N; j += i) {
			fac[j].emplace_back(i);
		}
	}
	for (int i = 1; i <= N; ++i) {
		std::reverse(fac[i].begin(), fac[i].end());
	}
}

void solve() {
	int n;
	std::cin >> n;

	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::sort(a.begin(), a.end());

	int range = *max_element(a.begin(), a.end());
	std::vector<int> f(range + 1), g(range + 1);
	i64 ans = 0LL;
	for (int i = 0; i < n; ++i) {
		int t = a[i];
		for (auto d : fac[t]) {
			g[d] = f[d];
		}
		for (auto d : fac[t]) {
			for (auto td : fac[d]) {
				g[td] -= (d != td) * g[d];
			}
		}
		for (auto d : fac[t]) {
			ans += 1LL * d * (n - i - 1) * g[d];
			f[d]++;
		}
	}

	std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init();

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```

