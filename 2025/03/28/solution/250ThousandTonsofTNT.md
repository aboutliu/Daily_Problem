注意到 $[1,150000]$ 以内的数的因子最多的很少，所以暴力枚举 $n$ 的因子，前缀和更新即可。

时间复杂度 $O(n \cdot max(d_{1..150000}),d_x $ 表示 $x$ 的因子数量。 

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

	std::vector<i64> pref(n + 1);
	for (int i = 0; i < n; ++i) {
		pref[i + 1] += pref[i] + a[i];
	}

	std::vector<int> fac;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; j += i) {
			if (j == n) {
				fac.emplace_back(i);
			}
		}
	}

	i64 ans = 0;
	for (auto i : fac) {
		i64 min = 1E18, max = 0;
		for (int j = i; j <= n; j += i) {
			min = std::min(min, pref[j] - pref[j - i]);
			max = std::max(max, pref[j] - pref[j - i]);
		}
		ans = std::max(ans, max - min);
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

