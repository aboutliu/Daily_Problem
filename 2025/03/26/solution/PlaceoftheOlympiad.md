二分答案。$check$ 写最多能放多少，检查是否小于等于 $k$ 。最多能放一定是先放 $n$ 行 $mid$ ，再隔一列，再放 $n$ 行 $mid...$ 。 

时间复杂度 $O(t \cdot logm)$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;

	auto check = [&](int x) -> int {
		i64 sum = 1LL * m / (x + 1) * x * n;
		i64 t = 1LL * m % (x + 1) * n;
		return sum + t >= k;
	};

	int lo = 1, hi = m, ans = m;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (check(mid)) {
			ans = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
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

