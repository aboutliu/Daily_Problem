打表发现，每个数乘以一个质数就满足条件。所以用欧拉筛预处理，再枚举 $[1,n]$ 用双指针更新答案即可。

时间复杂度 $O(n)$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

struct Sieve {
	int n;
	std::vector<int> pri, isp, mn;
	Sieve() {}
	Sieve(int _) {
		init(_);
	}
	void init(int _) {
		n = _;
		mn.resize(n + 1);
		isp.resize(n + 1);
		work();
	}
	void work() {
		for (int i = 2; i <= n; ++i) {
			if (!isp[i]) {
				pri.emplace_back(i);
				mn[i] = i;
			}
			for (int j = 0; j < pri.size() && i * pri[j] <= n; ++j) {
				isp[i * pri[j]] = 1;
				mn[i * pri[j]] = pri[j];
				if (!(i % pri[j])) {
					break;
				}
			}
		}
	}
};

void solve() {
	int n;
	std::cin >> n;

	Sieve sie(n);

	i64 ans = 0;
	for (int l = 1, r = -1; l <= n; ++l) {
		while (r + 1 < sie.pri.size() && l * sie.pri[r + 1] <= n) {
			r++;
		}
		while (r > -1 && l * sie.pri[r] > n) {
			r--;
		}
		ans += r + 1;
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

