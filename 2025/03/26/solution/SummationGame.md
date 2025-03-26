数值越大的数对答案的影响最大。

首先考虑把最大的前 $x$ 个数取负，然后枚举删除的数，当然要取负的数也后移。

时间复杂度 $O(max(n, k+x))$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
	int n, k, x;
	std::cin >> n >> k >> x;

	std::vector<int> a(std::max(n, k + x));
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	std::sort(a.rbegin(), a.rend());

	int ans = std::accumulate(a.begin(), a.end(), 0);
	for (int i = 0; i < x; ++i) {
		ans -= 2 * a[i];
	}
	int tans = ans;
	for (int i = x; i < k + x; ++i) {
		if (i - x + 1 <= k) {
			tans = tans + a[i - x] - 2 * a[i];
			ans = std::max(ans, tans);
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

