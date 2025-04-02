注意到所有的偶数可以转移到某一个奇数上去，那贪心的转移到最大的奇数上，但是此时并不最优，因为除了最大的奇数，剩余的奇数还可以转移 $x-1$ 到偶数上去，也就是剩余的先转移到偶数上，偶数在转移到最大的奇数上。那你肯定想到也可以转移到最大的偶数上，但是这并不优于转移到最大的奇数上，你可以模拟试试。

时间复杂度 $O(nlogn)$ 。

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

	std::vector<int> odd, even;
	for (int i = 0; i < n; ++i) {
		int u;
		std::cin >> u;

		if (u & 1) {
			odd.emplace_back(u);
		} else {
			even.emplace_back(u);
		}
	}

	if (odd.size() && even.size()) {
		i64 sum1 = 0, sum2 = 0;
		std::sort(odd.begin(), odd.end());
		sum1 += odd.back() + std::accumulate(even.begin(), even.end(), 0LL);
		for (int i = 0; i < odd.size() - 1; ++i) {
			sum1 += odd[i] - 1;
		}
		std::cout << sum1 << "\n";
	} else if (odd.size()) {
		int ans = *max_element(odd.begin(), odd.end());
		std::cout << ans << "\n";
	} else {
		int ans = *max_element(even.begin(), even.end());
		std::cout << ans << "\n";
	}
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

