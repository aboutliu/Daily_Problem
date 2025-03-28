设 $dp_i$ 表示以 $i$ 结尾的答案，按条件更新即可。

时间复杂度 $O(n)$ 。

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

	std::vector<int> dp(n + 1, -1E9);
	for (int i = 0; i < n; ++i) {
		dp[i + 1] = a[i];
		if (!i) {
			continue;
		}
		if ((a[i] & 1) != (a[i - 1] & 1)) {
			dp[i + 1] = std::max(dp[i + 1], a[i] + dp[i]);
		}
	}

	int ans = *max_element(dp.begin(), dp.end());
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

